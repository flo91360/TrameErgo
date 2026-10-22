// Questionnaire pré-bilan rempli en ligne par les parents (Google Forms). Le
// script formulaire/questionnaire-parents.gs, publié en application web, renvoie
// les réponses d'un enfant à partir de son nom ; elles ne sont reportées dans
// le bilan que si elles reprennent mot pour mot un choix de l'application.
import { computed, ref } from 'vue'
import { lateralites, questionnaire, type Bilan } from './bilan'

export interface Question {
  titre: string
  /** Texte, cases cochées (liste) ou, pour une grille, colonne choisie par ligne (null : ligne vide). */
  reponse: unknown
  /** Lignes d'une grille. */
  lignes?: string[]
}

export interface QuestionnaireParents {
  /** Date et heure d'envoi (ISO). */
  envoi: string
  questions: Question[]
}

export type Recherche =
  | { etat: 'trouve'; questionnaires: QuestionnaireParents[] }
  | { etat: 'absent' }
  | { etat: 'injoignable'; raison: string }

export interface Reglages {
  /** Adresse de l'application web du script (…/exec). */
  adresse: string
  cle: string
}

const CLE = 'trameergo.questionnaireParents'

function lireReglages(): Reglages {
  try {
    const enregistres: unknown = JSON.parse(localStorage.getItem(CLE) ?? '{}')
    const { adresse, cle } = (enregistres ?? {}) as Partial<Record<keyof Reglages, unknown>>
    return { adresse: typeof adresse === 'string' ? adresse : '', cle: typeof cle === 'string' ? cle : '' }
  } catch {
    return { adresse: '', cle: '' }
  }
}

/** Adresse et clé du script : propres à chaque appareil, jamais dans le code. */
export const reglages = ref<Reglages>(lireReglages())
export const configure = computed(() => !!reglages.value.adresse && !!reglages.value.cle)

export function enregistrerReglages(nouveaux: Reglages): void {
  reglages.value = { adresse: nouveaux.adresse.trim(), cle: nouveaux.cle.trim() }
  try {
    localStorage.setItem(CLE, JSON.stringify(reglages.value))
  } catch {
    // Stockage indisponible : les réglages valent pour cette session.
  }
}

