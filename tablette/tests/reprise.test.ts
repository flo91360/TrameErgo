import { describe, expect, it } from 'vitest'
import { champs, nouveauBilan } from '../src/bilan'
import { enregistrement, reprendre, VERSION_BROUILLON } from '../src/reprise'

const date = new Date(2026, 9, 14)

describe('reprise du brouillon', () => {
  it('relit ce qu\'elle enregistre', () => {
    const bilan = nouveauBilan(date)
    Object.assign(bilan, {
      prenom: 'Léa', classe: 'CE2', lateralite: 1, troubles: ['TSA'],
      professionnels: { orthophoniste: "à raison d'une fois par semaine" },
      autresProfessionnels: [{ nom: 'ostéopathe', frequence: "à raison d'une fois par mois" }],
      otHope: { maison: { Balayer: 'aide' } }, objectifs: { maison: ['Balayer'] }, objectifsFinaux: ['Balayer'],
    })
    const texte = enregistrement(bilan)
    expect(JSON.parse(texte).version).toBe(VERSION_BROUILLON)
    const reprise = reprendre(texte, date)!
    expect(reprise.retirees).toEqual([])
    expect(champs(reprise.bilan)).toEqual(champs(bilan))
    expect(reprise.bilan.autresProfessionnels).toEqual(bilan.autresProfessionnels)
  })

  it('garde au plus 3 autres thérapeutes et retire une fréquence inconnue', () => {
    const mois = "à raison d'une fois par mois"
    const ancien = {
      ...nouveauBilan(date),
      autresProfessionnels: [
        { nom: 'ostéopathe', frequence: 'chaque jour' }, 'texte', { nom: 'sophrologue', frequence: mois },
        { nom: 'éducatrice', frequence: mois }, { nom: 'quatrième', frequence: mois },
      ],
    }
    const { bilan, retirees } = reprendre(JSON.stringify(ancien), date)!
    expect(retirees).toEqual(['chaque jour (Fréquence de suivi)'])
    expect(bilan.autresProfessionnels).toEqual([
      { nom: 'ostéopathe', frequence: '' }, { nom: 'sophrologue', frequence: mois }, { nom: 'éducatrice', frequence: mois },
    ])
    expect(reprendre(JSON.stringify({ prenom: 'Léa' }), date)!.bilan.autresProfessionnels).toEqual([])
  })

  it('reprend un brouillon de la version 1 (réponses à la racine)', () => {
    const ancien = { ...nouveauBilan(date), prenom: 'Lucas', entente: 'Bonne', dossierMdph: 'Actif', lateralite: 0 }
    const reprise = reprendre(JSON.stringify(ancien), date)!
    expect(reprise.bilan.prenom).toBe('Lucas')
    expect(reprise.bilan.dossierMdph).toBe('Actif')
    expect(reprise.retirees).toEqual([])
  })

  it('retire et signale les réponses qui n\'existent plus dans le questionnaire', () => {
    const ancien = {
      ...nouveauBilan(date), entente: 'Bonne entente', classe: 'CM3', troubles: ['TSA', 'Trouble disparu'],
      lateralite: 7, professionnels: { psychologue: 'chaque jour', sophrologue: "à raison d'une fois par mois" },
      otHope: { maison: { Balayer: 'aide', 'Activité disparue': 'aide', Cuisiner: 'niveau inconnu' }, jardin: {} },
      objectifs: { maison: ['Balayer', 'Activité disparue'] }, objectifsFinaux: ['Activité disparue', 'Balayer'],
    }
    const { bilan, retirees } = reprendre(JSON.stringify(ancien), date)!
    expect([...retirees].sort()).toEqual([
      'Bonne entente (Entente)', 'CM3 (Classe)', 'Trouble disparu (Troubles)', 'choix n° 8 (Latéralité)',
      'chaque jour (Fréquence de suivi)', 'sophrologue (Professionnels)',
      'Activité disparue (OT Hope : Activités de vie quotidienne)',
      'Cuisiner (OT Hope : Activités de vie quotidienne)',
      'domaine « jardin » (OT Hope)',
    ].sort())
    expect(bilan.entente).toBe('')
    expect(champs(bilan).fratrie).not.toContain('(') // plus de « () » dans le bilan
    expect(bilan.troubles).toEqual(['TSA'])
    expect(bilan.lateralite).toBeNull()
    expect(bilan.professionnels).toEqual({ psychologue: '' })
    expect(bilan.otHope.maison).toEqual({ Balayer: 'aide' })
    expect(bilan.objectifs.maison).toEqual(['Balayer'])
    expect(bilan.objectifsFinaux).toEqual(['Balayer'])
  })

  it('ignore les valeurs de mauvaise forme et les brouillons illisibles', () => {
    const illisible = { prenom: 42, troubles: 'TSA', sexe: 'Autre', lateralite: 'droitier' }
    const { bilan } = reprendre(JSON.stringify(illisible), date)!
    expect(bilan.prenom).toBe('')
    expect(bilan.troubles).toEqual([])
    expect(bilan.sexe).toBe('Femme')
    expect(bilan.lateralite).toBeNull()
    const coordonnees = { 'parent1.nom': 'Petit', 'parent1.telephone': 612345678 }
    expect(reprendre(JSON.stringify({ coordonnees }), date)!.bilan.coordonnees).toEqual({ 'parent1.nom': 'Petit' })
    expect(reprendre('pas du JSON', date)).toBeNull()
    expect(reprendre('null', date)).toBeNull()
    expect(reprendre('[1, 2]', date)).toBeNull()
  })

  it('remplace une date illisible au lieu d\'écrire « NaN » dans le bilan', () => {
    const ancien = { dateNaissance: 'pas une date', datePassation: '2026-13-45' }
    const { bilan, retirees } = reprendre(JSON.stringify(ancien), date)!
    expect(retirees).toEqual(['pas une date (Date de naissance)', '2026-13-45 (Date de passation)'])
    expect(bilan.dateNaissance).toBe('')
    expect(bilan.datePassation).toBe('2026-10-14')
    expect(champs(bilan).age).toBe('')
  })
})
