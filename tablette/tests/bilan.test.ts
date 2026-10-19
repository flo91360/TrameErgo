import { readFileSync } from 'node:fs'
import { fileURLToPath } from 'node:url'
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'
import { describe, expect, it } from 'vitest'
import {
  calculerAge, champs, copieNumerotee, datesIncoherentes, nomDuFichier, nonRenseignes, nouveauBilan,
  objectifsPossibles, objectifsRetenus, questionnaire, type Bilan,
} from '../src/bilan'
import { remplirModele } from '../src/generer'

const modele = readFileSync(fileURLToPath(new URL('../../contenu/bilan.docx', import.meta.url)))

function texteDuBilan(docx: Uint8Array): string {
  return new Docxtemplater(new PizZip(docx), { paragraphLoop: true, linebreaks: true }).getFullText()
}

/** Garçon adolescent, tous les écrans remplis. */
function lucas(): Bilan {
  const bilan = nouveauBilan(new Date(2026, 9, 14))
  Object.assign(bilan, {
    sexe: 'Homme', trancheAge: 'Ado', prenom: 'Lucas', dossierMdph: 'En création', accordParents: 'Pas tout à fait', nom: 'Martin', dateNaissance: '2012-03-12',
    classe: '4ème', typeEtablissement: 'le collège', nomEtablissement: 'Jean Moulin', lateralite: 1,
    modeDeGarde: 'en garde alternée', fratrie: '1 sœur', entente: 'Mauvaise', medecinTraitant: 'Durand',
    ville: 'Massy', personneDemandeuse: 'la mère', motifs: [questionnaire.demande.motifs[2]],
    troubles: ['TSA', 'Dysgraphie'], autreTrouble: 'Trouble visuel',
    professionnels: { psychologue: "à raison d'une fois par mois", orthophoniste: "à raison d'une fois par semaine" },
    comportement: ['Bavardage en cours'], difficultes: ['pour s\'organiser'],
    matieresPreferees: ['EPS', 'Musique'], matieresDetestees: ['Français'],
    otHope: {
      maison: { 'Faire mes lacets': 'difficulte', 'Couper la viande': 'aide', 'Balayer': 'aide' },
      ecole: { 'Utiliser un compas': 'grande_difficulte' },
    },
    objectifs: { maison: ['Faire mes lacets', 'Balayer'], ecole: ['Utiliser un compas'] },
    objectifsFinaux: ['Utiliser un compas', 'Faire mes lacets'],
    objectifsParents: ['Faire mes lacets'], remarquesParents: 'Priorité au collège.',
    amenagements: ['Tiers temps', 'Ordinateur'], activitesExtraScolaires: 'foot, piano', difficultesLoisirs: 'fatigue',
  })
  return bilan
}

describe('âge', () => {
  it('compte les mois révolus', () => {
    expect(calculerAge('2015-10-15', '2026-10-14')).toBe('10 ans et 11 mois')
    expect(calculerAge('2015-10-14', '2026-10-14')).toBe('11 ans et 0 mois')
    expect(calculerAge('2025-10-14', '2026-10-14')).toBe('1 an et 0 mois')
    expect(calculerAge('2026-05-14', '2026-10-14')).toBe('0 an et 5 mois')
    expect(calculerAge('', '2026-10-14')).toBe('')
  })

  it('ne calcule pas d\'âge négatif et signale les dates incohérentes', () => {
    expect(calculerAge('2026-12-01', '2026-10-14')).toBe('')
    const bilan = nouveauBilan(new Date(2026, 9, 14))
    expect(datesIncoherentes(bilan)).toBe(false)
    bilan.dateNaissance = '2026-12-01'
    expect(datesIncoherentes(bilan)).toBe(true)
    expect(champs(bilan).age).toBe('')
    bilan.dateNaissance = '2026-10-14'
    expect(datesIncoherentes(bilan)).toBe(false)
  })
})

