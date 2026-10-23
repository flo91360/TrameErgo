// Fiche patient : coordonnées de l'enfant, du médecin traitant et de la
// famille, champs {partie.information} du modèle contenu/fiche.docx. L'écran
// Patient (vérifié par l'ergothérapeute) l'emporte sur le questionnaire des
// parents.
import { aujourdhui, calculerAge, dateFrancaise, lateralites, type Bilan } from './bilan'
import { dateDeNaissance } from './questionnaireParents'

export const INFORMATIONS_PARENT = ['nom', 'prenom', 'adresse', 'telephone', 'adresse_mail', 'profession'] as const

/** Valeur de chaque champ {…} du modèle fiche.docx. */
export function champsFiche(bilan: Bilan, date = new Date()): Record<string, string> {
  const parents = bilan.coordonnees
  const premier = (...valeurs: (string | undefined)[]) => valeurs.map((v) => v?.trim()).find(Boolean) ?? ''
  const naissance = bilan.dateNaissance || dateDeNaissance(parents['enfant.date_de_naissance'] ?? '')
  const lateralite = bilan.lateralite === null ? '' : lateralites(bilan.sexe)[bilan.lateralite]
  const valeurs: Record<string, string> = {
    date_de_creation: dateFrancaise(aujourdhui(date)),
    'enfant.nom': premier(bilan.nom, parents['enfant.nom']),
    'enfant.prenom': premier(bilan.prenom, parents['enfant.prenom']),
    'enfant.date_de_naissance': naissance ? dateFrancaise(naissance) : premier(parents['enfant.date_de_naissance']),
    'enfant.age': calculerAge(naissance, aujourdhui(date)),
    'enfant.classe': premier(bilan.classe, parents['enfant.classe']),
    'enfant.etablissement': [bilan.typeEtablissement, bilan.nomEtablissement.trim()].filter(Boolean).join(' '),
    'enfant.lateralite': premier(lateralite, parents['enfant.lateralite']),
    'medecin.nom': premier(bilan.medecinTraitant, parents['medecin.nom']),
    'medecin.ville': premier(bilan.ville, parents['medecin.ville']),
    'famille.fratrie': bilan.enfantUnique ? 'enfant unique' : premier(bilan.fratrie, parents['famille.fratrie']),
    'famille.mode_de_garde': premier(bilan.modeDeGarde, parents['famille.mode_de_garde']),
  }
  for (const numero of [1, 2])
    for (const information of INFORMATIONS_PARENT)
      valeurs[`parent${numero}.${information}`] = premier(parents[`parent${numero}.${information}`])
  return valeurs
}
