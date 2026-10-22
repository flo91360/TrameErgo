# Questionnaire des parents (Google Forms)

Les parents remplissent le questionnaire pré-bilan en ligne, avant le bilan.
À la création d'un bilan, TrameErgo retrouve leurs réponses au nom de
l'enfant et pré-remplit les écrans. Il ne fait que lire les réponses.

- [`creer-formulaire.gs`](creer-formulaire.gs) crée le formulaire, une fois,
  dans le Google Drive de celui qui l'exécute (activités en grilles, comme
  les écrans OT Hope).
- [`questionnaire-parents.gs`](questionnaire-parents.gs) laisse TrameErgo
  lire les réponses : à installer une fois par formulaire.

## Relier un formulaire à TrameErgo

Le compte qui installe le script doit être propriétaire ou éditeur du
formulaire.

1. Ouvrir [script.google.com](https://script.google.com), « Nouveau projet ».
   Effacer le contenu, coller tout `questionnaire-parents.gs`.
2. Coller l'adresse de modification du formulaire (celle qui finit par
   `/edit`) dans `ADRESSE_FORMULAIRE`, enregistrer.
3. Choisir `installer`, puis « Exécuter », et autoriser l'accès. Le journal
   d'exécution affiche le nombre de réponses et la **clé** à coller dans
   TrameErgo.
4. « Déployer » > « Nouveau déploiement » > type « Application web » :
   exécuter en tant que « Moi », accès « Tout le monde ». Copier l'**adresse
   de l'application web** (elle finit par `/exec`).
5. Dans TrameErgo, à l'accueil, « Questionnaire des parents : Régler » :
   coller l'adresse et la clé, sur chaque appareil.

Changer de formulaire : refaire les étapes avec la nouvelle adresse, puis un
nouveau déploiement.

## Ce que voit l'application

Le script ne répond qu'aux demandes qui portent la bonne clé, et ne renvoie
que les réponses de l'enfant demandé (comparaison du nom sans majuscules,
accents ni espaces, dans les deux ordres). `changerCle` crée une nouvelle
clé : les appareils qui avaient l'ancienne perdent l'accès.

Le nom est lu dans la question « Nom et Prénom de l'enfant ». Les lignes des
grilles ne sont pré-remplies que si l'activité existe dans
`contenu/questionnaire.json` avec le même libellé, aux majuscules et aux
accents près, et si la colonne cochée est « Rien à signaler » ou un niveau de
`otHope.niveaux` (« Avec aide »…). Les listes « cotation 0 à 4 » de l'ancien
formulaire ne sont pas reprises : leurs niveaux n'ont pas d'équivalent dans
l'application. Les autres réponses sont montrées telles quelles dans
l'encadré « Réponses des parents ».
