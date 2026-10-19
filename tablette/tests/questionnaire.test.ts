// Règles que contenu/questionnaire.json doit respecter : une erreur de saisie
// dans le fichier (doublon, liste vide, identifiant mal formé) est signalée
// ici plutôt que découverte dans un bilan.
import { describe, expect, it } from 'vitest'
import { questionnaire } from '../src/bilan'

const { identite, demande, suivis, scolarite, otHope, objectifs, amenagements } = questionnaire

/** Liste non vide, sans doublon ni texte vide ou entouré d'espaces. */
function listeValide(liste: readonly string[]) {
  expect(liste.length).toBeGreaterThan(0)
  for (const element of liste) expect(element, JSON.stringify(element)).toBe(element.trim())
  expect(liste.filter(Boolean)).toHaveLength(liste.length)
  expect(liste.filter((element, i) => liste.indexOf(element) !== i), 'en double').toEqual([])
}

describe('questionnaire.json', () => {
  it('a des listes sans doublon ni texte vide', () => {
    const listes = {
      classes: identite.classes, typesEtablissement: identite.typesEtablissement,
      modesDeGarde: identite.modesDeGarde, entente: identite.entente.map((e) => e.libelle),
      personnesDemandeuses: demande.personnesDemandeuses, motifs: demande.motifs, troubles: demande.troubles,
      dossierMdph: demande.dossierMdph, professionnels: suivis.professionnels, frequences: suivis.frequences,
      comportement: scolarite.comportement, difficultes: scolarite.difficultes, matieres: scolarite.matieres,
      accordParents: objectifs.accordParents.map((a) => a.libelle), amenagements,
    }
    for (const [nom, liste] of Object.entries(listes)) {
      expect(liste, nom).toBeDefined()
      listeValide(liste)
    }
  })

  it('garde les latéralités féminine et masculine dans le même ordre', () => {
    // La réponse est mémorisée par sa position : même nombre de choix, même sens.
    expect(identite.lateralite.Femme).toHaveLength(identite.lateralite.Homme.length)
    listeValide(identite.lateralite.Femme)
    listeValide(identite.lateralite.Homme)
  })

  it('a une phrase pour chaque entente et chaque accord des parents', () => {
    for (const { libelle, phrase } of identite.entente) expect(phrase.trim(), libelle).not.toBe('')
    for (const { libelle, phrase } of objectifs.accordParents) expect(phrase, libelle).toContain('{prenom}')
  })

  it('a des identifiants OT Hope utilisables dans les champs du modèle Word', () => {
    // {aide_maison}, {objectifs_ecole}… : lettres, chiffres et tirets bas seulement.
    const ids = [...otHope.niveaux.map((n) => n.id), ...otHope.domaines.map((d) => d.id)]
    for (const id of ids) expect(id).toMatch(/^[a-z][a-z0-9_]*$/)
    listeValide(otHope.niveaux.map((n) => n.id))
    listeValide(otHope.domaines.map((d) => d.id))
    listeValide(otHope.niveaux.map((n) => n.libelle))
    expect(otHope.neutre.trim()).not.toBe('')
  })

  it('a des activités OT Hope uniques, même d\'un domaine à l\'autre', () => {
    // Les objectifs finaux sont retrouvés par le libellé de l'activité.
    for (const domaine of otHope.domaines) listeValide(domaine.activites)
    listeValide(otHope.domaines.flatMap((d) => d.activites))
  })
})
