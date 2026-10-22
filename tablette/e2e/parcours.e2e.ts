import { readFile } from 'node:fs/promises'
import { expect, test, type Page } from '@playwright/test'
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'

async function etape(page: Page, titre: string | RegExp) {
  await page.getByRole('navigation', { name: 'Étapes du bilan' }).getByRole('button', { name: titre }).click()
}

async function brouillon(page: Page) {
  return page.evaluate(() => JSON.parse(localStorage.getItem('trameergo.brouillon') ?? '{}').bilan)
}

/** Brouillon enregistré avant l'ouverture : Patient et Demande remplis. */
async function avecBrouillon(page: Page, reponses: Record<string, unknown> = {}) {
  await page.evaluate((r) => localStorage.setItem('trameergo.brouillon', JSON.stringify({ version: 2, bilan: {
    prenom: 'Léa', nom: 'Petit', dateNaissance: '2015-10-14', datePassation: '2026-10-14', classe: 'CE2',
    typeEtablissement: "l'école", nomEtablissement: 'Jules Ferry', lateralite: 0, modeDeGarde: 'avec sa mère',
    enfantUnique: true, medecinTraitant: 'Durand', ville: 'Massy', personneDemandeuse: 'la mère',
    dossierMdph: 'Aucun', autreMotif: 'Lenteur', ...r,
  } })), reponses)
  await page.reload()
}

const accueil = (page: Page) => page.getByRole('heading', { name: 'Que voulez-vous faire ?' })

async function nouveauBilan(page: Page) {
  await page.getByRole('button', { name: /Nouveau bilan/ }).tap()
  await expect(page.getByRole('heading', { name: 'Nouveau bilan' })).toBeVisible()
  await page.getByRole('button', { name: 'Commencer le bilan' }).tap()
  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
}

const SCRIPT = 'https://script.google.com/macros/s/essai/exec'

/** Script du questionnaire des parents relié, qui connaît le questionnaire de Léa Petit. */
async function avecQuestionnaire(page: Page) {
  await page.route(`${SCRIPT}?*`, (route) => {
    const parametres = new URL(route.request().url()).searchParams
    const lea = parametres.get('cle') === 'cle-essai' && parametres.get('prenom') === 'Léa'
      && parametres.get('nom') === 'Petit'
    return route.fulfill({ headers: { 'Access-Control-Allow-Origin': '*' }, json: { reponses: lea ? [{
      envoi: '2026-10-12T08:30:00.000Z',
      questions: [
        { titre: "Nom et Prénom de l'enfant", reponse: 'Petit Léa' },
        { titre: 'Classe', reponse: 'CE2' },
        { titre: 'Fraterie', reponse: '1 frère' },
        { titre: "Niveau d'aide pour chaque activité", lignes: ['balayer', 'Faire son cartable'],
          reponse: ['Avec aide', 'Avec difficulté'] },
      ],
    }] : [] } })
  })
  await page.evaluate((adresse) => localStorage.setItem('trameergo.questionnaireParents',
    JSON.stringify({ adresse, cle: 'cle-essai' })), SCRIPT)
  await page.reload()
}

test.beforeEach(async ({ page }) => {
  await page.goto('./')
  await expect(accueil(page)).toBeVisible()
})

