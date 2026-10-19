// Remplit le modèle Word localement : aucune donnée ne quitte l'appareil.
import Docxtemplater from 'docxtemplater'
import PizZip from 'pizzip'

export const TYPE_DOCX = 'application/vnd.openxmlformats-officedocument.wordprocessingml.document'

/** Remplace les champs {…} du modèle ; « \n » dans une valeur devient un saut de ligne. */
export function remplirModele(modele: ArrayBuffer | Uint8Array, valeurs: Record<string, string>): Uint8Array {
  const document = new Docxtemplater(new PizZip(modele), {
    paragraphLoop: true,
    linebreaks: true,
    nullGetter: () => '',
  })
  document.render(valeurs)
  return document.getZip().generate({ type: 'uint8array', compression: 'DEFLATE' })
}
