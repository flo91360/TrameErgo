// Application Windows (Tauri) : le bilan est enregistré dans Documents\TrameErgo
// et ouvert dans Word, comme avec l'ancienne application. Dans un navigateur
// (tablette), il est téléchargé ou partagé à la place.
import { isTauri } from '@tauri-apps/api/core'

export const surOrdinateur = isTauri()

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
