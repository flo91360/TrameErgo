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
  /** Titre de l'encadré ou de la section où se trouve la question (« Parent 1 »…). */
  partie?: string
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

/** Lien de liaison affiché par le script (lienDeLiaison) : adresse de l'application web, puis #cle=…. */
export function lienDeLiaison({ adresse, cle }: Reglages): string {
  return adresse && cle ? `${adresse}#cle=${encodeURIComponent(cle)}` : ''
}

/** Réglages tirés d'un lien de liaison collé (null : ce n'en est pas un). */
export function lireLien(lien: string): Reglages | null {
  let url: URL
  try {
    url = new URL(lien.trim())
  } catch {
    return null
  }
  const cle = new URLSearchParams(url.hash.slice(1)).get('cle')?.trim()
  if (url.protocol !== 'https:' || !url.pathname.endsWith('/exec') || !cle) return null
  url.hash = ''
  url.search = ''
  return { adresse: url.toString(), cle }
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

/** Intitulés des questions du formulaire (formulaire/creer-formulaire.gs) reprises dans le bilan. */
export const QUESTIONS = {
  dateNaissance: 'Date de naissance',
  lateralite: 'Latéralité',
  classe: 'Classe',
  modeDeGarde: 'Mode de garde (si parents séparés)',
  personneDemandeuse: "Qui est à l'origine de la demande de réalisation du bilan (médecin traitant ou autre "
    + 'professionnel de santé, instituteurs/professeurs…) ?',
  dossierMdph: 'Dossier MDPH',
  motifs: 'Quel est le motif du Bilan, quelles problématiques rencontrez-vous ?',
  troubles: 'A ce jour, quel(s) trouble(s) ont été diagnostiqués ?',
  matieresPreferees: 'Matières préférées',
  matieresDetestees: 'Matières moins appréciées',
  difficultes: "Qu'est-ce qui est difficile en classe ?",
  amenagements: 'Y a t il eu des aménagements ?',
  activitesExtraScolaires: 'Quelles sont les activités extra-scolaire ? A quelle fréquence ?',
  activitesTempsLibre: 'Quelles sont les activités de temps libre ?',
  difficultesLoisirs: 'Y a t il des difficultés lors des loisirs ?',
} as const

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
  const morceaux = francaise ? [francaise[3], francaise[2], francaise[1]] : iso ? [iso[1], iso[2], iso[3]] : null
  if (!morceaux) return ''
  const [annee, mois, jour] = morceaux
  const date = `${annee}-${mois.padStart(2, '0')}-${jour.padStart(2, '0')}`
  const verifiee = new Date(`${date}T00:00:00Z`)
  return !Number.isNaN(verifiee.getTime()) && verifiee.toISOString().startsWith(date) ? date : ''
}

/** Une ligne « Question : réponse » par question répondue, pour l'encadré « Réponses des parents ». */
export function enLignes(reponses: QuestionnaireParents): string[] {
  // « Nom » sous « Enfant », « Parent 1 »… : l'intitulé seul ne dit pas de qui il s'agit.
  const titres = reponses.questions.map((question) => question.titre)
  const libelle = (question: Question) =>
    question.partie && titres.indexOf(question.titre) !== titres.lastIndexOf(question.titre)
      ? `${question.partie} - ${question.titre}`
      : question.titre
  return reponses.questions.flatMap((question) => {
    if (question.lignes && Array.isArray(question.reponse)) {
      const cotees = question.lignes
        .map((ligne, i) => [ligne, (question.reponse as unknown[])[i]])
        .filter(([, colonne]) => typeof colonne === 'string' && colonne)
        .map(([ligne, colonne]) => `${ligne} : ${colonne}`)
      return cotees.length ? [`${libelle(question)} : ${cotees.join(' ; ')}`] : []
    }
    const valeur = cases(question.reponse).join(', ')
    return valeur ? [`${libelle(question)} : ${valeur}`] : []
  })
}

/** Partie de la fiche patient d'après le titre de l'encadré (« Parent 1 » → parent1), sinon null. */
function groupe(partie: string): string | null {
  const titre = semblable(partie)
  const parent = titre.match(/parent\s*(\d)/)
  if (parent) return `parent${parent[1]}`
  if (/medecin/.test(titre)) return 'medecin'
  if (/famille/.test(titre)) return 'famille'
  if (/enfant/.test(titre)) return 'enfant'
  return null
}

/** « Adresse mail » → adresse_mail, « Mode de garde (si parents séparés) » → mode_de_garde. */
function information(titre: string): string {
  const cle = semblable(titre.replace(/\([^)]*\)/g, '').replace(/\s*:\s*$/, ''))
    .replace(/[^a-z0-9]+/g, '_').replace(/^_|_$/g, '')
  return cle === 'fraterie' ? 'fratrie' : cle
}

