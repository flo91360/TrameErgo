// Application Windows (Tauri) : le bilan est enregistré dans Documents\TrameErgo
// et ouvert dans Word. Dans un navigateur (tablette), il est téléchargé ou
// partagé à la place.
import { isTauri } from '@tauri-apps/api/core'
import { copieNumerotee } from './bilan'

export const surOrdinateur = isTauri()

/** Un bilan de ce nom existe déjà dans Documents\TrameErgo. */
export async function existe(nom: string): Promise<boolean> {
  const { BaseDirectory, exists } = await import('@tauri-apps/plugin-fs')
  return exists(`TrameErgo/${nom}`, { baseDir: BaseDirectory.Document })
}

/** Premier nom libre parmi Bilan_…_2.docx, Bilan_…_3.docx… */
export async function nomLibre(nom: string): Promise<string> {
  let numero = 2
  while (await existe(copieNumerotee(nom, numero))) numero += 1
  return copieNumerotee(nom, numero)
}

/** Écrit le bilan dans Documents\TrameErgo et renvoie son chemin complet. */
export async function enregistrerDansDocuments(nom: string, contenu: Uint8Array): Promise<string> {
  const { BaseDirectory, mkdir, writeFile } = await import('@tauri-apps/plugin-fs')
  const { documentDir, join } = await import('@tauri-apps/api/path')
  await mkdir('TrameErgo', { baseDir: BaseDirectory.Document, recursive: true })
  await writeFile(`TrameErgo/${nom}`, contenu, { baseDir: BaseDirectory.Document })
  return join(await documentDir(), 'TrameErgo', nom)
}

/** Ouvre le bilan avec l'application associée aux .docx (Word). */
export async function ouvrir(chemin: string): Promise<void> {
  const { openPath } = await import('@tauri-apps/plugin-opener')
  await openPath(chemin)
}
