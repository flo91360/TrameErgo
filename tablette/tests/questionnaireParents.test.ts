// Questionnaire des parents : recherche par nom auprès du script Google et
// pré-remplissage, seulement pour les réponses au même libellé que l'application.
import { readFileSync } from 'node:fs'
import { afterEach, describe, expect, it, vi } from 'vitest'
import { nouveauBilan, questionnaire } from '../src/bilan'
import {
  chercher, coordonnees, dateDeNaissance, enLignes, lienDeLiaison, lireLien, preRemplir, QUESTIONS, semblable,
  type QuestionnaireParents,
} from '../src/questionnaireParents'

const script = (nom: string) => readFileSync(new URL(`../../formulaire/${nom}`, import.meta.url), 'utf8')

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
    expect(bilan.amenagements).toEqual(['AESH'])
    expect(bilan.activitesTempsLibre).toBe('Lecture, vélo')
    expect(bilan.fratrie).toBe('')
    expect(bilan.sexe).toBe(nouveauBilan().sexe)
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

  it('suit le formulaire : mêmes questions, et des grilles aux niveaux de l\'application', () => {
    const creation = script('creer-formulaire.gs')
    for (const titre of Object.values(QUESTIONS)) expect(creation, titre).toContain(titre)
    const niveaux = creation.match(/const NIVEAUX = \[(.*)\];/)?.[1].split(',').map((n) => n.trim().slice(1, -1))
    expect(niveaux).toEqual([questionnaire.otHope.neutre, ...questionnaire.otHope.niveaux.map((n) => n.libelle)])
    // Le script de lecture cherche le nom dans la question du formulaire.
    const lecture = script('questionnaire-parents.gs')
    const question = lecture.match(/const QUESTION_NOM = "(.*)";/)?.[1]
    expect(creation).toContain(`texte(form, "${question}")`)
    // Ou le nom découpé (« Nom » et « Prénom » sous le titre « Enfant »).
    expect(lecture).toContain("const PARTIE_ENFANT = 'Enfant';")
  })
})
