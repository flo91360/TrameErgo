// Réponses du questionnaire et champs {…} du modèle contenu/bilan.docx.
import questionnaire from '@contenu/questionnaire.json'

export { questionnaire }

export type Sexe = 'Femme' | 'Homme'
export type TrancheAge = 'Enfant' | 'Ado'

/** Thérapeute « Autre », saisi en texte libre, et la fréquence de son suivi. */
export interface AutreProfessionnel {
  nom: string
  frequence: string
}

/** Nombre maximal de thérapeutes « Autre ». */
export const NOMBRE_AUTRES_PROFESSIONNELS = 3

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
  /** Indice dans identite/lateralite/<sexe> : le libellé s'accorde au sexe (null : non renseignée). */
  lateralite: number | null
  modeDeGarde: string
  enfantUnique: boolean
  fratrie: string
  entente: string
  medecinTraitant: string
  ville: string
  personneDemandeuse: string
  /** Personne demandeuse saisie en texte libre, quand « Autre » est choisi. */
  autrePersonneDemandeuse: string
  motifs: string[]
  autreMotif: string
  troubles: string[]
  autreTrouble: string
  dossierMdph: string
  aucunProfessionnel: boolean
  /** Professionnel suivi → fréquence du suivi. */
  professionnels: Record<string, string>
  /** Autres thérapeutes (« Autre »), au plus NOMBRE_AUTRES_PROFESSIONNELS ; vide : « Autre » n'est pas coché. */
  autresProfessionnels: AutreProfessionnel[]
  comportement: string[]
  difficultes: string[]
  matieresPreferees: string[]
  autreMatierePreferee: string
  matieresDetestees: string[]
  autreMatiereDetestee: string
  /** Caractère de l'enfant selon ses parents : libellés de questionnaire.caractere. */
  caractereParents: string[]
  /** Caractère de l'enfant selon lui-même : libellés (pas les formulations pour l'enfant) de questionnaire.caractere. */
  caractereEnfant: string[]
  /** Domaine OT Hope → activité → identifiant du niveau (absente : rien à signaler). */
  otHope: Record<string, Record<string, string>>
  /** Domaine OT Hope → objectifs choisis, dans l'ordre du choix. */
  objectifs: Record<string, string[]>
  objectifsFinaux: string[]
  accordParents: string
  objectifsParents: string[]
  remarquesParents: string
  amenagements: string[]
  /** Aménagements scolaires précis, en texte libre (une ligne par aménagement). */
  autreAmenagement: string
  activitesExtraScolaires: string
  activitesTempsLibre: string
  difficultesLoisirs: string
  /** Réponses du questionnaire des parents, « Question : réponse », montrées pendant la saisie. */
  reponsesParents: string[]
  /** Réponses des parents rangées par partie du questionnaire, pour la fiche patient (« parent1.nom » → « Martin »). */
  coordonnees: Record<string, string>
}

export const NOMBRE_OBJECTIFS = 5

export function aujourdhui(date = new Date()): string {
  const deux = (n: number) => String(n).padStart(2, '0')
  return `${date.getFullYear()}-${deux(date.getMonth() + 1)}-${deux(date.getDate())}`
}

