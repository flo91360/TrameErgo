import { readFileSync } from 'node:fs'
import { fileURLToPath } from 'node:url'
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'
import { describe, expect, it } from 'vitest'
import {
  aRenseigner, calculerAge, champs, copieNumerotee, datesIncoherentes, nomDuFichier, nouveauBilan, obligatoires,
  objectifsPossibles, objectifsRetenus, questionnaire, reevaluation, type Bilan,
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
    sexe: 'Homme', trancheAge: 'Ado', prenom: 'Lucas', nom: 'Martin', dateNaissance: '2012-03-12',
    dossierMdph: 'En création', accordParents: 'Pas tout à fait',
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
    const duModele = [...new Set([...texte.matchAll(/\{(\w+)\}/g)].map((m) => m[1]))].sort()
    expect(duModele.length).toBeGreaterThan(40)
    expect(Object.keys(champs(nouveauBilan())).sort()).toEqual(duModele)
  })

  it('accorde au sexe et suit l\'ordre du questionnaire', () => {
    const valeurs = champs(lucas())
    expect(valeurs.type_bilan).toBe('Adolescent')
    expect(valeurs.lateralite).toBe('gaucher')
    expect(valeurs.fratrie).toBe('a 1 sœur (mauvaise entente entre eux)')
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

  it('écrit l\'enfant unique et les choix de la personne demandeuse', () => {
    const bilan = lucas()
    Object.assign(bilan, { enfantUnique: true, fratrie: '', entente: '', sexe: 'Femme', prenom: 'Léa' })
    const texte = texteDuBilan(remplirModele(modele, champs(bilan)))
    expect(texte).toContain('Elle vit en garde alternée, elle est enfant unique. ')
    expect(texte).toMatch(/Nom du médecin traitant\s: Dr Durand, à Massy\./)
    expect(texte).toContain('le bilan a été demandé par la mère.')
    expect(texte).not.toMatch(/[{}]|\(\)| \./)
  })
})

describe('autres thérapeutes', () => {
  const semaine = "à raison d'une fois par semaine"
  const mois = "à raison d'une fois par mois"

  it('écrit chaque « Autre » avec sa fréquence, à la suite des professionnels', () => {
    const bilan = lucas()
    bilan.autresProfessionnels = [
      { nom: 'ostéopathe', frequence: mois },
      { nom: 'Mme Petit, éducatrice', frequence: semaine },
      { nom: 'sophrologue', frequence: "à raison d'une fois par an" },
    ]
    expect(aRenseigner(bilan)).toEqual([])
    const valeurs = champs(bilan)
    expect(valeurs.autre).toBe(
      "\n- ostéopathe : à raison d'une fois par mois\n- Mme Petit, éducatrice : à raison d'une fois par semaine"
      + "\n- sophrologue : à raison d'une fois par an")
    const texte = texteDuBilan(remplirModele(modele, valeurs))
    expect(texte).toContain(
      "- psychologue : à raison d'une fois par mois- ostéopathe : à raison d'une fois par mois"
      + "- Mme Petit, éducatrice : à raison d'une fois par semaine- sophrologue : à raison d'une fois par an")
  })

  it('n\'écrit rien sans « Autre »', () => {
    const bilan = lucas()
    expect(champs(bilan).autre).toBe('')
    const texte = texteDuBilan(remplirModele(modele, champs(bilan)))
    expect(texte).toContain("- psychologue : à raison d'une fois par moisDossier MDPH")
    bilan.autresProfessionnels = [{ nom: 'ostéopathe', frequence: mois }]
    bilan.aucunProfessionnel = true
    expect(champs(bilan).autre).toBe('')
  })

  it('suffit seul, sans saut de ligne avant', () => {
    const bilan = lucas()
    bilan.professionnels = {}
    bilan.autresProfessionnels = [{ nom: 'ostéopathe', frequence: mois }]
    expect(obligatoires.suivis(bilan)).toEqual([])
    expect(champs(bilan).professionnels).toBe('')
    expect(champs(bilan).autre).toBe("- ostéopathe : à raison d'une fois par mois")
  })

  it('demande le thérapeute et sa fréquence pour quitter l\'écran', () => {
    const bilan = lucas()
    bilan.autresProfessionnels = [{ nom: 'ostéopathe', frequence: '' }, { nom: ' ', frequence: semaine }]
    expect(obligatoires.suivis(bilan)).toEqual([
      'la fréquence de suivi (ostéopathe)', "le nom ou la profession de l'autre thérapeute n° 2",
    ])
  })
})

describe('modèle lisible', () => {
  it('n\'a que des champs simples, sans conditions', () => {
    const texte = new Docxtemplater(new PizZip(modele), { paragraphLoop: true, linebreaks: true }).getFullText()
    expect(texte).not.toMatch(/\{[#^/]/)
    expect(texte).toContain('Je rencontre {prenom} {ne_e} le {date_de_naissance}, {il_elle} a {age}.')
  })
})

describe('réponses obligatoires', () => {
  it('ne laisse pas passer un écran incomplet', () => {
    const bilan = nouveauBilan()
    expect(obligatoires.patient(bilan)).toEqual([
      'le prénom', 'le nom', 'la date de naissance', 'la classe', "l'établissement", "le nom de l'établissement",
      'la latéralité', 'le mode de garde', 'la fratrie (ou « Enfant unique »)', "l'entente dans la fratrie",
      'le médecin traitant', 'la ville du médecin traitant',
    ])
    expect(obligatoires.demande(bilan)).toEqual(['la personne demandeuse', 'le dossier MDPH', 'au moins un motif'])
    expect(obligatoires.suivis(bilan)).toEqual(["les professionnels qui suivent l'enfant (ou « Aucun »)"])
    expect(obligatoires.objectifs(bilan)).toEqual(["l'accord des parents"])
    expect(champs(bilan).dossier_mdph).toBe('')
    expect(aRenseigner(lucas())).toEqual([])
  })

  it('suit les réponses qui en dispensent ou en ajoutent', () => {
    const bilan = lucas()
    Object.assign(bilan, { fratrie: '', entente: '', enfantUnique: true, motifs: [], autreMotif: 'Lenteur' })
    expect(aRenseigner(bilan)).toEqual([])
    bilan.dateNaissance = '2027-01-01'
    expect(obligatoires.patient(bilan)).toEqual(['une date de naissance avant la date de passation'])
    bilan.professionnels = { psychologue: '', orthophoniste: "à raison d'une fois par mois" }
    expect(obligatoires.suivis(bilan)).toEqual(['la fréquence de suivi (psychologue)'])
    bilan.aucunProfessionnel = true
    expect(obligatoires.suivis(bilan)).toEqual([])
    bilan.objectifsFinaux = []
    expect(obligatoires.objectifs(bilan)).toEqual(['au moins un objectif final'])
    bilan.otHope = {}
    expect(obligatoires.objectifs(bilan)).toEqual([])
  })
})

describe('réévaluation', () => {
  it('garde l\'identité et refait la classe et la partie clinique', () => {
    const nouveau = reevaluation(lucas(), new Date(2027, 9, 1))
    expect(nouveau).toMatchObject({
      prenom: 'Lucas', nom: 'Martin', dateNaissance: '2012-03-12', sexe: 'Homme', medecinTraitant: 'Durand',
      datePassation: '2027-10-01', classe: '', troubles: [], otHope: {}, objectifsFinaux: [], accordParents: '',
    })
    expect(obligatoires.patient(nouveau)).toEqual(['la classe'])
  })
})