describe('champs du bilan', () => {
  it('fournit exactement les champs du modèle bilan.docx', () => {
    const texte = new Docxtemplater(new PizZip(modele), { paragraphLoop: true, linebreaks: true }).getFullText()
    // Champs {champ} et conditions {#champ}…{/champ}, {^champ}…{/champ}.
    const duModele = [...new Set([...texte.matchAll(/\{[#^/]?(\w+)\}/g)].map((m) => m[1]))].sort()
    expect(duModele.length).toBeGreaterThan(40)
    expect(Object.keys(champs(nouveauBilan())).sort()).toEqual(duModele)
  })

  it('accorde au sexe et suit l\'ordre du questionnaire', () => {
    const valeurs = champs(lucas())
    expect(valeurs.type_bilan).toBe('Adolescent')
    expect(valeurs.lateralite).toBe('gaucher')
    expect(valeurs.entente).toBe('(mauvaise entente entre eux)')
    expect(valeurs.troubles).toBe('- Dysgraphie\n- TSA\n- Trouble visuel')
    expect(valeurs.professionnels).toBe(
      "- orthophoniste : à raison d'une fois par semaine\n- psychologue : à raison d'une fois par mois")
    expect(valeurs.aide_maison).toBe('- Balayer\n- Couper la viande')
    expect(valeurs.objectifs_maison).toBe('1 - Faire mes lacets\n2 - Balayer')
    expect(valeurs.objectifs_finaux).toBe('1 - Utiliser un compas\n2 - Faire mes lacets')
    expect(valeurs.objectifs_parents).toBe('1 - Faire mes lacets\nRemarques des parents : Priorité au collège.')
    expect(valeurs.activites_extra_scolaires).toBe('- foot\n- piano')
  })

  it('oublie un objectif dont l\'activité est revenue à « rien à signaler »', () => {
    const bilan = lucas()
    delete bilan.otHope.maison['Balayer']
    expect(champs(bilan).objectifs_maison).toBe('1 - Faire mes lacets')
    expect(objectifsPossibles(bilan)).toEqual(['Faire mes lacets', 'Utiliser un compas'])
  })

  it('compte les mêmes objectifs finaux à l\'écran et dans le Word', () => {
    const bilan = lucas()
    delete bilan.otHope.ecole['Utiliser un compas']
    expect(objectifsRetenus(bilan, bilan.objectifsFinaux)).toEqual(['Faire mes lacets'])
    expect(champs(bilan).objectifs_finaux).toBe('1 - Faire mes lacets')
  })

  it('nomme le fichier d\'après le patient et la passation', () => {
    expect(nomDuFichier(lucas())).toBe('Bilan_ergotherapie_Martin_Lucas_octobre_2026.docx')
    expect(copieNumerotee('Bilan_ergotherapie_Martin_Lucas_octobre_2026.docx', 2))
      .toBe('Bilan_ergotherapie_Martin_Lucas_octobre_2026_2.docx')
  })
})

describe('génération', () => {
  it('remplit tout le modèle', () => {
    const texte = texteDuBilan(remplirModele(modele, champs(lucas())))
    expect(texte).not.toMatch(/[{}]/)
    expect(texte).toContain('Je rencontre Lucas né le 12-03-2012, il a 14 ans et 7 mois.')
    expect(texte).toContain('Il vit en garde alternée, il a 1 sœur (mauvaise entente entre eux).')
    expect(texte).toContain('ne sait pas encore faire seul ou celles qu’il fait difficilement')
    expect(texte).toContain('Bilan ergothérapie Adolescent')
    expect(texte).toContain('ne sont pas totalement en accord')
    expect(texte).toMatch(/Préférées\s: EPS, Musique/)
    expect(texte).toMatch(/Les moins appréciées\s: Français/)
  })

  it('remplit un bilan vide sans laisser de champ', () => {
    const texte = texteDuBilan(remplirModele(modele, champs(nouveauBilan())))
    expect(texte).not.toMatch(/[{}]/)
    expect(texte).toContain('Bilan ergothérapie Enfant')
  })

  it('masque les phrases dont la réponse est vide', () => {
    const bilan = nouveauBilan(new Date(2026, 9, 14))
    Object.assign(bilan, { prenom: 'Léa', dateNaissance: '2015-10-14' })
    const texte = texteDuBilan(remplirModele(modele, champs(bilan)))
    expect(texte).toContain('Je rencontre Léa née le 14-10-2015, elle a 11 ans et 0 mois. ')
    expect(texte).not.toMatch(/Dr |est en|vit |demandé par|\(\)| \.|: \./)
    expect(texte).toMatch(/Motif\s:\s+Connaissance/)

    Object.assign(bilan, { enfantUnique: true, medecinTraitant: 'Durand', classe: 'CE2', lateralite: 0 })
    const complete = texteDuBilan(remplirModele(modele, champs(bilan)))
    expect(complete).toContain('Elle est en CE2. Léa est droitière. Elle est enfant unique. ')
    expect(complete).toMatch(/Nom du médecin traitant\s: Dr Durand\./)
  })

  it('ne choisit rien à la place de l\'ergothérapeute', () => {
    const bilan = nouveauBilan()
    expect(nonRenseignes(bilan)).toEqual([
      'la classe', "l'établissement", 'la latéralité', 'le mode de garde', "l'entente dans la fratrie",
      'la personne demandeuse', 'le dossier MDPH', "l'accord des parents",
    ])
    expect(champs(bilan).dossier_mdph).toBe('')
    expect(champs(bilan).accord_parents).toBe('')
    bilan.enfantUnique = true
    expect(nonRenseignes(bilan)).not.toContain("l'entente dans la fratrie")
  })
})
