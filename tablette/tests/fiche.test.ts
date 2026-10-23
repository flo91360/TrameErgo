// Fiche patient : champs du modèle contenu/fiche.docx, remplis par l'écran
// Patient puis, à défaut, par le questionnaire des parents.
import { readFileSync } from 'node:fs'
import { fileURLToPath } from 'node:url'
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'
import { describe, expect, it } from 'vitest'
import { nomDeLaFiche, nouveauBilan, reevaluation } from '../src/bilan'
import { champsFiche } from '../src/fiche'
import { remplirModele } from '../src/generer'

const modele = readFileSync(fileURLToPath(new URL('../../contenu/fiche.docx', import.meta.url)))
const texte = (docx: Uint8Array | Buffer) =>
  new Docxtemplater(new PizZip(docx), { paragraphLoop: true, linebreaks: true }).getFullText()
const date = new Date(2026, 9, 23)

function lea() {
  const bilan = nouveauBilan(date)
  Object.assign(bilan, {
    prenom: 'Léa', nom: 'Petit', medecinTraitant: 'Durand', lateralite: 0,
    coordonnees: {
      'enfant.nom': 'PETIT', 'enfant.date_de_naissance': '2016-10-14', 'enfant.classe': 'CE2',
      'medecin.nom': 'Dr Durant', 'medecin.ville': 'Massy',
      'parent1.nom': 'Petit', 'parent1.prenom': 'Anne', 'parent1.telephone': '06 12 34 56 78',
      'parent1.adresse_mail': 'a.petit@exemple.fr', 'parent2.profession': 'Boulanger',
      'famille.fratrie': '1 frère', 'famille.mode_de_garde': 'Garde alternée',
    },
  })
  return bilan
}

describe('fiche patient', () => {
  it('fournit exactement les champs du modèle fiche.docx, sans conditions', () => {
    const contenu = texte(modele)
    expect(contenu).not.toMatch(/\{[#/^]/)
    const duModele = [...new Set([...contenu.matchAll(/\{([\w.]+)\}/g)].map((m) => m[1]))].sort()
    expect(duModele).toContain('parent2.adresse_mail')
    expect(Object.keys(champsFiche(nouveauBilan(), date)).sort()).toEqual(duModele)
  })

  it("préfère l'écran Patient au questionnaire des parents", () => {
    const valeurs = champsFiche(lea(), date)
    expect(valeurs['enfant.nom']).toBe('Petit')
    expect(valeurs['enfant.date_de_naissance']).toBe('14-10-2016')
    expect(valeurs['enfant.age']).toBe('10 ans et 0 mois')
    expect(valeurs['enfant.classe']).toBe('CE2')
    expect(valeurs['enfant.lateralite']).toBe('droitière')
    expect([valeurs['medecin.nom'], valeurs['medecin.ville']]).toEqual(['Durand', 'Massy'])
    expect(valeurs['parent1.telephone']).toBe('06 12 34 56 78')
    expect(valeurs['parent2.nom']).toBe('')
    expect(valeurs['famille.fratrie']).toBe('1 frère')
    expect(champsFiche({ ...lea(), enfantUnique: true }, date)['famille.fratrie']).toBe('enfant unique')
  })

  it('remplit le vrai modèle', () => {
    const contenu = texte(remplirModele(modele, champsFiche(lea(), date)))
    expect(contenu).toContain('Fiche créée le 23-10-2026')
    expect(contenu).toContain('a.petit@exemple.fr')
    expect(contenu).toContain('Boulanger')
    expect(contenu).not.toMatch(/[{}]/)
  })

  it('est nommée d\'après l\'enfant et garde les coordonnées en réévaluation', () => {
    expect(nomDeLaFiche(lea())).toBe('Fiche_patient_Petit_Léa.docx')
    expect(reevaluation(lea(), date).coordonnees['parent1.prenom']).toBe('Anne')
  })
})