/** Libellés égaux aux majuscules, accents, apostrophes et espaces près. */
export function semblable(texte: string): string {
  return texte.normalize('NFD').replace(/[̀-ͯ]/g, '').replace(/[’`]/g, "'")
    .toLowerCase().replace(/\s+/g, ' ').trim()
}

function estQuestionnaire(valeur: unknown): valeur is QuestionnaireParents {
  if (typeof valeur !== 'object' || valeur === null) return false
  const { envoi, questions } = valeur as Record<string, unknown>
  return typeof envoi === 'string' && Array.isArray(questions)
    && questions.every((q) => typeof q === 'object' && q !== null && typeof (q as Question).titre === 'string')
}

/** Questionnaires envoyés pour cet enfant, du plus récent au plus ancien. */
export async function chercher(prenom: string, nom: string, { adresse, cle } = reglages.value,
  delai = 15000): Promise<Recherche> {
  const url = new URL(adresse)
  url.search = new URLSearchParams({ cle, prenom: prenom.trim(), nom: nom.trim() }).toString()
  const abandon = new AbortController()
  const minuteur = setTimeout(() => abandon.abort(), delai)
  let donnees: unknown
  try {
    const reponse = await fetch(url, { signal: abandon.signal, cache: 'no-store' })
    if (!reponse.ok) return { etat: 'injoignable', raison: `le script a répondu ${reponse.status}` }
    donnees = await reponse.json()
  } catch {
    return { etat: 'injoignable', raison: 'pas de connexion, ou adresse du script incorrecte' }
  } finally {
    clearTimeout(minuteur)
  }
  const { erreur, reponses } = (donnees ?? {}) as { erreur?: unknown; reponses?: unknown }
  if (erreur === 'cle') return { etat: 'injoignable', raison: 'clé refusée par le script' }
  if (!Array.isArray(reponses)) return { etat: 'injoignable', raison: 'réponse du script illisible' }
  const questionnaires = reponses.filter(estQuestionnaire).sort((a, b) => b.envoi.localeCompare(a.envoi))
  return questionnaires.length ? { etat: 'trouve', questionnaires } : { etat: 'absent' }
}

function texte(reponse: unknown): string {
  return typeof reponse === 'string' ? reponse.trim() : ''
}

function cases(reponse: unknown): string[] {
  if (typeof reponse === 'string') return reponse.trim() ? [reponse.trim()] : []
  return Array.isArray(reponse) ? reponse.filter((r): r is string => typeof r === 'string' && !!r.trim()) : []
}

/** Le choix de la liste qui a ce libellé (aux majuscules et accents près). */
function choix(liste: readonly string[], reponse: string): string | undefined {
  return liste.find((element) => semblable(element) === semblable(reponse))
}

/** 12/03/2016, 12-03-2016, 12.03.2016 ou 2016-03-12 → 2016-03-12 ; sinon vide. */
export function dateDeNaissance(reponse: string): string {
  const francaise = reponse.trim().match(/^(\d{1,2})[/.-](\d{1,2})[/.-](\d{4})$/)
  const iso = reponse.trim().match(/^(\d{4})-(\d{2})-(\d{2})$/)
  const [annee, mois, jour] = francaise
    ? [francaise[3], francaise[2], francaise[1]]
    : iso ? [iso[1], iso[2], iso[3]] : []
  if (!annee) return ''
  const date = `${annee}-${mois.padStart(2, '0')}-${jour.padStart(2, '0')}`
  const verifiee = new Date(`${date}T00:00:00Z`)
  return !Number.isNaN(verifiee.getTime()) && verifiee.toISOString().startsWith(date) ? date : ''
}

/** Une ligne « Question : réponse » par question répondue, pour l'encadré « Réponses des parents ». */
export function enLignes(reponses: QuestionnaireParents): string[] {
  return reponses.questions.flatMap((question) => {
    if (question.lignes && Array.isArray(question.reponse)) {
      const cotees = question.lignes
        .map((ligne, i) => [ligne, (question.reponse as unknown[])[i]])
        .filter(([, colonne]) => typeof colonne === 'string' && colonne)
        .map(([ligne, colonne]) => `${ligne} : ${colonne}`)
      return cotees.length ? [`${question.titre} : ${cotees.join(' ; ')}`] : []
    }
    const valeur = cases(question.reponse).join(', ')
    return valeur ? [`${question.titre} : ${valeur}`] : []
  })
}

/**
 * Bilan pré-rempli avec les réponses des parents. Seules les réponses qui
 * reprennent un choix de l'application (activité, niveau, classe…) au même
 * libellé sont reportées ; le reste n'apparaît que dans l'encadré.
 */
export function preRemplir(depart: Bilan, reponses: QuestionnaireParents): { bilan: Bilan; activites: number } {
  const bilan: Bilan = JSON.parse(JSON.stringify(depart))
  const { identite, demande, scolarite, otHope, amenagements } = questionnaire
  const question = (titre: string) => reponses.questions.find((q) => semblable(q.titre) === semblable(titre))?.reponse

  const naissance = dateDeNaissance(texte(question('Date de naissance')))
  if (naissance) bilan.dateNaissance = naissance

  const lateralite = texte(question('Latéralité'))
  const position = (['Femme', 'Homme'] as const)
    .map((sexe) => lateralites(sexe).findIndex((l) => semblable(l) === semblable(lateralite)))
    .find((i) => i >= 0)
  if (lateralite && position !== undefined) bilan.lateralite = position

  const simples: [keyof Bilan & ('classe' | 'modeDeGarde' | 'personneDemandeuse' | 'dossierMdph'), string,
    readonly string[]][] = [
    ['classe', 'Classe', identite.classes],
    ['modeDeGarde', 'Mode de garde (si parents séparés)', identite.modesDeGarde],
    ['personneDemandeuse', "Qui est à l'origine de la demande de réalisation du bilan (médecin traitant ou "
      + 'autre professionnel de santé, instituteurs/professeurs…) ?', demande.personnesDemandeuses],
    ['dossierMdph', 'Dossier MDPH', demande.dossierMdph],
  ]
  for (const [cle, titre, liste] of simples) {
    const trouve = choix(liste, texte(question(titre)))
    if (trouve) bilan[cle] = trouve
  }

  const multiples: [keyof Bilan & ('troubles' | 'matieresPreferees' | 'matieresDetestees' | 'difficultes'
    | 'amenagements'), string[], readonly string[]][] = [
    ['troubles', ['Quel est le motif du Bilan, quelles problématiques rencontrez-vous ?',
      'A ce jour, quel(s) trouble(s) ont été diagnostiqués ?'], demande.troubles],
    ['matieresPreferees', ['Matières préférées'], scolarite.matieres],
    ['matieresDetestees', ['Matières moins appréciées'], scolarite.matieres],
    ['difficultes', ["Qu'est-ce qui est difficile en classe ?"], scolarite.difficultes],
    ['amenagements', ['Y a t il eu des aménagements ?'], amenagements],
  ]
  for (const [cle, titres, liste] of multiples) {
    const trouves = titres.flatMap((titre) => cases(question(titre)))
      .map((reponse) => choix(liste, reponse)).filter((c): c is string => !!c)
    bilan[cle] = [...new Set([...bilan[cle], ...trouves])]
  }

  const textes: [keyof Bilan & ('activitesExtraScolaires' | 'activitesTempsLibre' | 'difficultesLoisirs'),
    string][] = [
    ['activitesExtraScolaires', 'Quelles sont les activités extra-scolaire ? A quelle fréquence ?'],
    ['activitesTempsLibre', 'Quelles sont les activités de temps libre ?'],
    ['difficultesLoisirs', 'Y a t il des difficultés lors des loisirs ?'],
  ]
  for (const [cle, titre] of textes) {
    const valeur = texte(question(titre))
    if (valeur) bilan[cle] = valeur
  }

  // Grilles : chaque ligne qui porte le libellé d'une activité OT Hope, quel
  // que soit son domaine, reçoit le niveau de la colonne cochée.
  let activites = 0
  for (const grille of reponses.questions) {
    if (!grille.lignes || !Array.isArray(grille.reponse)) continue
    grille.lignes.forEach((ligne, i) => {
      const colonne = (grille.reponse as unknown[])[i]
      if (typeof colonne !== 'string') return
      const niveau = otHope.niveaux.find((n) => semblable(n.libelle) === semblable(colonne))
      const neutre = semblable(otHope.neutre) === semblable(colonne)
      const domaine = otHope.domaines.find((d) => choix(d.activites, ligne))
      if (!domaine || (!niveau && !neutre)) return
      const activite = choix(domaine.activites, ligne)!
      const cotations = { ...(bilan.otHope[domaine.id] ?? {}) }
      if (niveau) cotations[activite] = niveau.id
      else delete cotations[activite]
      bilan.otHope = { ...bilan.otHope, [domaine.id]: cotations }
      activites += 1
    })
  }

  bilan.reponsesParents = enLignes(reponses)
  return { bilan, activites }
}
