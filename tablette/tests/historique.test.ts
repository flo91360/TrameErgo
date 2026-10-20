import { describe, expect, it } from 'vitest'
import { nouveauBilan } from '../src/bilan'
import { entreeDe, fusionner, lireHistorique, sauvegarde } from '../src/historique'
import { reprendre } from '../src/reprise'

function entree(prenom: string, jour: number) {
  const bilan = nouveauBilan(new Date(2026, 9, jour))
  Object.assign(bilan, { prenom, nom: 'Martin' })
  return entreeDe(bilan, new Date(2026, 9, jour, 12))
}

describe('historique', () => {
  it('garde les réponses, relues comme un brouillon', () => {
    const lea = entree('Léa', 14)
    expect(lea).toMatchObject({
      fichier: 'Bilan_ergotherapie_Martin_Léa_octobre_2026.docx', patient: 'Léa Martin', passation: '2026-10-14',
    })
    expect(reprendre(lea.reponses)?.bilan.prenom).toBe('Léa')
  })

  it('garde un bilan par fichier, le plus récent en premier', () => {
    const lea = entree('Léa', 14)
    const leaRecree = { ...lea, cree: '2026-10-20T10:00:00.000Z' }
    const tom = entree('Tom', 15)
    expect(fusionner([lea, tom], [leaRecree]).map((e) => [e.patient, e.cree]))
      .toEqual([['Léa Martin', leaRecree.cree], ['Tom Martin', tom.cree]])
  })

  it('relit une sauvegarde et refuse un autre fichier', () => {
    const lea = entree('Léa', 14)
    expect(lireHistorique(sauvegarde([lea]))).toEqual([lea])
    expect(lireHistorique(JSON.stringify([lea, { fichier: 'incomplet' }]))).toEqual([lea])
    expect(lireHistorique('{"autre": 1}')).toBeNull()
    expect(lireHistorique('pas du JSON')).toBeNull()
  })
})
