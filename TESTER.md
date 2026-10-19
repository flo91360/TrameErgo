# Tester TrameErgo

Liste de vérifications avant de diffuser une nouvelle version, sous Windows
(l'application empaquetée en `.exe`) et sur tablette. Noter toute anomalie,
avec une capture d'écran ou le `.docx`.

## 1. Version Windows

### Installer

1. Sur un PC Windows, ouvrir les
   [Releases](https://github.com/flo91360/TrameErgo/releases) et télécharger
   `TrameErgo-Installation-<version>.exe` de la version à tester.
   Pour une PR pas encore publiée : se connecter à GitHub, ouvrir son
   exécution « Application tablette et Windows » dans
   [Actions](https://github.com/flo91360/TrameErgo/actions) et télécharger
   l'artefact **TrameErgo-Windows-Tauri** (zip, conservé 90 jours).
2. Lancer l'installateur. S'il est bloqué par SmartScreen (installateur non
   signé) : « Informations complémentaires », puis « Exécuter quand même ».
   Aucun droit administrateur n'est demandé.

### Vérifier

- [ ] L'application démarre depuis le menu Démarrer.
- [ ] Remplir toutes les étapes avec un patient fictif, puis « Créer le bilan
      Word » à l'étape « Bilan » : le fichier
      `Bilan_ergotherapie_Nom_Prénom_mois_année.docx` apparaît dans
      `Documents\TrameErgo` et s'ouvre dans Word.
- [ ] Dans le bilan : aucun `{champ}` restant, page de garde correcte,
      accords il/elle et né/née, listes OT Hope (avec aide, avec difficulté…),
      ordre des objectifs.
- [ ] Refaire un bilan en changeant fille/garçon et enfant/adolescent : titre
      et accords suivent.
- [ ] Laisser des choix à « — à renseigner — » : l'écran Bilan les liste, et
      le Word n'a pas de phrase cassée (« Dr , à . », « () »…).
- [ ] Fermer l'application en cours de saisie et la rouvrir : les réponses
      sont toujours là.
- [ ] Recréer le même bilan : une fenêtre Windows propose « Remplacer »,
      « Garder les deux » (enregistre `…_2.docx` à côté) et « Annuler »
      (rien n'est écrit) ; vérifier les trois.
- [ ] Au clavier, sur l'écran Patient : Tab arrive sur « Sexe », les flèches
      passent de Fille à Garçon.
- [ ] Remplacer un bilan pendant qu'il est ouvert dans Word : un message
      demande s'il est déjà ouvert dans Word, sans plantage.
- [ ] Wi-Fi coupé, créer un bilan : tout fonctionne.

## 2. Version tablette

- [ ] Ouvrir <https://flo91360.github.io/TrameErgo/> dans Safari (iPad) ou
      Chrome (Android), puis l'ajouter à l'écran d'accueil (Safari :
      Partager, puis « Sur l'écran d'accueil »).
- [ ] L'ouvrir une fois avec du réseau, puis passer en mode avion, la
      relancer depuis l'icône et créer un bilan : il s'ouvre dans Word, Pages
      ou Fichiers.
- [ ] Mêmes vérifications du contenu du bilan que sous Windows.
