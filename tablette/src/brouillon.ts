// Bilan en cours, enregistré sur l'appareil (localStorage) à chaque modification :
// il survit à une fermeture de l'application et ne quitte jamais l'appareil.
import { reactive, watch } from 'vue'
import { nouveauBilan, type Bilan } from './bilan'
import { enregistrement, reprendre, type Reprise } from './reprise'

const CLE = 'trameergo.brouillon'

function lire(): Reprise | null {
  try {
    const texte = localStorage.getItem(CLE)
    return texte ? reprendre(texte) : null
  } catch {
    return null
  }
}

const reprise = lire()

export const brouillonTrouve = reprise !== null

/** Réponses du brouillon qui n'existent plus dans le questionnaire. */
export const reponsesRetirees = reprise?.retirees ?? []

export const bilan = reactive<Bilan>(reprise?.bilan ?? nouveauBilan())

function enregistrer(valeur: Bilan): void {
  try {
    localStorage.setItem(CLE, enregistrement(valeur))
  } catch {
    // Stockage indisponible (navigation privée) : le bilan reste en mémoire.
  }
}

// Brouillon repris : enregistré tout de suite au format actuel, sans les
// réponses retirées (elles ne sont signalées qu'une fois).
if (reprise) enregistrer(bilan)
watch(bilan, enregistrer, { deep: true })

/** Efface le brouillon et repart d'un bilan vide. */
export function nouveauBilanVide(): void {
  Object.assign(bilan, nouveauBilan())
}
