// Reprise d'un brouillon enregistré, peut-être par une version précédente.
// Les réponses sont retrouvées par leur libellé : une option renommée ou
// supprimée dans questionnaire.json est retirée du bilan et signalée, au lieu
// d'aller dans le Word sans apparaître à l'écran.
import { lateralites, libellesCaractere, nouveauBilan, questionnaire, type Bilan } from './bilan'

/** Format du brouillon ; l'augmenter (et adapter reprendre) si une réponse change de forme. */
export const VERSION_BROUILLON = 2

export interface Reprise {
  bilan: Bilan
  /** Réponses retirées, sous la forme « valeur (rubrique) ». */
  retirees: string[]
}

type Objet = Record<string, unknown>
type ChoixSimple = 'classe' | 'typeEtablissement' | 'modeDeGarde' | 'entente' | 'personneDemandeuse'
  | 'dossierMdph' | 'accordParents'
type ChoixMultiple = 'motifs' | 'troubles' | 'comportement' | 'difficultes' | 'matieresPreferees'
  | 'matieresDetestees' | 'amenagements' | 'caractereParents' | 'caractereEnfant'

function estObjet(valeur: unknown): valeur is Objet {
  return typeof valeur === 'object' && valeur !== null && !Array.isArray(valeur)
}

/** La valeur enregistrée a la forme de la valeur de départ (sinon elle est ignorée). */
function memeForme(valeur: unknown, depart: unknown): boolean {
  if (Array.isArray(depart)) return Array.isArray(valeur) && valeur.every((v) => typeof v === 'string')
  if (depart === null) return valeur === null || Number.isInteger(valeur) // latéralité
  if (estObjet(depart)) return estObjet(valeur)
  return typeof valeur === typeof depart
}

function dateValide(date: string): boolean {
  return /^\d{4}-\d{2}-\d{2}$/.test(date) && !Number.isNaN(Date.parse(date))
}

export function enregistrement(bilan: Bilan): string {
  return JSON.stringify({ version: VERSION_BROUILLON, bilan })
}

