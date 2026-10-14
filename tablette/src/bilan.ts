// Réponses du questionnaire et champs {…} du modèle contenu/bilan.docx.
// Les champs sont calculés comme dans l'application Windows (écrans interface*.cpp) :
// les deux applications produisent le même bilan.
import questionnaire from '@contenu/questionnaire.json'

export { questionnaire }

export type Sexe = 'Femme' | 'Homme'
export type TrancheAge = 'Enfant' | 'Ado'

export interface Bilan {
  sexe: Sexe
  trancheAge: TrancheAge
  prenom: string
  nom: string
  /** AAAA-MM-JJ, comme un champ <input type="date">. */
  dateNaissance: string
  datePassation: string
  classe: string
  typeEtablissement: string
  nomEtablissement: string
  /** Indice dans identite/lateralite/<sexe> : le libellé s'accorde au sexe. */
  lateralite: number
  modeDeGarde: string
  enfantUnique: boolean
  fratrie: string
  entente: string
  medecinTraitant: string
  ville: string
  personneDemandeuse: string
  motifs: string[]
  autreMotif: string
  troubles: string[]
  autreTrouble: string
  dossierMdph: string
  aucunProfessionnel: boolean
  /** Professionnel suivi → fréquence du suivi. */
  professionnels: Record<string, string>
  comportement: string[]
  difficultes: string[]
  matieresPreferees: string[]
  autreMatierePreferee: string
  matieresDetestees: string[]
  autreMatiereDetestee: string
  /** Domaine OT Hope → activité → identifiant du niveau (absente : rien à signaler). */
  otHope: Record<string, Record<string, string>>
  /** Domaine OT Hope → objectifs choisis, dans l'ordre du choix. */
  objectifs: Record<string, string[]>
  objectifsFinaux: string[]
  accordParents: string
  objectifsParents: string[]
  remarquesParents: string
  amenagements: string[]
  activitesExtraScolaires: string
  activitesTempsLibre: string
  difficultesLoisirs: string
}

export const NOMBRE_OBJECTIFS = 5

export function aujourdhui(date = new Date()): string {
  const deux = (n: number) => String(n).padStart(2, '0')
  return `${date.getFullYear()}-${deux(date.getMonth() + 1)}-${deux(date.getDate())}`
}

export function nouveauBilan(date = new Date()): Bilan {
  const { identite, demande, objectifs } = questionnaire
  return {
    sexe: 'Femme',
    trancheAge: 'Enfant',
    prenom: '',
    nom: '',
    dateNaissance: '',
    datePassation: aujourdhui(date),
    classe: identite.classes[0],
    typeEtablissement: identite.typesEtablissement[0],
    nomEtablissement: '',
    lateralite: 0,
    modeDeGarde: identite.modesDeGarde[0],
    enfantUnique: false,
    fratrie: '',
    entente: identite.entente[0].libelle,
    medecinTraitant: '',
    ville: '',
    personneDemandeuse: demande.personnesDemandeuses[0],
    motifs: [],
    autreMotif: '',
    troubles: [],
    autreTrouble: '',
    dossierMdph: demande.dossierMdph[0],
    aucunProfessionnel: false,
    professionnels: {},
    comportement: [],
    difficultes: [],
    matieresPreferees: [],
    autreMatierePreferee: '',
    matieresDetestees: [],
    autreMatiereDetestee: '',
    otHope: {},
    objectifs: {},
    objectifsFinaux: [],
    accordParents: objectifs.accordParents[0].libelle,
    objectifsParents: [],
    remarquesParents: '',
    amenagements: [],
    activitesExtraScolaires: '',
    activitesTempsLibre: '',
    difficultesLoisirs: '',
  }
}

/** Âge en années et mois révolus à la date de référence (dates AAAA-MM-JJ). */
export function calculerAge(naissance: string, reference: string): string {
  if (!naissance || !reference) return ''
  const [an1, mois1, jour1] = naissance.split('-').map(Number)
  const [an2, mois2, jour2] = reference.split('-').map(Number)
  let mois = (an2 - an1) * 12 + mois2 - mois1
  if (jour2 < jour1) mois -= 1 // Le mois en cours n'est pas encore révolu
  const ans = Math.floor(mois / 12)
  return `${ans} ${ans > 1 ? 'ans' : 'an'} et ${mois % 12} mois`
}