// Les choix sans réponse évidente commencent vides (« — à renseigner — ») :
// une valeur par défaut irait dans le bilan sans avoir été choisie.
export function nouveauBilan(date = new Date()): Bilan {
  return {
    sexe: 'Femme',
    trancheAge: 'Enfant',
    prenom: '',
    nom: '',
    dateNaissance: '',
    datePassation: aujourdhui(date),
    classe: '',
    typeEtablissement: '',
    nomEtablissement: '',
    lateralite: null,
    modeDeGarde: '',
    enfantUnique: false,
    fratrie: '',
    entente: '',
    medecinTraitant: '',
    ville: '',
    personneDemandeuse: '',
    autrePersonneDemandeuse: '',
    motifs: [],
    autreMotif: '',
    troubles: [],
    autreTrouble: '',
    dossierMdph: '',
    aucunProfessionnel: false,
    professionnels: {},
    autresProfessionnels: [],
    comportement: [],
    difficultes: [],
    matieresPreferees: [],
    autreMatierePreferee: '',
    matieresDetestees: [],
    autreMatiereDetestee: '',
    caractereParents: [],
    caractereEnfant: [],
    otHope: {},
    objectifs: {},
    objectifsFinaux: [],
    accordParents: '',
    objectifsParents: [],
    remarquesParents: '',
    amenagements: [],
    autreAmenagement: '',
    activitesExtraScolaires: '',
    activitesTempsLibre: '',
    difficultesLoisirs: '',
    reponsesParents: [],
    coordonnees: {},
  }
}

/** Date de naissance postérieure à la date de passation : l'âge ne peut pas être calculé. */
export function datesIncoherentes(bilan: Bilan): boolean {
  return !!bilan.dateNaissance && !!bilan.datePassation && bilan.dateNaissance > bilan.datePassation
}

/** Âge en années et mois révolus à la date de référence (dates AAAA-MM-JJ). */
export function calculerAge(naissance: string, reference: string): string {
  if (!naissance || !reference) return ''
  const [an1, mois1, jour1] = naissance.split('-').map(Number)
  const [an2, mois2, jour2] = reference.split('-').map(Number)
  let mois = (an2 - an1) * 12 + mois2 - mois1
  if (jour2 < jour1) mois -= 1 // Le mois en cours n'est pas encore révolu
  if (mois < 0) return '' // Naissance après la référence : signalé par datesIncoherentes
  const ans = Math.floor(mois / 12)
  return `${ans} ${ans > 1 ? 'ans' : 'an'} et ${mois % 12} mois`
}

/** JJ-MM-AAAA. */
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

/** Objectifs (finaux, des parents) encore possibles : ceux qui iront dans le bilan. */
export function objectifsRetenus(bilan: Bilan, choisis: readonly string[]): string[] {
  const possibles = objectifsPossibles(bilan)
  return choisis.filter((objectif) => possibles.includes(objectif))
}

export type TypeCaractere = 'qualite' | 'defaut'

/** Libellés du caractère, dans l'ordre du questionnaire (d'un seul type si précisé). */
export function libellesCaractere(type?: TypeCaractere): string[] {
  return questionnaire.caractere.filter((item) => !type || item.type === type).map((item) => item.libelle)
}

/** Libellé accordé au sexe de l'enfant (« curieux » → « curieuse »). */
export function caractereAccorde(bilan: Bilan, libelle: string): string {
  const item = questionnaire.caractere.find((element) => element.libelle === libelle)
  return item ? accord(bilan, item.libelle, item.feminin) : libelle
}

/** « a », « a et b », « a, b et c ». */
export function enumeration(elements: readonly string[]): string {
  if (elements.length < 2) return elements.join('')
  return `${elements.slice(0, -1).join(', ')} et ${elements[elements.length - 1]}`
}

/** Phrase du caractère selon les parents (vide si rien n'est coché). */
export function phraseCaractereParents(bilan: Bilan): string {
  const traits = dansLOrdre(libellesCaractere(), bilan.caractereParents).map((l) => caractereAccorde(bilan, l))
  return traits.length ? `D'après ses parents, ${bilan.prenom.trim()} est ${enumeration(traits)}.` : ''
}

/** Phrase de l'auto-évaluation de l'enfant : qualités puis défauts cochés (vide si rien n'est coché). */
export function phraseCaractereEnfant(bilan: Bilan): string {
  const partie = (type: TypeCaractere, singulier: string) => {
    const traits = dansLOrdre(libellesCaractere(type), bilan.caractereEnfant).map((l) => caractereAccorde(bilan, l))
    return traits.length ? `comme ${singulier}${traits.length > 1 ? 's' : ''} d'être ${enumeration(traits)}` : ''
  }
  const parties = [partie('qualite', 'qualité'), partie('defaut', 'défaut')].filter(Boolean)
  return parties.length
    ? `Lors de son auto-évaluation, ${bilan.prenom.trim()} se reconnaît ${parties.join(', et ')}.`
    : ''
}

