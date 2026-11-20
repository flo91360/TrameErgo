// Règles que contenu/questionnaire.json doit respecter : une erreur de saisie
// dans le fichier (doublon, liste vide, identifiant mal formé) est signalée
// ici plutôt que découverte dans un bilan.
import { describe, expect, it } from 'vitest'
import { normes, observationsPossibles, OBSERVATIONS_BB, questionnaire } from '../src/bilan'

const { identite, demande, suivis, scolarite, caractere, otHope, objectifs, amenagements } = questionnaire

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
      difficultes: scolarite.difficultes, matieres: scolarite.matieres,
      accordParents: objectifs.accordParents.map((a) => a.libelle), amenagements,
    }
    for (const [nom, liste] of Object.entries(listes)) {
      expect(liste, nom).toBeDefined()
      listeValide(liste)
    }
  })

  it('a un caractère mélangé, chaque item reformulé pour l\'enfant', () => {
    listeValide(caractere.map((c) => c.libelle))
    listeValide(caractere.map((c) => c.feminin))
    listeValide(caractere.map((c) => c.enfant))
    for (const item of caractere) expect(['qualite', 'defaut'], item.libelle).toContain(item.type)
    expect(caractere.some((c) => c.type === 'qualite')).toBe(true)
    expect(caractere.some((c) => c.type === 'defaut')).toBe(true)
    for (const item of caractere) if ('infinitif' in item) expect(item.infinitif?.trim(), item.libelle).toBeTruthy()
  })

  it('propose les traits de caractère ajoutés pour les parents', () => {
    const libelles = caractere.map((c) => c.libelle)
    for (const trait of ['peu sociable', 'très sensible', 'empathique', 'intolérant à l\'injustice',
      'intolérant à la frustration', 'facilement dans le conflit', 'influençable', 'teste souvent le cadre',
      'provocateur']) expect(libelles).toContain(trait)
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

  it('a des observations du Box and Blocks utilisables', () => {
    listeValide(OBSERVATIONS_BB.map((o) => o.libelle))
    listeValide(observationsPossibles())
    for (const observation of OBSERVATIONS_BB) {
      if (observation.choix) listeValide(observation.choix)
      if (observation.phrase) expect(observation.phrase, observation.libelle).toContain('{choix}')
      if (observation.feminin) expect(observation.feminin.trim(), observation.libelle).toBeTruthy()
    }
    const { douleur } = questionnaire.boxAndBlocks
    expect(douleur.aucune.trim()).not.toBe('')
    expect(douleur.presente).toContain('{douleur}')
    expect(douleur.localisee).toContain('{localisation}')
  })
})

describe('normes.json', () => {
  it('couvre le Box and Blocks de 6 à 19 ans, sans trou ni chevauchement', () => {
    const { tranches } = normes.boxAndBlocks
    expect(tranches[0].ageMin).toBe(6)
    expect(tranches[tranches.length - 1].ageMax).toBe(19)
    tranches.forEach((tranche, i) => {
      expect(tranche.ageMax).toBeGreaterThanOrEqual(tranche.ageMin)
      if (i > 0) expect(tranche.ageMin).toBe(tranches[i - 1].ageMax + 1)
      for (const sexe of ['Homme', 'Femme'] as const) {
        for (const cote of ['droite', 'gauche'] as const) {
          const { moyenne, ecartType } = tranche[sexe][cote]
          expect(moyenne, `${tranche.ageMin}-${tranche.ageMax} ${sexe} ${cote}`).toBeGreaterThan(0)
          expect(ecartType, `${tranche.ageMin}-${tranche.ageMax} ${sexe} ${cote}`).toBeGreaterThan(0)
        }
      }
    })
  })

  it('reprend les valeurs du fichier Calcul-DS.xlsx', () => {
    const [six, , , douze, , , dixHuit] = normes.boxAndBlocks.tranches
    expect(six.Homme).toEqual({ droite: { moyenne: 54.4, ecartType: 6.6 }, gauche: { moyenne: 50.7, ecartType: 6.3 } })
    expect(six.Femme).toEqual({ droite: { moyenne: 57.9, ecartType: 5.3 }, gauche: { moyenne: 54.2, ecartType: 5.6 } })
    expect(douze.Homme.droite).toEqual({ moyenne: 74.6, ecartType: 8.3 })
    expect(dixHuit.Femme.gauche).toEqual({ moyenne: 76, ecartType: 8.5 })
  })
})
