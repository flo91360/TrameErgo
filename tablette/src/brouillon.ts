// Bilan en cours, enregistré sur l'appareil (localStorage) à chaque modification :
// il survit à une fermeture de l'onglet et ne quitte jamais la tablette.
import { reactive, watch } from 'vue'
import { nouveauBilan, type Bilan } from './bilan'

const CLE = 'trameergo.brouillon'

function lire(): Bilan | null {
  try {
    const texte = localStorage.getItem(CLE)
    // Les champs ajoutés depuis l'enregistrement prennent leur valeur par défaut.
    return texte ? { ...nouveauBilan(), ...JSON.parse(texte) } : null
  } catch {
    return null
  }
}

export const brouillonTrouve = lire() !== null

export const bilan = reactive<Bilan>(lire() ?? nouveauBilan())

watch(bilan, (valeur) => {
  try {
    localStorage.setItem(CLE, JSON.stringify(valeur))
  } catch {
    // Stockage indisponible (navigation privée) : le bilan reste en mémoire.
  }
}, { deep: true })

/** Efface le brouillon et repart d'un bilan vide. */
export function nouveauBilanVide(): void {
  Object.assign(bilan, nouveauBilan())
}
