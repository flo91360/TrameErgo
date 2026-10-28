// Questionnaire des parents : recherche par nom auprès du script Google et
// pré-remplissage, seulement pour les réponses au même libellé que l'application.
import { readFileSync } from 'node:fs'
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'
import { afterEach, describe, expect, it, vi } from 'vitest'
import { AUTRE_AMENAGEMENT, champs, libellesCaractere, nouveauBilan, phraseCaractereParents, questionnaire } from '../src/bilan'
import { remplirModele } from '../src/generer'
import {
  activiteOtHope, chercher, coordonnees, dateDeNaissance, enLignes, EQUIVALENCES, lienDeLiaison, lireLien,
  OPTIONS_FORMULAIRE, preRemplir, QUESTIONS, rapproche, semblable, type QuestionnaireParents,
} from '../src/questionnaireParents'

const script = (nom: string) => readFileSync(new URL(`../../formulaire/${nom}`, import.meta.url), 'utf8')

/** Chaînes entre guillemets d'un extrait de formulaire/creer-formulaire.gs. */
function chaines(extrait: string | undefined): string[] {
  return [...(extrait ?? '').matchAll(/'([^']*)'|"([^"]*)"/g)].map((m) => m[1] ?? m[2])
}

/** Choix d'une question à cases de creer-formulaire.gs. */
function optionsDe(creation: string, titre: string): string[] {
  const debut = creation.indexOf(`cases(form, "${titre}", [`) >= 0
    ? creation.indexOf(`cases(form, "${titre}", [`) : creation.indexOf(`cases(form, '${titre}', [`)
  expect(debut, titre).toBeGreaterThanOrEqual(0)
  const liste = creation.slice(creation.indexOf('[', debut) + 1, creation.indexOf(']', debut))
  return chaines(liste)
}

/** Lignes d'une grille d'activités de creer-formulaire.gs (ACTIVITES_QUOTIDIEN…). */
function lignesDe(creation: string, constante: string): string[] {
  return chaines(creation.match(new RegExp(`const ${constante} = \\[([^\\]]*)\\];`))?.[1])
}

/** Réponse fictive, au format renvoyé par formulaire/questionnaire-parents.gs. */
const reponse: QuestionnaireParents = {
  envoi: '2026-10-12T08:30:00.000Z',
  questions: [
    { titre: "Nom et Prénom de l'enfant", reponse: 'PETIT Léa' },
    { titre: 'Date de naissance', reponse: '14/10/2015' },
    { titre: 'Latéralité', reponse: 'Gaucher' },
    { titre: 'Classe', reponse: 'CE2' },
    { titre: 'Fraterie', reponse: '1 frère' },
    { titre: 'Dossier MDPH', reponse: 'NON' },
    { titre: QUESTIONS.motifs, reponse: ["difficulté d'écriture", 'difficulté de visualisation dans l\'espace'] },
    { titre: QUESTIONS.troubles, reponse: ['Dyslexie', 'Dyspraxie / trouble de l\'acquisition des coordination'] },
    { titre: 'Matières préférées', reponse: ['Français', 'Mathématique'] },
    { titre: 'Y a t il eu des aménagements ?', reponse: ['AESH', 'Polycopier fournis dans certaines matières'] },
    {
      titre: "Niveau d'aide pour chaque activité",
      lignes: ['balayer', 'étendre le linge', 'Faire son cartable', 'passer l\'aspirateur', 'ranger sa chambre'],
      reponse: ['Avec aide', 'avec grande DIFFICULTÉ', 'Avec aide', null, 'Rien à signaler'],
    },
    {
      titre: "Niveau d'aide pour chaque activité",
      lignes: ['Découper', 'Gommer'],
      reponse: ['Avec difficulté', 'Très grand effort'],
    },
    { titre: QUESTIONS.activitesTempsLibre, reponse: 'Lecture, vélo' },
  ],
}

