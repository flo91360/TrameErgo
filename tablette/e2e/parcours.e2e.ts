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

test.beforeEach(async ({ page }) => {
  await page.goto('./')
  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
})

test('toucher le titre d\'un choix ne change pas la réponse', async ({ page }) => {
  await page.getByRole('radio', { name: 'Garçon' }).tap()
  // Le texte « Sexe » est en haut à gauche de son bloc, au-dessus des segments.
  await page.locator('.champ', { hasText: 'Sexe' }).tap({ position: { x: 5, y: 5 } })
  expect((await brouillon(page)).sexe).toBe('Homme')
})

test('un bilan rempli de bout en bout donne le Word attendu', async ({ page }) => {
  await page.getByRole('radio', { name: 'Garçon' }).tap()
  await page.getByLabel('Prénom').fill('Lucas')
  await page.getByLabel('Nom', { exact: true }).fill('Martin')
  await page.getByLabel('Date de naissance').fill('2012-03-12')
  await page.getByLabel('Date de passation').fill('2026-10-14')
  await expect(page.getByText('Âge à la passation : 14 ans et 7 mois')).toBeVisible()
  await page.getByLabel('Classe').selectOption('4ème')
  await page.getByLabel('Latéralité').selectOption({ label: 'gaucher' })
  await page.getByLabel('Mode de garde').selectOption('en garde alternée')
  await page.getByLabel('Médecin traitant').fill('Durand')

  await etape(page, 'Demande')
  await page.getByLabel('Personne demandeuse').selectOption('la mère')
  await page.getByRole('button', { name: 'Dysgraphie' }).tap()

  await etape(page, /OT Hope : Activités de vie quotidienne/)
  await page.getByRole('radiogroup', { name: 'Faire mes lacets' }).getByRole('radio', { name: 'Avec difficulté' }).tap()
  await expect(page.getByText('1 activité signalée.')).toBeVisible()

  await etape(page, 'Objectifs')
  await page.locator('.carte', { hasText: 'Objectifs de Lucas : activités de vie quotidienne' })
    .getByRole('button', { name: 'Faire mes lacets' }).tap()
  await page.locator('.carte', { hasText: 'Objectifs finaux' }).getByRole('button', { name: 'Faire mes lacets' }).tap()

  await etape(page, /^\d+\s*Bilan$/)
  await expect(page.getByText(/À renseigner : l'établissement, l'entente dans la fratrie, le dossier MDPH/)).toBeVisible()
  const [telechargement] = await Promise.all([
    page.waitForEvent('download'),
    page.getByRole('button', { name: 'Créer le bilan Word' }).tap(),
  ])
  expect(telechargement.suggestedFilename()).toBe('Bilan_ergotherapie_Martin_Lucas_octobre_2026.docx')

  const docx = await readFile(await telechargement.path())
  const texte = new Docxtemplater(new PizZip(docx), { paragraphLoop: true, linebreaks: true }).getFullText()
  expect(texte).toContain('Je rencontre Lucas né le 12-03-2012, il a 14 ans et 7 mois. Il est en 4ème. Lucas est gaucher. ')
  expect(texte).toContain('Il vit en garde alternée. ')
  expect(texte).toMatch(/Dr Durand\./)
  expect(texte).toContain('le bilan a été demandé par la mère.')
  expect(texte).toContain('1 - Faire mes lacets')
  expect(texte).not.toMatch(/[{}]|\(\)| \./)
})

test('le brouillon est repris, puis effacé par « Nouveau bilan »', async ({ page }) => {
  await page.getByLabel('Prénom').fill('Léa')
  await page.reload()
  await expect(page.getByText('Bilan en cours repris (Léa )')).toBeVisible()
  await expect(page.getByLabel('Prénom')).toHaveValue('Léa')

  await etape(page, /^\d+\s*Bilan$/)
  page.once('dialog', (dialogue) => dialogue.accept())
  await page.getByRole('button', { name: 'Nouveau bilan' }).tap()
  await expect(page.getByRole('heading', { name: 'Patient' })).toBeVisible()
  await expect(page.getByLabel('Prénom')).toHaveValue('')
  await expect(page.locator('.bandeau')).toHaveCount(0)
})

test('un ancien brouillon signale les réponses disparues du questionnaire', async ({ page }) => {
  await page.evaluate(() => localStorage.setItem('trameergo.brouillon', JSON.stringify({
    prenom: 'Léa', classe: 'CM3', entente: 'Bonne', troubles: ['TSA', 'Trouble disparu'],
  })))
  await page.reload()
  await expect(page.getByText(/ont été retirées du bilan en cours : CM3 \(Classe\), Trouble disparu \(Troubles\)\./))
    .toBeVisible()
  await expect(page.getByLabel('Classe')).toHaveValue('')
  expect((await brouillon(page)).troubles).toEqual(['TSA'])
  await page.reload()
  await expect(page.getByText(/ont été retirées/)).toHaveCount(0)
})