test('l\'accueil propose les actions, sans bilan en cours à reprendre', async ({ page }) => {
  await expect(page.getByRole('button', { name: /Nouveau bilan/ })).toBeEnabled()
  await expect(page.getByRole('button', { name: /Reprendre le bilan en cours/ })).toBeDisabled()
  await page.getByRole('button', { name: /Historique des bilans/ }).tap()
  await expect(page.getByText(/Aucun bilan pour l'instant/)).toBeVisible()
  await page.getByRole('button', { name: 'Accueil' }).tap()
  await expect(accueil(page)).toBeVisible()
})

test('toucher le titre d\'un choix ne change pas la réponse', async ({ page }) => {
  await nouveauBilan(page)
  await page.getByRole('radio', { name: 'Garçon' }).tap()
  // Le texte « Sexe » est en haut à gauche de son bloc, au-dessus des segments.
  await page.locator('.champ', { hasText: 'Sexe' }).tap({ position: { x: 5, y: 5 } })
  expect((await brouillon(page)).sexe).toBe('Homme')
})

test('on ne passe à l\'écran suivant qu\'avec les réponses obligatoires', async ({ page }) => {
  await nouveauBilan(page)
  const etapes = page.getByRole('navigation', { name: 'Étapes du bilan' })
  await expect(etapes.getByRole('button', { name: 'Demande' })).toBeDisabled()
  await page.getByLabel('Prénom').fill('Lucas')
  await page.getByRole('button', { name: 'Suivant' }).tap()
  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
  await expect(page.getByRole('alert')).toContainText('Pour continuer, renseigner : le nom, ')
})

test('un bilan rempli de bout en bout donne le Word attendu et va dans l\'historique', async ({ page }) => {
  await nouveauBilan(page)
  await page.getByRole('radio', { name: 'Garçon' }).tap()
  await page.getByLabel('Prénom').fill('Lucas')
  await page.getByLabel('Nom', { exact: true }).fill('Martin')
  await page.getByLabel('Date de naissance').fill('2012-03-12')
  await page.getByLabel('Date de passation').fill('2026-10-14')
  await expect(page.getByText('Âge à la passation : 14 ans et 7 mois')).toBeVisible()
  await page.getByLabel('Classe').selectOption('4ème')
  await page.getByRole('combobox', { name: /^Établissement/ }).selectOption('le collège')
  await page.getByLabel("Nom de l'établissement").fill('Jean Moulin')
  await page.getByLabel('Latéralité').selectOption({ label: 'gaucher' })
  await page.getByLabel('Mode de garde').selectOption('en garde alternée')
  await page.getByLabel('Fratrie').fill('1 sœur')
  await page.getByRole('radiogroup', { name: 'Entente' }).getByRole('radio', { name: 'Bonne' }).tap()
  await page.getByLabel('Médecin traitant').fill('Durand')
  await page.getByLabel('Ville').fill('Massy')
  await page.getByRole('button', { name: 'Suivant' }).tap()

  await expect(page.getByRole('heading', { name: 'Demande' })).toBeVisible()
  await page.getByLabel('Personne demandeuse').selectOption('la mère')
  await page.getByLabel('Dossier MDPH').selectOption('Aucun')
  await page.getByLabel('Autre motif').fill('Lenteur en classe')
  await page.getByRole('button', { name: 'Dysgraphie' }).tap()
  await page.getByRole('button', { name: 'Suivant' }).tap()

  await expect(page.getByRole('heading', { name: 'Suivis' })).toBeVisible()
  await page.getByLabel('Aucun', { exact: true }).tap()

  await etape(page, /OT Hope : Activités de vie quotidienne/)
  await page.getByRole('radiogroup', { name: 'Faire mes lacets' })
    .getByRole('radio', { name: 'Avec difficulté' }).tap()
  await expect(page.getByText('1 activité signalée.')).toBeVisible()

  await etape(page, 'Objectifs')
  await page.locator('.carte', { hasText: 'Objectifs de Lucas : activités de vie quotidienne' })
    .getByRole('button', { name: 'Faire mes lacets' }).tap()
  await page.locator('.carte', { hasText: 'Objectifs finaux' }).getByRole('button', { name: 'Faire mes lacets' }).tap()
  await page.getByRole('radiogroup', { name: 'Accord des parents' }).getByRole('radio', { name: 'Oui' }).tap()

  await etape(page, /^\d+\s*Bilan$/)
  const [telechargement] = await Promise.all([
    page.waitForEvent('download'),
    page.getByRole('button', { name: 'Créer le bilan Word' }).tap(),
  ])
  expect(telechargement.suggestedFilename()).toBe('Bilan_ergotherapie_Martin_Lucas_octobre_2026.docx')

  const docx = await readFile(await telechargement.path())
  const texte = new Docxtemplater(new PizZip(docx), { paragraphLoop: true, linebreaks: true }).getFullText()
  expect(texte).toContain('Je rencontre Lucas né le 12-03-2012, il a 14 ans et 7 mois. Il est en 4ème dans '
    + 'le collège Jean Moulin. Lucas est gaucher. Il vit en garde alternée, il a 1 sœur (bonne entente entre eux).')
  expect(texte).toMatch(/Dr Durand, à Massy\./)
  expect(texte).toContain('le bilan a été demandé par la mère.')
  expect(texte).toMatch(/Motif\s: Lenteur en classe\./)
  expect(texte).toContain('1 - Faire mes lacets')
  expect(texte).not.toMatch(/[{}]|\(\)| \./)

  // Historique : réévaluation du même enfant, identité reprise, classe à revoir.
  await page.getByRole('button', { name: "Retour à l'accueil" }).tap()
  await page.getByRole('button', { name: /Historique des bilans/ }).tap()
  await expect(page.getByText('Lucas Martin')).toBeVisible()
  await expect(page.getByText(/Passation le 14-10-2026/)).toBeVisible()
  await page.getByRole('button', { name: 'Réévaluation' }).tap()
  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
  await expect(page.getByLabel('Prénom')).toHaveValue('Lucas')
  await expect(page.getByLabel('Ville')).toHaveValue('Massy')
  await expect(page.getByLabel('Classe')).toHaveValue('')
  expect((await brouillon(page)).otHope).toEqual({})
})

test('le bilan en cours est repris depuis l\'accueil, puis remplacé par un nouveau', async ({ page }) => {
  await nouveauBilan(page)
  await page.getByLabel('Prénom').fill('Léa')
  await page.reload()
  await page.getByRole('button', { name: /Reprendre le bilan en cours/ }).tap()
  await expect(page.getByLabel('Prénom')).toHaveValue('Léa')

  await page.getByRole('button', { name: 'Accueil' }).tap()
  page.once('dialog', (dialogue) => dialogue.accept())
  await nouveauBilan(page)
  await expect(page.getByLabel('Prénom')).toHaveValue('')
})

test('un ancien brouillon signale les réponses disparues du questionnaire', async ({ page }) => {
  await page.evaluate(() => localStorage.setItem('trameergo.brouillon', JSON.stringify({
    prenom: 'Léa', classe: 'CM3', entente: 'Bonne', troubles: ['TSA', 'Trouble disparu'],
  })))
  await page.reload()
  await page.getByRole('button', { name: /Reprendre le bilan en cours/ }).tap()
  await expect(page.getByText(/ont été retirées du bilan : CM3 \(Classe\), Trouble disparu \(Troubles\)\./))
    .toBeVisible()
  await expect(page.getByLabel('Classe')).toHaveValue('')
  expect((await brouillon(page)).troubles).toEqual(['TSA'])
  await page.reload()
  await page.getByRole('button', { name: /Reprendre le bilan en cours/ }).tap()
  await expect(page.getByText(/ont été retirées/)).toHaveCount(0)
})

test('un professionnel choisi n\'a pas de fréquence d\'office', async ({ page }) => {
  await avecBrouillon(page)
  await page.getByRole('button', { name: /Reprendre le bilan en cours/ }).tap()
  await expect(page.getByRole('heading', { name: 'Suivis' })).toBeVisible()
  await page.getByRole('button', { name: 'orthophoniste' }).tap()
  await expect(page.getByLabel('orthophoniste')).toHaveValue('')
  expect((await brouillon(page)).professionnels).toEqual({ orthophoniste: '' })
  await page.getByRole('button', { name: 'Suivant' }).tap()
  await expect(page.getByRole('alert')).toContainText('la fréquence de suivi (orthophoniste)')
})

test('les flèches du clavier changent le choix d\'un groupe de segments', async ({ page }) => {
  await nouveauBilan(page)
  const sexe = page.getByRole('radiogroup', { name: 'Sexe' })
  await expect(sexe.getByRole('radio', { name: 'Fille' })).toHaveAttribute('tabindex', '0')
  await expect(sexe.getByRole('radio', { name: 'Garçon' })).toHaveAttribute('tabindex', '-1')
  await sexe.getByRole('radio', { name: 'Fille' }).focus()
  await page.keyboard.press('ArrowRight')
  await expect(sexe.getByRole('radio', { name: 'Garçon' })).toBeFocused()
  expect((await brouillon(page)).sexe).toBe('Homme')
  await page.keyboard.press('ArrowRight') // On revient au début.
  expect((await brouillon(page)).sexe).toBe('Femme')
})

test('le questionnaire des parents trouvé au nom de l\'enfant pré-remplit le bilan', async ({ page }) => {
  await avecQuestionnaire(page)
  await expect(page.getByText('Questionnaire des parents : relié.')).toBeVisible()
  await page.getByRole('button', { name: /Nouveau bilan/ }).tap()
  await page.getByLabel('Prénom').fill('Léa')
  await page.getByLabel('Nom', { exact: true }).fill('Petit')
  await expect(page.getByRole('status')).toContainText('Questionnaire des parents trouvé, envoyé le 12 octobre 2026')
  await page.getByRole('button', { name: 'Importer et pré-remplir' }).tap()

  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
  await expect(page.getByLabel('Prénom')).toHaveValue('Léa')
  await expect(page.getByLabel('Classe')).toHaveValue('CE2')
  await expect(page.getByText(/Pré-rempli avec le questionnaire des parents \(1 activité OT Hope reprise\)/))
    .toBeVisible()
  await page.getByText('Réponses des parents au questionnaire').tap()
  await expect(page.getByText('Fraterie : 1 frère')).toBeVisible()
  // « Faire son cartable » n'est pas une activité de l'application : pas reprise.
  expect((await brouillon(page)).otHope).toEqual({ maison: { Balayer: 'aide' } })
})

test('sans questionnaire à ce nom, ou sans connexion, le bilan commence vide', async ({ page }) => {
  await avecQuestionnaire(page)
  await page.getByRole('button', { name: /Nouveau bilan/ }).tap()
  await page.getByLabel('Prénom').fill('Paul')
  await page.getByLabel('Nom', { exact: true }).fill('Martin')
  await expect(page.getByRole('status')).toContainText('Aucun questionnaire des parents à ce nom.')
  await expect(page.getByRole('button', { name: 'Importer et pré-remplir' })).toHaveCount(0)

  await page.unroute(`${SCRIPT}?*`)
  await page.route(`${SCRIPT}?*`, (route) => route.abort('internetdisconnected'))
  await page.getByLabel('Nom', { exact: true }).fill('Martine')
  await expect(page.getByRole('status')).toContainText('Questionnaire des parents non vérifié')
  await page.getByRole('button', { name: 'Commencer le bilan' }).tap()
  await expect(page.getByLabel('Nom', { exact: true })).toHaveValue('Martine')
  expect((await brouillon(page)).reponsesParents).toEqual([])
})