describe('questionnaire des parents', () => {
  afterEach(() => vi.unstubAllGlobals())

  it('compare les libellés aux majuscules, accents et espaces près', () => {
    expect(semblable('  Étendre  le LINGE ')).toBe(semblable('etendre le linge'))
    expect(semblable('S’occuper des animaux')).toBe(semblable("s'occuper des animaux"))
    expect(semblable('Faire son cartable')).not.toBe(semblable('Préparer mon cartable'))
  })

  it('lit le lien de liaison affiché par le script', () => {
    const reglages = { adresse: 'https://script.google.com/macros/s/AKfy-1/exec', cle: '3f2a-9c1e' }
    expect(lienDeLiaison(reglages)).toBe('https://script.google.com/macros/s/AKfy-1/exec#cle=3f2a-9c1e')
    expect(lireLien(`  ${lienDeLiaison(reglages)} `)).toEqual(reglages)
    expect(lireLien('https://script.google.com/macros/s/AKfy-1/exec')).toBeNull()
    expect(lireLien('http://script.google.com/macros/s/AKfy-1/exec#cle=k')).toBeNull()
    expect(lireLien('https://script.google.com/macros/s/AKfy-1/dev#cle=k')).toBeNull()
    expect(lireLien('3f2a-9c1e')).toBeNull()
  })

  it('lit les dates de naissance saisies librement', () => {
    expect(dateDeNaissance('14/10/2015')).toBe('2015-10-14')
    expect(dateDeNaissance('4-3-2016')).toBe('2016-03-04')
    expect(dateDeNaissance('2016-03-04')).toBe('2016-03-04')
    expect(dateDeNaissance('31/02/2016')).toBe('')
    expect(dateDeNaissance('mars 2016')).toBe('')
  })

  it('ne reporte que les activités et niveaux au même libellé que l\'application', () => {
    const depart = { ...nouveauBilan(), otHope: { maison: { 'Ranger sa chambre': 'aide' } } }
    const { bilan, activites } = preRemplir(depart, reponse)
    expect(bilan.otHope.maison).toEqual({ Balayer: 'aide', 'Etendre le linge': 'grande_difficulte' })
    expect(bilan.otHope.ecole).toEqual({ Découper: 'difficulte' })
    // Balayer, Etendre le linge, Ranger sa chambre (rien à signaler), Découper.
    expect(activites).toBe(4)
  })

  it('reporte les choix qui existent dans l\'application, et rien d\'autre', () => {
    const { bilan } = preRemplir(nouveauBilan(), reponse)
    expect(bilan.dateNaissance).toBe('2015-10-14')
    expect(bilan.lateralite).toBe(1)
    expect(bilan.classe).toBe('CE2')
    expect(bilan.dossierMdph).toBe('')
    expect(bilan.troubles).toEqual(["Difficulté d'écriture", 'Dyslexie'])
    expect(bilan.matieresPreferees).toEqual(['Français'])
    expect(bilan.amenagements).toEqual(['AESH', 'Polycopiés donnés'])
    expect(bilan.autreAmenagement).toBe('')
    expect(bilan.activitesTempsLibre).toBe('Lecture, vélo')
    expect(bilan.fratrie).toBe('')
    expect(bilan.sexe).toBe(nouveauBilan().sexe)
  })

  it('coche les troubles des raisons du bilan, et reporte les autres réponses en « Autre trouble »', () => {
    const avecRaisons: QuestionnaireParents = {
      envoi: reponse.envoi,
      questions: [
        { titre: QUESTIONS.raisonsTroubles, reponse: ['tsa', 'Dysgraphie', 'Hypersensibilité au bruit', 'Dysgraphie'] },
      ],
    }
    const { bilan } = preRemplir(nouveauBilan(), avecRaisons)
    expect(bilan.troubles).toEqual(['TSA', 'Dysgraphie'])
    expect(bilan.autreTrouble).toBe('Hypersensibilité au bruit')
    // Déjà saisi : pas de doublon ; toutes cochées : « Autre trouble » reste tel quel.
    expect(preRemplir({ ...nouveauBilan(), autreTrouble: 'Hypersensibilité au bruit' }, avecRaisons).bilan.autreTrouble)
      .toBe('Hypersensibilité au bruit')
    expect(preRemplir({ ...nouveauBilan(), autreTrouble: 'Trouble visuel' }, avecRaisons).bilan.autreTrouble)
      .toBe('Trouble visuel, Hypersensibilité au bruit')
    const toutesCochees = { envoi: reponse.envoi, questions: [{ titre: QUESTIONS.raisonsTroubles, reponse: ['TSA'] }] }
    expect(preRemplir(nouveauBilan(), toutesCochees).bilan.autreTrouble).toBe('')
    // Les autres questions de troubles ne remplissent pas « Autre trouble ».
    expect(preRemplir(nouveauBilan(), reponse).bilan.autreTrouble).toBe('')
    // Le Word écrit les troubles cochés, puis la réponse libre.
    const modele = readFileSync(new URL('../../contenu/bilan.docx', import.meta.url))
    const word = new Docxtemplater(new PizZip(remplirModele(modele, champs(bilan))),
      { paragraphLoop: true, linebreaks: true }).getFullText()
    expect(word).toContain('- Dysgraphie')
    expect(word).toContain('- TSA')
    expect(word).toContain('- Hypersensibilité au bruit')
  })

  it('coche le caractère selon les parents, en gardant les sélections déjà faites', () => {
    const avecCaractere: QuestionnaireParents = {
      envoi: reponse.envoi,
      questions: [
        { titre: QUESTIONS.caractere, reponse: ['curieux', 'Têtu', 'joyeuse', "peu motivé par l'effort", 'Rêveur'] },
      ],
    }
    const { bilan } = preRemplir(nouveauBilan(), avecCaractere)
    // Exactement les items cochés qui existent dans l'application, sans « Rêveur », absent de l'application.
    expect(bilan.caractereParents).toEqual(['curieux', 'têtu', 'joyeux', "peu motivé par l'effort"])
    expect(bilan.caractereEnfant).toEqual([])
    expect(bilan.reponsesParents).toContain(
      `${QUESTIONS.caractere} : curieux, Têtu, joyeuse, peu motivé par l'effort, Rêveur`)
    // Déjà cochés : gardés, sans doublon ; « Selon l'enfant » n'est pas touché.
    const depart = { ...nouveauBilan(), caractereParents: ['calme', 'curieux'], caractereEnfant: ['bavard'] }
    const complete = preRemplir(depart, avecCaractere).bilan
    expect(complete.caractereParents).toEqual(['calme', 'curieux', 'têtu', 'joyeux', "peu motivé par l'effort"])
    expect(complete.caractereEnfant).toEqual(['bavard'])
    // Intitulé sans la précision entre parenthèses, et rien de coché : rien ne change.
    const ancien = { envoi: reponse.envoi, questions: [{ titre: 'Actuellement votre enfant est :', reponse: ['Sociable'] }] }
    expect(preRemplir(nouveauBilan(), ancien).bilan.caractereParents).toEqual(['sociable'])
    expect(preRemplir(depart, reponse).bilan.caractereParents).toEqual(['calme', 'curieux'])
    // Le Word reprend les traits, accordés au sexe.
    expect(phraseCaractereParents({ ...bilan, prenom: 'Léa', sexe: 'Femme' }))
      .toBe("D'après ses parents, Léa est curieuse, têtue, joyeuse et peu motivée par l'effort.")
  })

  it('garde toutes les réponses pour l\'encadré « Réponses des parents »', () => {
    const lignes = enLignes(reponse)
    expect(lignes).toContain('Fraterie : 1 frère')
    expect(lignes).toContain(`${QUESTIONS.troubles} : Dyslexie, Dyspraxie / trouble de l'acquisition des coordination`)
    expect(lignes).toContain("Niveau d'aide pour chaque activité : balayer : Avec aide ; étendre le linge : "
      + 'avec grande DIFFICULTÉ ; Faire son cartable : Avec aide ; ranger sa chambre : Rien à signaler')
    expect(preRemplir(nouveauBilan(), reponse).bilan.reponsesParents).toEqual(lignes)
  })

  it('précise de qui parle une question au même intitulé qu\'une autre', () => {
    const lignes = enLignes({
      envoi: reponse.envoi,
      questions: [
        { titre: 'Nom', partie: 'Enfant', reponse: 'Petit' },
        { titre: 'Date de naissance', partie: 'Enfant', reponse: '2016-10-14' },
        { titre: 'Nom', partie: 'Parent 1', reponse: 'Petit' },
        { titre: 'Profession', partie: 'Parent 1', reponse: 'Infirmière' },
      ],
    })
    expect(lignes).toEqual([
      'Enfant - Nom : Petit', 'Date de naissance : 2016-10-14', 'Parent 1 - Nom : Petit', 'Profession : Infirmière',
    ])
    expect(dateDeNaissance('2016-10-14')).toBe('2016-10-14')
  })

  it('range les réponses par partie, et reprend le médecin', () => {
    const formulaire: QuestionnaireParents = {
      envoi: reponse.envoi,
      questions: [
        { titre: 'Nom', partie: 'Enfant', reponse: 'Petit' },
        { titre: 'Nom', partie: 'Médecin traitant', reponse: 'Durand' },
        { titre: 'Ville', partie: 'Médecin traitant', reponse: 'Massy' },
        { titre: 'Nom', partie: 'Parent 1', reponse: 'Petit' },
        { titre: 'Adresse mail', partie: 'Parent 1', reponse: 'a.petit@exemple.fr' },
        { titre: 'Téléphone :', partie: 'Parent 2', reponse: '06 12 34 56 78' },
        { titre: 'Profession', partie: 'Parent 2', reponse: '' },
        { titre: 'Fraterie', partie: 'Famille', reponse: '1 frère' },
        { titre: 'Mode de garde (si parents séparés)', partie: 'Famille', reponse: 'Garde alternée' },
        { titre: 'Classe', partie: 'Bilan', reponse: 'CE2' },
        { titre: "Niveau d'aide", partie: 'Enfant', lignes: ['Balayer'], reponse: ['Avec aide'] },
      ],
    }
    expect(coordonnees(formulaire)).toEqual({
      'enfant.nom': 'Petit', 'medecin.nom': 'Durand', 'medecin.ville': 'Massy', 'parent1.nom': 'Petit',
      'parent1.adresse_mail': 'a.petit@exemple.fr', 'parent2.telephone': '06 12 34 56 78',
      'famille.fratrie': '1 frère', 'famille.mode_de_garde': 'Garde alternée',
    })
    const { bilan } = preRemplir(nouveauBilan(), formulaire)
    expect([bilan.medecinTraitant, bilan.ville]).toEqual(['Durand', 'Massy'])
  })

  it('reprend la personne à l\'origine de la demande, sauf une réponse sans équivalent', () => {
    const avec = (valeur: string) => preRemplir(nouveauBilan(), {
      envoi: reponse.envoi,
      questions: [{ titre: 'Qui est à l’origine de la demande de réalisation du bilan en ergothérapie ?', reponse: valeur }],
    }).bilan.personneDemandeuse
    expect(avec('la mère')).toBe('la mère')
    expect(avec("l'enseignant")).toBe("l'enseignant")
    expect(avec("l'orthoptiste")).toBe('')
    expect(avec('Autre')).toBe('')
    expect(preRemplir(nouveauBilan(), reponse).bilan.personneDemandeuse).toBe('')
  })

  it('reconnaît les intitulés suivis de deux-points', () => {
    const { bilan } = preRemplir(nouveauBilan(), {
      envoi: reponse.envoi,
      questions: [{ titre: 'Date de naissance :', partie: 'Enfant', reponse: '2016-10-14' }, { titre: 'Classe :', reponse: 'CE2' }],
    })
    expect(bilan.dateNaissance).toBe('2016-10-14')
    expect(bilan.classe).toBe('CE2')
  })

  it('cherche les questionnaires d\'un enfant auprès du script, avec la clé', async () => {
    const appel = vi.fn(async (_url: URL) => new Response(JSON.stringify({
      reponses: [{ ...reponse, envoi: '2026-09-01T10:00:00.000Z' }, reponse],
    })))
    vi.stubGlobal('fetch', appel)
    const resultat = await chercher(' Léa ', 'Petit', { adresse: 'https://script.google.com/macros/s/x/exec', cle: 'k' })
    const url = appel.mock.calls[0][0]
    expect(url.searchParams.get('cle')).toBe('k')
    expect(url.searchParams.get('prenom')).toBe('Léa')
    expect(url.searchParams.get('nom')).toBe('Petit')
    expect(resultat.etat).toBe('trouve')
    if (resultat.etat === 'trouve')
      expect(resultat.questionnaires.map((q) => q.envoi)).toEqual([reponse.envoi, '2026-09-01T10:00:00.000Z'])
  })

  it('distingue l\'absence de questionnaire d\'un script injoignable ou d\'une clé refusée', async () => {
    const reglages = { adresse: 'https://script.google.com/macros/s/x/exec', cle: 'k' }
    vi.stubGlobal('fetch', async () => new Response(JSON.stringify({ reponses: [] })))
    expect(await chercher('Léa', 'Petit', reglages)).toEqual({ etat: 'absent' })
    vi.stubGlobal('fetch', async () => new Response(JSON.stringify({ erreur: 'cle' })))
    expect(await chercher('Léa', 'Petit', reglages)).toMatchObject({ etat: 'injoignable', raison: /clé/ })
    vi.stubGlobal('fetch', async () => { throw new TypeError('Failed to fetch') })
    expect(await chercher('Léa', 'Petit', reglages)).toMatchObject({ etat: 'injoignable' })
  })

  it('reprend les activités renommées d\'après le document « modification TramErgo »', () => {
    const lignes: [string, string | undefined][] = [
      ['Enfiler ses vêtement (dans le bon sens)', 'Enfiler ses vêtement (dans le bon sens)'],
      ['cuisiner un plat simple', 'Cuisiner un plat simple'],
      ['Manipuler les boutons', 'Manipuler les boutons (chemise/ pantalon)'],
      ['se couper les ongles', 'Me couper les ongles'],
      ['Se coiffer', 'Me coiffer'],
      ["S'endormir facilement", "S'endormir facilement"],
      ['Préparer son cartable', 'Préparer son cartable'],
      ['Tracer un rond/ carré/ triangle à main levée', 'Tracer un rond/ carré/ triangle à main levée'],
      ['jouer/ discuter dans la cours de récréation avec des amis',
        'Jouer/ discuter dans la cours de récréation avec des amis'],
      ['lancer une balle', 'Lancer une balle'],
      ["s'exprimer (écrit, oral)", "S'exprimer (écrit, oral)"],
      // « Préparer mon cartable » (école) et « Préparer son cartable » (maison) : ambigu, pas repris.
      ['Préparer ton cartable', undefined],
      ['Prendre sa douche seul(e)', undefined],
    ]
    for (const [ligne, activite] of lignes) expect(activiteOtHope(ligne), ligne).toBe(activite)
    const { bilan, activites } = preRemplir(nouveauBilan(), {
      envoi: reponse.envoi,
      questions: [{
        titre: "Niveau d'aide pour chaque activité",
        lignes: ['Manipuler les boutons', 'se couper les ongles', 'Lecture voix haute', 'enfiler des perles'],
        reponse: ['Avec aide', 'Avec difficulté', 'Avec grande difficulté', 'Avec aide'],
      }],
    })
    expect(activites).toBe(4)
    expect(bilan.otHope).toEqual({
      maison: { 'Manipuler les boutons (chemise/ pantalon)': 'aide', 'Me couper les ongles': 'difficulte' },
      ecole: { 'Lecture voix haute': 'grande_difficulte' },
      loisirs: { 'Enfiler des perles': 'aide' },
    })
  })

  it('rapproche les libellés sans précision entre parenthèses ni « me »/« se »', () => {
    expect(rapproche('Me couper les ongles')).toBe(rapproche('se couper les ongles'))
    expect(rapproche("M'installer à ma place")).toBe(rapproche("s'installer à sa place"))
    expect(rapproche('Ecrire vite et bien (qualité et quantité)')).toBe(rapproche('Ecrire vite et bien'))
    expect(rapproche('Ecrire vite (quantité)')).not.toBe(rapproche('Ecrire vite et bien'))
    expect(rapproche('Mémoriser')).toBe('memoriser')
  })

  it('coche les difficultés en classe du formulaire, et reporte « Autre »', () => {
    const { bilan } = preRemplir({ ...nouveauBilan(), prenom: 'Léa' }, {
      envoi: reponse.envoi,
      questions: [{ titre: QUESTIONS.difficultes, reponse: [...OPTIONS_FORMULAIRE.difficultes, 'Copier au tableau'] }],
    })
    expect(bilan.difficultes).toEqual([
      'la concentration toute la journée', 'la concentration le matin', "la concentration l'après-midi",
      'Ecrire vite et bien (qualité et quantité)', "S'organiser", "Douleur à l'écriture", 'Participer',
    ])
    expect(bilan.autreDifficulte).toBe('Copier au tableau')
    expect(champs(bilan).difficultes_en_classe).toBe([
      '- la concentration toute la journée', '- la concentration le matin', "- la concentration l'après-midi",
      '- Ecrire vite et bien (qualité et quantité)', "- Douleur à l'écriture", "- S'organiser", '- Participer',
      '- Copier au tableau',
    ].join('\n'))
  })

  it('coche les aménagements du formulaire, et recopie « Autre » dans l\'aménagement scolaire libre', () => {
    const { bilan } = preRemplir({ ...nouveauBilan(), autreAmenagement: 'Pupitre adapté' }, {
      envoi: reponse.envoi,
      questions: [{
        titre: QUESTIONS.amenagements,
        reponse: ['Polycopier fournis dans certaines matières', "réduction du nombre d'exercice lors des évaluations",
          'adaptation des barèmes', 'Texte plus grand et/ou bien espacé', 'polycopier à trou', 'Tiers-temps',
          'Place au premier rang', 'pupitre adapté'],
      }],
    })
    expect(bilan.amenagements).toEqual(['Polycopiés donnés', "Moins d'exercices", 'Adaptation des barèmes',
      'Texte plus grand et/ou bien espacé', 'Polycopier à trou', AUTRE_AMENAGEMENT])
    // « Tiers-temps » est un choix du formulaire, sans équivalent exact : ni coché, ni recopié.
    expect(bilan.autreAmenagement).toBe('Pupitre adapté\nPlace au premier rang')
    const sansAutre = preRemplir(nouveauBilan(), { envoi: reponse.envoi,
      questions: [{ titre: QUESTIONS.amenagements, reponse: ['AESH', 'Tiers-temps'] }] }).bilan
    expect(sansAutre.amenagements).toEqual(['AESH'])
    expect(sansAutre.autreAmenagement).toBe('')
  })

  it('remplit les activités extra-scolaires, de temps libre et les difficultés pendant les loisirs', () => {
    const { bilan } = preRemplir(nouveauBilan(), {
      envoi: reponse.envoi,
      questions: [
        { titre: QUESTIONS.activitesExtraScolaires, reponse: 'judo, piano' },
        { titre: QUESTIONS.activitesTempsLibre, reponse: 'dessin' },
        { titre: QUESTIONS.difficultesLoisirs, reponse: 'se fatigue vite' },
      ],
    })
    expect([bilan.activitesExtraScolaires, bilan.activitesTempsLibre, bilan.difficultesLoisirs])
      .toEqual(['judo, piano', 'dessin', 'se fatigue vite'])
  })

  it('connaît les choix du formulaire et les équivalences demandées', () => {
    const creation = script('creer-formulaire.gs')
    expect(optionsDe(creation, QUESTIONS.difficultes)).toEqual(OPTIONS_FORMULAIRE.difficultes)
    expect(optionsDe(creation, QUESTIONS.amenagements)).toEqual(OPTIONS_FORMULAIRE.amenagements)
    const listes = [...questionnaire.scolarite.difficultes, ...questionnaire.amenagements]
    for (const [formulaire, application] of Object.entries(EQUIVALENCES)) {
      expect([...OPTIONS_FORMULAIRE.difficultes, ...OPTIONS_FORMULAIRE.amenagements]).toContain(formulaire)
      expect(listes).toContain(application)
    }
    // Les choix des difficultés en classe ont tous leur équivalent dans l'application.
    const { bilan } = preRemplir(nouveauBilan(), { envoi: reponse.envoi,
      questions: [{ titre: QUESTIONS.difficultes, reponse: [...OPTIONS_FORMULAIRE.difficultes] }] })
    expect(bilan.difficultes).toHaveLength(OPTIONS_FORMULAIRE.difficultes.length)
    // Les lignes des grilles du formulaire sont bien lues par le test.
    for (const grille of ['ACTIVITES_QUOTIDIEN', 'ACTIVITES_ECOLE', 'ACTIVITES_LOISIRS'])
      expect(lignesDe(creation, grille).length, grille).toBeGreaterThan(30)
  })

  it('suit le formulaire : mêmes questions, et des grilles aux niveaux de l\'application', () => {
    const creation = script('creer-formulaire.gs')
    for (const titre of Object.values(QUESTIONS)) expect(creation, titre).toContain(titre)
    const niveaux = creation.match(/const NIVEAUX = \[(.*)\];/)?.[1].split(',').map((n) => n.trim().slice(1, -1))
    expect(niveaux).toEqual([questionnaire.otHope.neutre, ...questionnaire.otHope.niveaux.map((n) => n.libelle)])
    // Options de la personne demandeuse : celles de l'application, « Autre » en texte libre.
    const personnes = creation.match(/const PERSONNES_DEMANDEUSES = \[([^\]]*)\];/)?.[1]
      .split(/,\s*/).map((p) => p.trim()).filter(Boolean).map((p) => p.slice(1, -1).replace(/\\'/g, "'"))
    expect([...(personnes ?? []), 'Autre']).toEqual(questionnaire.demande.personnesDemandeuses)
    expect(creation).toContain(`choix(form, "${QUESTIONS.personneDemandeuse}", PERSONNES_DEMANDEUSES, true)`)
    // Raisons du bilan : cases aux libellés des troubles de l'application.
    const troubles = creation.match(/const TROUBLES = \[([^\]]*)\];/)?.[1]
      .split(/,\s*/).map((t) => t.trim()).filter(Boolean).map((t) => t.slice(1, -1))
    expect(troubles).toEqual(questionnaire.demande.troubles)
    expect(creation).toContain(`cases(form, '${QUESTIONS.raisonsTroubles}', TROUBLES)`)
    // Caractère : cases aux libellés de l'application, dans le même ordre.
    const caractere = creation.match(/const CARACTERE = \[([^\]]*)\];/)?.[1]
      .split(/,\s*/).map((c) => c.trim()).filter(Boolean).map((c) => c.slice(1, -1))
    expect(caractere).toEqual(libellesCaractere())
    expect(creation).toContain(`cases(form, '${QUESTIONS.caractere}', CARACTERE)`)
    // Le script de lecture cherche le nom dans la question du formulaire.
    const lecture = script('questionnaire-parents.gs')
    const question = lecture.match(/const QUESTION_NOM = "(.*)";/)?.[1]
    expect(creation).toContain(`texte(form, "${question}")`)
    // Ou le nom découpé (« Nom » et « Prénom » sous le titre « Enfant »).
    expect(lecture).toContain("const PARTIE_ENFANT = 'Enfant';")
  })
})