/** JJ-MM-AAAA, comme dans l'application Windows. */
export function dateFrancaise(date: string): string {
  return date ? date.split('-').reverse().join('-') : ''
}

export function accord(bilan: Bilan, masculin: string, feminin: string): string {
  return bilan.sexe === 'Homme' ? masculin : feminin
}

/** Éléments choisis, dans l'ordre de la liste du questionnaire, puis « autre ». */
export function dansLOrdre(liste: readonly string[], choisis: readonly string[], autre = ''): string[] {
  const resultat = liste.filter((element) => choisis.includes(element))
  if (autre.trim()) resultat.push(autre.trim())
  return resultat
}

/** Une ligne « - élément » par élément. */
export function enListe(elements: readonly string[]): string {
  return elements.map((element) => `- ${element}`).join('\n')
}

/** Une ligne « 1 - élément » par élément. */
export function numerotes(elements: readonly string[]): string {
  return elements.map((element, i) => `${i + 1} - ${element}`).join('\n')
}

/** Activités saisies séparées par des virgules. */
export function activitesSaisies(texte: string): string[] {
  return texte.split(',').map((activite) => activite.trim()).filter(Boolean)
}

/** Activités d'un domaine OT Hope cotées à ce niveau, dans l'ordre du questionnaire. */
export function activitesDuNiveau(bilan: Bilan, domaine: string, niveau: string): string[] {
  const reponses = bilan.otHope[domaine] ?? {}
  const definition = questionnaire.otHope.domaines.find((d) => d.id === domaine)
  return (definition?.activites ?? []).filter((activite) => reponses[activite] === niveau)
}

/** Activités d'un domaine faites avec aide ou difficulté : les objectifs possibles. */
export function activitesEnDifficulte(bilan: Bilan, domaine: string): string[] {
  return questionnaire.otHope.niveaux.flatMap((niveau) => activitesDuNiveau(bilan, domaine, niveau.id))
}

/** Objectifs d'un domaine encore valables (l'activité peut avoir été recotée « rien à signaler »). */
export function objectifsDuDomaine(bilan: Bilan, domaine: string): string[] {
  const possibles = activitesEnDifficulte(bilan, domaine)
  return (bilan.objectifs[domaine] ?? []).filter((objectif) => possibles.includes(objectif))
}

/** Objectifs finaux possibles : ceux des domaines, toutes catégories confondues. */
export function objectifsPossibles(bilan: Bilan): string[] {
  const tous = questionnaire.otHope.domaines.flatMap((domaine) => objectifsDuDomaine(bilan, domaine.id))
  return [...new Set(tous)]
}

function phrase(liste: readonly { libelle: string; phrase: string }[], libelle: string): string {
  return liste.find((element) => element.libelle === libelle)?.phrase ?? ''
}

export function lateralites(sexe: Sexe): string[] {
  return questionnaire.identite.lateralite[sexe]
}