function phrase(liste: readonly { libelle: string; phrase: string }[], libelle: string): string {
  return liste.find((element) => element.libelle === libelle)?.phrase ?? ''
}

export function lateralites(sexe: Sexe): string[] {
  return questionnaire.identite.lateralite[sexe]
}

/** Case des aménagements scolaires qui renvoie au texte libre : elle n'est pas écrite dans le bilan. */
export const AUTRE_AMENAGEMENT = 'Autre / aménagement scolaire'

/** Aménagements scolaires du bilan : ceux de la liste, puis une ligne par ligne du texte libre. */
export function amenagementsScolaires(bilan: Bilan): string[] {
  const liste = questionnaire.amenagements.filter((amenagement) => amenagement !== AUTRE_AMENAGEMENT)
  const precis = bilan.autreAmenagement.split('\n').map((ligne) => ligne.trim()).filter(Boolean)
  return [...dansLOrdre(liste, bilan.amenagements), ...precis]
}

/** Personne demandeuse qui renvoie au texte libre : c'est le texte saisi qui est écrit dans le bilan. */
export const AUTRE_PERSONNE_DEMANDEUSE = 'Autre'

/** Personne demandeuse du bilan : le choix de la liste, ou le texte libre pour « Autre ». */
export function personneDemandeuse(bilan: Bilan): string {
  return bilan.personneDemandeuse === AUTRE_PERSONNE_DEMANDEUSE
    ? bilan.autrePersonneDemandeuse.trim()
    : bilan.personneDemandeuse
}

type Manquants = (bilan: Bilan) => string[]

function presents(liste: (string | false)[]): string[] {
  return liste.filter(Boolean) as string[]
}

/**
 * Réponses obligatoires de chaque écran : tant qu'il en manque, on ne passe
 * pas à l'écran suivant. Le modèle Word peut ainsi écrire ses phrases sans
 * conditions ({#champ}…{/champ}), et rester lisible.
 */
export const obligatoires: Record<'patient' | 'demande' | 'suivis' | 'objectifs' | 'amenagements', Manquants> = {
  patient: (bilan) => presents([
    !bilan.prenom.trim() && 'le prénom',
    !bilan.nom.trim() && 'le nom',
    !bilan.dateNaissance && 'la date de naissance',
    !bilan.datePassation && 'la date de passation',
    datesIncoherentes(bilan) && 'une date de naissance avant la date de passation',
    !bilan.classe && 'la classe',
    !bilan.typeEtablissement && "l'établissement",
    !bilan.nomEtablissement.trim() && "le nom de l'établissement",
    bilan.lateralite === null && 'la latéralité',
    !bilan.modeDeGarde && 'le mode de garde',
    !bilan.enfantUnique && !bilan.fratrie.trim() && 'la fratrie (ou « Enfant unique »)',
    !bilan.enfantUnique && !bilan.entente && "l'entente dans la fratrie",
    !bilan.medecinTraitant.trim() && 'le médecin traitant',
    !bilan.ville.trim() && 'la ville du médecin traitant',
  ]),
  demande: (bilan) => presents([
    !bilan.personneDemandeuse && 'la personne demandeuse',
    bilan.personneDemandeuse === AUTRE_PERSONNE_DEMANDEUSE && !bilan.autrePersonneDemandeuse.trim()
      && 'la personne demandeuse (Autre)',
    !bilan.dossierMdph && 'le dossier MDPH',
    !bilan.motifs.length && !bilan.autreMotif.trim() && 'au moins un motif',
  ]),
  suivis: (bilan) => {
    if (bilan.aucunProfessionnel) return []
    if (!Object.keys(bilan.professionnels).length && !bilan.autresProfessionnels.length)
      return ['les professionnels qui suivent l\'enfant (ou « Aucun »)']
    return [
      ...dansLOrdre(questionnaire.suivis.professionnels, Object.keys(bilan.professionnels))
        .filter((professionnel) => !bilan.professionnels[professionnel])
        .map((professionnel) => `la fréquence de suivi (${professionnel})`),
      ...bilan.autresProfessionnels.flatMap((autre, i) => presents([
        !autre.nom.trim() && `le nom ou la profession de l'autre thérapeute n° ${i + 1}`,
        !autre.frequence && `la fréquence de suivi (${autre.nom.trim() || `autre thérapeute n° ${i + 1}`})`,
      ])),
    ]
  },
  objectifs: (bilan) => presents([
    objectifsPossibles(bilan).length > 0 && !objectifsRetenus(bilan, bilan.objectifsFinaux).length
      && 'au moins un objectif final',
    !bilan.accordParents && "l'accord des parents",
  ]),
  amenagements: (bilan) => presents([
    bilan.amenagements.includes(AUTRE_AMENAGEMENT) && !bilan.autreAmenagement.trim()
      && "l'aménagement scolaire « Autre » à préciser",
  ]),
}

