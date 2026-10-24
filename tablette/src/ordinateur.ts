// Application Windows (Tauri) : le bilan est enregistré dans Documents\TrameErgo
// et ouvert dans Word. Dans un navigateur (tablette), il est téléchargé ou
// partagé à la place.
import { isTauri } from '@tauri-apps/api/core'
import { copieNumerotee } from './bilan'

export const surOrdinateur = isTauri()

/** Un document (bilan) de ce nom existe déjà dans Documents\TrameErgo. */
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

export type ChoixBilanExistant = 'remplacer' | 'copie' | 'annuler'

/**
 * Un bilan de ce nom existe déjà (et a peut-être été complété dans Word) :
 * fenêtre Windows avec trois boutons nommés, plutôt qu'un « OK / Annuler »
 * où « Annuler » créerait une copie.
 */
export async function choisirSiExiste(nom: string): Promise<ChoixBilanExistant> {
  const { message } = await import('@tauri-apps/plugin-dialog')
  const remplacer = 'Remplacer'
  const copie = 'Garder les deux'
  const reponse = await message(
    `${nom} existe déjà dans Documents\\TrameErgo et a peut-être été complété dans Word.\n\n`
      + `« ${remplacer} » efface ce fichier, avec les modifications faites dans Word.\n`
      + `« ${copie} » enregistre le nouveau document à côté, sous un autre nom.`,
    { title: 'Document déjà enregistré', kind: 'warning', buttons: { yes: remplacer, no: copie, cancel: 'Annuler' } },
  )
  // Réponse : le libellé du bouton (ou Yes / No selon le système) ; fermer la fenêtre annule.
  if (reponse === remplacer || reponse === 'Yes') return 'remplacer'
  if (reponse === copie || reponse === 'No') return 'copie'
  return 'annuler'
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
