// Historique des bilans créés sur cet appareil (localStorage) : chaque bilan
// Word créé y laisse ses réponses, pour le reprendre, le recréer ou préparer
// une réévaluation. Comme le brouillon, il ne quitte jamais l'appareil, sauf
// sauvegarde demandée (fichier .json à garder ou à importer sur un autre appareil).
import { ref } from 'vue'
import { nomDuFichier, type Bilan } from './bilan'
import { enregistrement } from './reprise'

const CLE = 'trameergo.historique'

export interface EntreeHistorique {
  /** Nom du fichier Word : un bilan recréé remplace son entrée. */
  fichier: string
  patient: string
  /** AAAA-MM-JJ. */
  passation: string
  /** Date et heure de création du Word (ISO). */
  cree: string
  /** Réponses, au format du brouillon (relues par reprendre). */
  reponses: string
}

function estEntree(valeur: unknown): valeur is EntreeHistorique {
  if (typeof valeur !== 'object' || valeur === null) return false
  const entree = valeur as Record<string, unknown>
  return ['fichier', 'patient', 'passation', 'cree', 'reponses'].every((cle) => typeof entree[cle] === 'string')
}

/** Entrées valables d'un historique enregistré ou d'une sauvegarde (null : illisible). */
export function lireHistorique(texte: string): EntreeHistorique[] | null {
  try {
    const donnees: unknown = JSON.parse(texte)
    const liste = Array.isArray(donnees) ? donnees : (donnees as { historique?: unknown })?.historique
    return Array.isArray(liste) ? liste.filter(estEntree) : null
  } catch {
    return null
  }
}

/** Du plus récent au plus ancien, une entrée par fichier (la plus récente). */
export function fusionner(...listes: EntreeHistorique[][]): EntreeHistorique[] {
  const parFichier = new Map<string, EntreeHistorique>()
  for (const entree of listes.flat()) {
    const connue = parFichier.get(entree.fichier)
    if (!connue || connue.cree < entree.cree) parFichier.set(entree.fichier, entree)
  }
  return [...parFichier.values()].sort((a, b) => b.cree.localeCompare(a.cree))
}

export function entreeDe(bilan: Bilan, date = new Date()): EntreeHistorique {
  return {
    fichier: nomDuFichier(bilan),
    patient: `${bilan.prenom.trim()} ${bilan.nom.trim()}`.trim(),
    passation: bilan.datePassation,
    cree: date.toISOString(),
    reponses: enregistrement(bilan),
  }
}

/** Sauvegarde de l'historique, à importer plus tard ou sur un autre appareil. */
export function sauvegarde(entrees: EntreeHistorique[]): string {
  return JSON.stringify({ application: 'TrameErgo', historique: entrees }, null, 1)
}

function lire(): EntreeHistorique[] {
  try {
    return lireHistorique(localStorage.getItem(CLE) ?? '[]') ?? []
  } catch {
    return []
  }
}

export const historique = ref<EntreeHistorique[]>(lire())

function enregistrer(entrees: EntreeHistorique[]): void {
  historique.value = entrees
  try {
    localStorage.setItem(CLE, JSON.stringify(entrees))
  } catch {
    // Stockage indisponible ou plein : l'historique reste en mémoire.
  }
}

export function ajouterAHistorique(bilan: Bilan): void {
  enregistrer(fusionner([entreeDe(bilan)], historique.value))
}

export function retirerDeHistorique(fichier: string): void {
  enregistrer(historique.value.filter((entree) => entree.fichier !== fichier))
}

/** Ajoute les bilans d'une sauvegarde ; renvoie leur nombre (null : fichier illisible). */
export function importer(texte: string): number | null {
  const entrees = lireHistorique(texte)
  if (entrees === null) return null
  enregistrer(fusionner(historique.value, entrees))
  return entrees.length
}