/** Toutes les réponses obligatoires encore absentes : le bilan Word ne peut pas être créé. */
export function aRenseigner(bilan: Bilan): string[] {
  return Object.values(obligatoires).flatMap((manquants) => manquants(bilan))
}

/** Un bilan entamé : il a au moins un prénom ou un nom. */
export function entame(bilan: Bilan): boolean {
  return !!(bilan.prenom.trim() || bilan.nom.trim())
}

/**
 * Réévaluation : nouveau bilan du même enfant, daté du jour. Il garde
 * l'identité, l'environnement et les coordonnées de la famille (à vérifier) ; la classe et toute la partie
 * clinique sont à refaire.
 */
export function reevaluation(ancien: Bilan, date = new Date()): Bilan {
  const { sexe, trancheAge, prenom, nom, dateNaissance, typeEtablissement, nomEtablissement, lateralite,
    modeDeGarde, enfantUnique, fratrie, entente, medecinTraitant, ville, coordonnees } = ancien
  return {
    ...nouveauBilan(date),
    sexe, trancheAge, prenom, nom, dateNaissance, typeEtablissement, nomEtablissement, lateralite,
    modeDeGarde, enfantUnique, fratrie, entente, medecinTraitant, ville, coordonnees: { ...coordonnees },
  }
}

/** Professionnels de la liste suivis, « professionnel : fréquence », dans l'ordre du questionnaire. */
function professionnelsSuivis(bilan: Bilan): string[] {
  return dansLOrdre(questionnaire.suivis.professionnels, Object.keys(bilan.professionnels))
    .map((professionnel) => [professionnel, bilan.professionnels[professionnel]].filter(Boolean).join(' : '))
}

/**
 * {autre} : autres thérapeutes, à la suite de {professionnels} dans le même
 * paragraphe du modèle. Vide si « Autre » n'est pas coché : aucune trace dans le Word.
 */
function autresSuivis(bilan: Bilan): string {
  if (bilan.aucunProfessionnel) return ''
  const autres = bilan.autresProfessionnels
    .filter((autre) => autre.nom.trim())
    .map((autre) => [autre.nom.trim(), autre.frequence].filter(Boolean).join(' : '))
  if (!autres.length) return ''
  return (professionnelsSuivis(bilan).length ? '\n' : '') + enListe(autres)
}