/** Valeur de chaque champ {…} du modèle bilan.docx. */
export function champs(bilan: Bilan): Record<string, string> {
  const { identite, demande, suivis, scolarite, otHope, objectifs, amenagements } = questionnaire
  const valeurs: Record<string, string> = {
    il_elle: accord(bilan, 'il', 'elle'),
    Il_Elle: accord(bilan, 'Il', 'Elle'),
    ne_e: accord(bilan, 'né', 'née'),
    seul_e: accord(bilan, 'seul', 'seule'),
    type_bilan: bilan.trancheAge === 'Ado' ? accord(bilan, 'Adolescent', 'Adolescente') : 'Enfant',

    prenom: bilan.prenom.trim(),
    nom: bilan.nom.trim(),
    date_de_naissance: dateFrancaise(bilan.dateNaissance),
    age: calculerAge(bilan.dateNaissance, bilan.datePassation),
    date_de_passation: dateFrancaise(bilan.datePassation),
    classe: bilan.classe,
    type_etablissement: bilan.typeEtablissement,
    nom_etablissement: bilan.nomEtablissement.trim(),
    lateralite: lateralites(bilan.sexe)[bilan.lateralite] ?? '',
    mode_de_garde: bilan.modeDeGarde,
    fratrie: bilan.enfantUnique ? 'est enfant unique' : `a ${bilan.fratrie.trim()}`,
    entente: bilan.enfantUnique ? '' : `(${phrase(identite.entente, bilan.entente)})`,
    medecin_traitant: bilan.medecinTraitant.trim(),
    ville: bilan.ville.trim(),

    personne_demandeuse: bilan.personneDemandeuse,
    motifs: dansLOrdre(demande.motifs, bilan.motifs, bilan.autreMotif).join(', '),
    troubles: enListe(dansLOrdre(demande.troubles, bilan.troubles, bilan.autreTrouble)),
    professionnels: enListe(bilan.aucunProfessionnel
      ? ['aucun']
      : dansLOrdre(suivis.professionnels, Object.keys(bilan.professionnels))
          .map((professionnel) => `${professionnel} : ${bilan.professionnels[professionnel]}`)),
    dossier_mdph: bilan.dossierMdph,

    comportement_en_classe: enListe(dansLOrdre(scolarite.comportement, bilan.comportement)),
    difficultes_en_classe: enListe(dansLOrdre(scolarite.difficultes, bilan.difficultes)),
    matieres_preferees: dansLOrdre(scolarite.matieres, bilan.matieresPreferees, bilan.autreMatierePreferee).join(', '),
    matieres_moins_appreciees:
      dansLOrdre(scolarite.matieres, bilan.matieresDetestees, bilan.autreMatiereDetestee).join(', '),

    objectifs_finaux: numerotes(bilan.objectifsFinaux.filter((o) => objectifsPossibles(bilan).includes(o))),
    accord_parents: phrase(objectifs.accordParents, bilan.accordParents).replace('{prenom}', bilan.prenom.trim()),
    objectifs_parents: [
      numerotes(bilan.objectifsParents.filter((o) => objectifsPossibles(bilan).includes(o))),
      bilan.remarquesParents.trim() ? `Remarques des parents : ${bilan.remarquesParents.trim()}` : '',
    ].filter(Boolean).join('\n'),

    amenagements_scolaires: enListe(dansLOrdre(amenagements, bilan.amenagements)),
    activites_extra_scolaires: enListe(activitesSaisies(bilan.activitesExtraScolaires)),
    activites_temps_libre: enListe(activitesSaisies(bilan.activitesTempsLibre)),
    difficultes_loisirs: bilan.difficultesLoisirs.trim()
      ? `- difficultés pendant les loisirs : ${bilan.difficultesLoisirs.trim()}`
      : '',
  }
  // OT Hope : {niveau_domaine} (aide_maison…) et {objectifs_domaine}.
  for (const domaine of otHope.domaines) {
    for (const niveau of otHope.niveaux)
      valeurs[`${niveau.id}_${domaine.id}`] = enListe(activitesDuNiveau(bilan, domaine.id, niveau.id))
    valeurs[`objectifs_${domaine.id}`] = numerotes(objectifsDuDomaine(bilan, domaine.id))
  }
  return valeurs
}

/** Bilan_ergotherapie_<nom>_<prénom>_<mois>_<année>.docx, comme sous Windows. */
export function nomDuFichier(bilan: Bilan): string {
  const [annee, mois] = (bilan.datePassation || aujourdhui()).split('-').map(Number)
  const nomDuMois = new Intl.DateTimeFormat('fr-FR', { month: 'long' }).format(new Date(annee, mois - 1, 1))
  const morceau = (texte: string) => texte.trim().replace(/[\\/:*?"<>|]/g, '').replace(/\s+/g, '_')
  return ['Bilan_ergotherapie', morceau(bilan.nom), morceau(bilan.prenom), nomDuMois, annee]
    .filter(Boolean).join('_') + '.docx'
}
