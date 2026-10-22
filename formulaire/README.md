# Questionnaire des parents (Google Forms)

Les parents remplissent le questionnaire pré-bilan en ligne. À la création
d'un bilan, TrameErgo retrouve leurs réponses au nom de l'enfant et
pré-remplit les écrans. Tout passe par un seul script Google,
[`questionnaire-parents.gs`](questionnaire-parents.gs), à installer une fois.

## Installer le script

1. Ouvrir [script.google.com](https://script.google.com), « Nouveau projet ».
   Effacer le contenu, coller tout `questionnaire-parents.gs`, enregistrer.
2. Choisir `creerFormulaire` en haut, puis « Exécuter », et autoriser l'accès.
   Le journal d'exécution affiche le lien du formulaire à envoyer aux parents
   et la **clé** à coller dans TrameErgo.
   Formulaire déjà créé par une version précédente du script : coller son
   adresse de modification dans `ADRESSE_FORMULAIRE_EXISTANT` et exécuter
   `relierFormulaireExistant` à la place.
3. « Déployer » > « Nouveau déploiement » > type « Application web » :
   exécuter en tant que « Moi », accès « Tout le monde ». Copier l'**adresse
   de l'application web** (elle finit par `/exec`).
4. Dans TrameErgo, à l'accueil, « Questionnaire des parents » : coller
   l'adresse et la clé, sur chaque appareil.

## Ce que voit l'application

Le script ne répond qu'aux demandes qui portent la bonne clé, et ne renvoie
que les réponses de l'enfant demandé (comparaison du nom sans majuscules,
accents ni espaces, dans les deux ordres). `changerCle` crée une nouvelle
clé : les appareils qui avaient l'ancienne perdent l'accès.

Les lignes des grilles ne sont pré-remplies que si l'activité existe dans
`contenu/questionnaire.json` avec le même libellé, aux majuscules et aux
accents près. Les colonnes doivent rester les niveaux de l'application
(« Rien à signaler » puis ceux de `otHope.niveaux`) : un test le vérifie.