/** Valeur de chaque champ {…} du modèle bilan.docx. */
export function champs(bilan: Bilan): Record<string, string> {
  const { identite, demande, scolarite, otHope, objectifs } = questionnaire
  // Les réponses obligatoires (voir obligatoires) sont toujours remplies : le
  // modèle les écrit sans condition. Les listes facultatives peuvent être vides.
  const entente = phrase(identite.entente, bilan.entente)
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
    lateralite: bilan.lateralite === null ? '' : lateralites(bilan.sexe)[bilan.lateralite] ?? '',
    mode_de_garde: bilan.modeDeGarde,
    fratrie: bilan.enfantUnique
      ? 'est enfant unique'
      : [`a ${bilan.fratrie.trim()}`, entente && `(${entente})`].filter(Boolean).join(' '),
    medecin_traitant: bilan.medecinTraitant.trim(),
    ville: bilan.ville.trim(),

    personne_demandeuse: personneDemandeuse(bilan),
    motifs: dansLOrdre(demande.motifs, bilan.motifs, bilan.autreMotif).join(', '),
    troubles: enListe(dansLOrdre(demande.troubles, bilan.troubles, bilan.autreTrouble)),
    professionnels: enListe(bilan.aucunProfessionnel ? ['aucun'] : professionnelsSuivis(bilan)),
    autre: autresSuivis(bilan),
    dossier_mdph: bilan.dossierMdph,

    comportement_en_classe: enListe(dansLOrdre(scolarite.comportement, bilan.comportement)),
    difficultes_en_classe: enListe(dansLOrdre(scolarite.difficultes, bilan.difficultes)),
    matieres_preferees: dansLOrdre(scolarite.matieres, bilan.matieresPreferees, bilan.autreMatierePreferee).join(', '),
    matieres_moins_appreciees:
      dansLOrdre(scolarite.matieres, bilan.matieresDetestees, bilan.autreMatiereDetestee).join(', '),

    // Étape facultative : une phrase sans case cochée reste vide.
    caractere_parents: phraseCaractereParents(bilan),
    caractere_enfant: phraseCaractereEnfant(bilan),

    objectifs_finaux: numerotes(objectifsRetenus(bilan, bilan.objectifsFinaux)),
    accord_parents: phrase(objectifs.accordParents, bilan.accordParents).replace('{prenom}', bilan.prenom.trim()),
    objectifs_parents: [
      numerotes(objectifsRetenus(bilan, bilan.objectifsParents)),
      bilan.remarquesParents.trim() ? `Remarques des parents : ${bilan.remarquesParents.trim()}` : '',
    ].filter(Boolean).join('\n'),

    amenagements_scolaires: enListe(amenagementsScolaires(bilan)),
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

/** Morceau de nom de fichier : sans caractère interdit sous Windows, espaces en « _ ». */
function morceau(texte: string): string {
  return texte.trim().replace(/[\\/:*?"<>|]/g, '').replace(/\s+/g, '_')
}

/** Bilan_ergotherapie_<nom>_<prénom>_<mois>_<année>.docx. */
export function nomDuFichier(bilan: Bilan): string {
  const [annee, mois] = (bilan.datePassation || aujourdhui()).split('-').map(Number)
  const nomDuMois = new Intl.DateTimeFormat('fr-FR', { month: 'long' }).format(new Date(annee, mois - 1, 1))
  return ['Bilan_ergotherapie', morceau(bilan.nom), morceau(bilan.prenom), nomDuMois, annee]
    .filter(Boolean).join('_') + '.docx'
}

/** Fiche_patient_<nom>_<prénom>.docx. */
export function nomDeLaFiche(bilan: Bilan): string {
  return ['Fiche_patient', morceau(bilan.nom), morceau(bilan.prenom)].filter(Boolean).join('_') + '.docx'
}

/** Bilan_….docx → Bilan_…_2.docx : copie enregistrée à côté d'un bilan existant. */
export function copieNumerotee(nom: string, numero: number): string {
  return nom.replace(/\.docx$/, '') + `_${numero}.docx`
}
