# Tester TrameErgo

Liste de vérifications avant de diffuser une nouvelle version, sous Windows
(l'application empaquetée en `.exe`) et sur tablette. Noter toute anomalie,
avec une capture d'écran ou le `.docx`.

## 1. Version Windows

### Installer

1. Sur un PC Windows, se connecter à GitHub (les artefacts ne se téléchargent
   que connecté ; ils sont conservés 90 jours).
2. Ouvrir [Actions](https://github.com/flo91360/TrameErgo/actions), puis la
   dernière exécution verte « Application tablette et Windows » sur `main`.
3. En bas de la page, dans **Artifacts**, télécharger
   **TrameErgo-Windows-Tauri** et décompresser le zip.
4. Lancer l'installateur. S'il est bloqué par SmartScreen (installateur non
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
- [ ] Fermer l'application en cours de saisie et la rouvrir : les réponses
      sont toujours là.
- [ ] Recréer le même bilan : l'application demande s'il faut le remplacer.
      « Annuler » enregistre `…_2.docx` à côté ; « OK » le remplace.
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
