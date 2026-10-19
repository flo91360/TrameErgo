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
      otHope: { maison: { Balayer: 'aide' } }, objectifs: { maison: ['Balayer'] }, objectifsFinaux: ['Balayer'],
    })
    const texte = enregistrement(bilan)
    expect(JSON.parse(texte).version).toBe(VERSION_BROUILLON)
    const reprise = reprendre(texte, date)!
    expect(reprise.retirees).toEqual([])
    expect(champs(reprise.bilan)).toEqual(champs(bilan))
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
      'Activité disparue (OT Hope : Activités de vie quotidienne)', 'Cuisiner (OT Hope : Activités de vie quotidienne)',
      'domaine « jardin » (OT Hope)',
    ].sort())
    expect(bilan.entente).toBe('')
    expect(champs(bilan).entente).toBe('') // plus de « () » dans le bilan
    expect(bilan.troubles).toEqual(['TSA'])
    expect(bilan.lateralite).toBeNull()
    expect(bilan.professionnels).toEqual({ psychologue: '' })
    expect(bilan.otHope.maison).toEqual({ Balayer: 'aide' })
    expect(bilan.objectifs.maison).toEqual(['Balayer'])
    expect(bilan.objectifsFinaux).toEqual(['Balayer'])
  })

  it('ignore les valeurs de mauvaise forme et les brouillons illisibles', () => {
    const { bilan } = reprendre(JSON.stringify({ prenom: 42, troubles: 'TSA', sexe: 'Autre', lateralite: 'droitier' }), date)!
    expect(bilan.prenom).toBe('')
    expect(bilan.troubles).toEqual([])
    expect(bilan.sexe).toBe('Femme')
    expect(bilan.lateralite).toBeNull()
    expect(reprendre('pas du JSON', date)).toBeNull()
    expect(reprendre('null', date)).toBeNull()
    expect(reprendre('[1, 2]', date)).toBeNull()
  })
})
