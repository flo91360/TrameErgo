# Journal des modifications

Toutes les modifications notables de TrameErgo, version par version. La
version est celle de `tablette/package.json` ; chaque version arrivée sur
`main` est publiée dans les
[Releases](https://github.com/flo91360/TrameErgo/releases) avec
l'installateur Windows.

Les modifications pas encore publiées vont dans « Non publié » ; elles
passent sous un nouveau numéro de version au moment de la livraison.

## Non publié

### Ajouté

- Ce journal des modifications (`CHANGELOG.md`).

## [1.2.0] - 2026-10-18

Une seule application pour la tablette et Windows.

### Ajouté

- Application tablette (`tablette/`, Vue 3) installable depuis le navigateur
  et utilisable hors ligne, publiée sur
  [GitHub Pages](https://flo91360.github.io/TrameErgo/). Le bilan est rempli
  sur l'appareil, rien n'est envoyé sur Internet.
  - Dix étapes tactiles : patient, demande, suivis, scolarité, OT Hope par
    domaine (« Rien à signaler » par défaut), objectifs numérotés dans
    l'ordre du toucher, aménagements, création du bilan.
  - Âge calculé à la date de passation, modifiable.
  - Brouillon enregistré sur l'appareil à chaque modification et repris au
    retour ; bouton « Nouveau bilan » pour l'effacer.
  - Bilan téléchargé ou partagé (Word, Mail…).
- Version Windows de cette même application, empaquetée par Tauri :
  installateur `TrameErgo-Installation-<version>.exe` installé pour
  l'utilisateur courant, sans droit administrateur. Le bilan est enregistré
  dans `Documents\TrameErgo` puis ouvert dans Word ; Word n'est plus
  nécessaire pour le créer.
- `TESTER.md` : vérifications à faire sur Windows et sur tablette.
- README réécrit : fonctionnement de l'application et façon de l'enrichir.

### Supprimé

- Ancienne application Windows C++/Qt, son installateur Inno Setup et sa
  compilation en CI. Les Releases fournissent désormais l'installateur Tauri.

## [1.1.0] - 2026-10-14

Le contenu du bilan sort du code. Cette version inclut aussi les corrections
prévues pour une 1.0.1, jamais publiée séparément.

### Modifié

- `contenu/questionnaire.json` regroupe toutes les listes de choix et les
  phrases du bilan (classes, motifs, troubles, professionnels, fréquences,
  scolarité, 135 activités OT Hope, aménagements, accord des parents).
  Changer une liste ne demande plus de toucher au code.
- Un seul modèle Word, `contenu/bilan.docx`, au lieu de 20 ; les mots sont
  accordés au sexe par des champs (`{il_elle}`, `{ne_e}`…).
- Un écran OT Hope par domaine avec « Rien à signaler » par défaut ; une
  réponse peut être corrigée.

### Corrigé

- Le modèle était toujours celui d'une fille enfant : il est maintenant
  choisi selon le sexe et l'âge.
- La partie OT Hope et objectifs n'était jamais ajoutée au bilan ; la page
  aménagements et loisirs n'existait pas.
- Âge calculé en mois révolus (10 ans et 11 mois s'affichait 11 ans et
  0 mois).
- Fratrie : « () » quand « Bonne » restait cochée par défaut ; « Enfant
  unique » ne se décochait plus.
- Objectifs : « Aucun » par défaut, sans doublons ; objectifs et remarques
  des parents écrits dans le bilan.
- Liste des troubles en double, « vit avec avec ses 2 parents », tirets
  doublés dans les listes à puces, liste du comportement en classe collée au
  titre, latéralité accordée au masculin.
- Écran de fin : une activité par ligne, message avec le chemin du bilan,
  Word fermé s'il n'a plus de document ouvert.
- Contrôle en CI que les champs du modèle Word correspondent au code.

## [1.0.0] - 2026-10-12

Première version publiée : application Windows C++/Qt.

### Ajouté

- Compilation de l'application et installateur Windows sur GitHub ; Release
  publiée pour chaque nouvelle version, jamais remplacée.
- Installation par utilisateur, modèles copiés dans
  `%LOCALAPPDATA%\TrameErgo`.

### Corrigé

- Ouverture des modèles Word (noms et chemins des écrans 1, 2, 3 et 5).
- Message clair quand Word est absent ou qu'un modèle manque, au lieu d'un
  plantage ; dossier `Documents\TrameErgo` créé si besoin.

[1.2.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.2.0
[1.1.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.1.0
[1.0.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.0.0