export function reprendre(texte: string, date = new Date()): Reprise | null {
  let donnees: unknown
  try {
    donnees = JSON.parse(texte)
  } catch {
    return null
  }
  if (!estObjet(donnees)) return null
  // Version 1 (jusqu'à 1.2.1) : les réponses à la racine, sans numéro de version.
  const enregistre = typeof donnees.version === 'number' && estObjet(donnees.bilan) ? donnees.bilan : donnees

  const bilan = nouveauBilan(date)
  const reponses = bilan as unknown as Objet
  for (const [cle, depart] of Object.entries(reponses))
    if (memeForme(enregistre[cle], depart)) reponses[cle] = enregistre[cle]

  const depart = nouveauBilan(date)
  if (!['Femme', 'Homme'].includes(bilan.sexe)) bilan.sexe = depart.sexe
  if (!['Enfant', 'Ado'].includes(bilan.trancheAge)) bilan.trancheAge = depart.trancheAge

  const retirees: string[] = []

  // Dates AAAA-MM-JJ, comme un champ <input type="date"> : sinon l'âge vaudrait « NaN ».
  const dates: ['dateNaissance' | 'datePassation', string][] = [
    ['dateNaissance', 'Date de naissance'], ['datePassation', 'Date de passation'],
  ]
  for (const [cle, rubrique] of dates) {
    if (bilan[cle] && !dateValide(bilan[cle])) {
      retirees.push(`${bilan[cle]} (${rubrique})`)
      bilan[cle] = depart[cle]
    }
  }

  const { identite, demande, suivis, scolarite, otHope, objectifs, amenagements } = questionnaire

  const simples: [ChoixSimple, readonly string[], string][] = [
    ['classe', identite.classes, 'Classe'],
    ['typeEtablissement', identite.typesEtablissement, 'Établissement'],
    ['modeDeGarde', identite.modesDeGarde, 'Mode de garde'],
    ['entente', identite.entente.map((e) => e.libelle), 'Entente'],
    ['personneDemandeuse', demande.personnesDemandeuses, 'Personne demandeuse'],
    ['dossierMdph', demande.dossierMdph, 'Dossier MDPH'],
    ['accordParents', objectifs.accordParents.map((a) => a.libelle), 'Accord des parents'],
  ]
  for (const [cle, liste, rubrique] of simples) {
    if (bilan[cle] && !liste.includes(bilan[cle])) {
      retirees.push(`${bilan[cle]} (${rubrique})`)
      bilan[cle] = ''
    }
  }

  const multiples: [ChoixMultiple, readonly string[], string][] = [
    ['motifs', demande.motifs, 'Motifs'],
    ['troubles', demande.troubles, 'Troubles'],
    ['comportement', scolarite.comportement, 'Comportement en classe'],
    ['difficultes', scolarite.difficultes, 'Difficultés en classe'],
    ['matieresPreferees', scolarite.matieres, 'Matières préférées'],
    ['matieresDetestees', scolarite.matieres, 'Matières moins appréciées'],
    ['amenagements', amenagements, 'Aménagements'],
    ['caractereParents', libellesCaractere(), 'Caractère selon les parents'],
    ['caractereEnfant', libellesCaractere(), 'Caractère selon l\'enfant'],
  ]
  for (const [cle, liste, rubrique] of multiples) {
    for (const valeur of bilan[cle].filter((v) => !liste.includes(v))) retirees.push(`${valeur} (${rubrique})`)
    bilan[cle] = bilan[cle].filter((v) => liste.includes(v))
  }

  if (bilan.lateralite !== null && !(bilan.lateralite >= 0 && bilan.lateralite < lateralites(bilan.sexe).length)) {
    retirees.push(`choix n° ${bilan.lateralite + 1} (Latéralité)`)
    bilan.lateralite = null
  }

  const professionnels: Record<string, string> = {}
  for (const [professionnel, frequence] of Object.entries(bilan.professionnels)) {
    if (!suivis.professionnels.includes(professionnel)) {
      retirees.push(`${professionnel} (Professionnels)`)
    } else if (typeof frequence !== 'string' || !suivis.frequences.includes(frequence)) {
      if (frequence) retirees.push(`${frequence} (Fréquence de suivi)`)
      professionnels[professionnel] = ''
    } else {
      professionnels[professionnel] = frequence
    }
  }
  bilan.professionnels = professionnels

  // OT Hope : domaine, activité et niveau doivent exister ; les objectifs suivent les activités.
  const niveaux = otHope.niveaux.map((n) => n.id)
  const cotations: Bilan['otHope'] = {}
  const objectifsParDomaine: Bilan['objectifs'] = {}
  for (const domaine of otHope.domaines) {
    const enregistrees = bilan.otHope[domaine.id]
    const reponsesDomaine: Record<string, string> = {}
    for (const [activite, niveau] of Object.entries(estObjet(enregistrees) ? enregistrees : {})) {
      if (domaine.activites.includes(activite) && niveaux.includes(niveau)) reponsesDomaine[activite] = niveau
      else retirees.push(`${activite} (OT Hope : ${domaine.titre})`)
    }
    cotations[domaine.id] = reponsesDomaine
    const choisis = bilan.objectifs[domaine.id]
    objectifsParDomaine[domaine.id] = Array.isArray(choisis)
      ? choisis.filter((o) => typeof o === 'string' && domaine.activites.includes(o))
      : []
  }
  for (const domaine of Object.keys(bilan.otHope))
    if (!otHope.domaines.some((d) => d.id === domaine)) retirees.push(`domaine « ${domaine} » (OT Hope)`)
  bilan.otHope = cotations
  bilan.objectifs = objectifsParDomaine
  const activites = otHope.domaines.flatMap((d) => d.activites)
  bilan.objectifsFinaux = bilan.objectifsFinaux.filter((o) => activites.includes(o))
  bilan.objectifsParents = bilan.objectifsParents.filter((o) => activites.includes(o))

  // Coordonnées des parents (fiche patient) : du texte seulement.
  bilan.coordonnees = Object.fromEntries(
    Object.entries(bilan.coordonnees).filter(([, valeur]) => typeof valeur === 'string'))

  return { bilan, retirees: [...new Set(retirees)] }
}