/**
 * Réponses texte des encadrés Enfant, Médecin traitant, Parent 1, Parent 2 et
 * Famille, par « partie.information » (parent1.telephone, medecin.ville…) :
 * l'intitulé seul (« Nom ») ne dit pas de qui il s'agit.
 */
export function coordonnees(reponses: QuestionnaireParents): Record<string, string> {
  const resultat: Record<string, string> = {}
  for (const question of reponses.questions) {
    const partie = question.partie ? groupe(question.partie) : null
    const valeur = cases(question.reponse).join(', ')
    if (!partie || question.lignes || !valeur) continue
    resultat[`${partie}.${information(question.titre)}`] = valeur
  }
  return resultat
}

/**
 * Bilan pré-rempli avec les réponses des parents. Seules les réponses qui
 * reprennent un choix de l'application (activité, niveau, classe…) au même
 * libellé sont reportées ; le reste n'apparaît que dans l'encadré.
 */
export function preRemplir(depart: Bilan, reponses: QuestionnaireParents): { bilan: Bilan; activites: number } {
  const bilan: Bilan = JSON.parse(JSON.stringify(depart))
  const { identite, demande, scolarite, otHope, amenagements } = questionnaire
  // Intitulé du formulaire de l'ergo : « Date de naissance : », avec deux-points.
  const intitule = (titre: string) => semblable(titre.replace(/\s*:\s*$/, ''))
  const question = (titre: string) => reponses.questions.find((q) => intitule(q.titre) === intitule(titre))?.reponse

  const naissance = dateDeNaissance(texte(question(QUESTIONS.dateNaissance)))
  if (naissance) bilan.dateNaissance = naissance

  const lateralite = texte(question(QUESTIONS.lateralite))
  const position = (['Femme', 'Homme'] as const)
    .map((sexe) => lateralites(sexe).findIndex((l) => semblable(l) === semblable(lateralite)))
    .find((i) => i >= 0)
  if (lateralite && position !== undefined) bilan.lateralite = position

  const simples: [keyof Bilan & ('classe' | 'modeDeGarde' | 'personneDemandeuse' | 'dossierMdph'), string,
    readonly string[]][] = [
    ['classe', QUESTIONS.classe, identite.classes],
    ['modeDeGarde', QUESTIONS.modeDeGarde, identite.modesDeGarde],
    ['personneDemandeuse', QUESTIONS.personneDemandeuse, demande.personnesDemandeuses],
    ['dossierMdph', QUESTIONS.dossierMdph, demande.dossierMdph],
  ]
  for (const [cle, titre, liste] of simples) {
    const trouve = choix(liste, texte(question(titre)))
    if (trouve) bilan[cle] = trouve
  }

  const multiples: [keyof Bilan & ('troubles' | 'matieresPreferees' | 'matieresDetestees' | 'difficultes'
    | 'amenagements'), string[], readonly string[]][] = [
    // Les motifs du formulaire (« difficulté d'écriture »…) sont des troubles de l'application.
    ['troubles', [QUESTIONS.motifs, QUESTIONS.troubles], demande.troubles],
    ['matieresPreferees', [QUESTIONS.matieresPreferees], scolarite.matieres],
    ['matieresDetestees', [QUESTIONS.matieresDetestees], scolarite.matieres],
    ['difficultes', [QUESTIONS.difficultes], scolarite.difficultes],
    ['amenagements', [QUESTIONS.amenagements], amenagements],
  ]
  for (const [cle, titres, liste] of multiples) {
    const trouves = titres.flatMap((titre) => cases(question(titre)))
      .map((reponse) => choix(liste, reponse)).filter((c): c is string => !!c)
    bilan[cle] = [...new Set([...bilan[cle], ...trouves])]
  }

  const textes: [keyof Bilan & ('activitesExtraScolaires' | 'activitesTempsLibre' | 'difficultesLoisirs'),
    string][] = [
    ['activitesExtraScolaires', QUESTIONS.activitesExtraScolaires],
    ['activitesTempsLibre', QUESTIONS.activitesTempsLibre],
    ['difficultesLoisirs', QUESTIONS.difficultesLoisirs],
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

  // Médecin traitant découpé en « Nom » et « Ville » sous son titre.
  bilan.coordonnees = coordonnees(reponses)
  if (bilan.coordonnees['medecin.nom']) bilan.medecinTraitant = bilan.coordonnees['medecin.nom']
  if (bilan.coordonnees['medecin.ville']) bilan.ville = bilan.coordonnees['medecin.ville']

  bilan.reponsesParents = enLignes(reponses)
  return { bilan, activites }
}
