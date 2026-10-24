# Questionnaire des parents (Google Forms)

Les parents remplissent le questionnaire pré-bilan en ligne, avant le bilan.
À la création d'un bilan, TrameErgo retrouve leurs réponses au nom de
l'enfant et pré-remplit les écrans. Il ne fait que lire les réponses.

- [`creer-formulaire.gs`](creer-formulaire.gs) crée le formulaire, une fois,
  dans le Google Drive de celui qui l'exécute (activités en grilles, comme
  les écrans OT Hope).
- [`questionnaire-parents.gs`](questionnaire-parents.gs) laisse TrameErgo
  lire les réponses : à installer une fois par formulaire.
- [`fiche-patient.gs`](fiche-patient.gs) crée une fiche patient Word dans
  le Google Drive à chaque réponse reçue (voir plus bas).

## Relier un formulaire à TrameErgo

Le compte qui installe le script doit être propriétaire ou éditeur du
formulaire.

1. Ouvrir [script.google.com](https://script.google.com), « Nouveau projet ».
   Effacer le contenu, coller tout `questionnaire-parents.gs`.
2. Coller l'adresse de modification du formulaire (celle qui finit par
   `/edit`) dans `ADRESSE_FORMULAIRE`, enregistrer.
3. Choisir `installer`, puis « Exécuter », et autoriser l'accès. Le journal
   d'exécution affiche le titre du formulaire et son nombre de réponses.
4. « Déployer » > « Nouveau déploiement » > type « Application web » :
   exécuter en tant que « Moi », accès « Tout le monde ».
5. Choisir `lienDeLiaison`, puis « Exécuter » : le journal affiche le **lien
   de liaison** (adresse de l'application web suivie de `#cle=…`). Si Google
   ne lui donne pas l'adresse de l'application web, il affiche seulement
   `#cle=…` : le coller à la fin de l'URL copiée dans « Déployer » > « Gérer
   les déploiements » (elle finit par `/exec`). La clé est aussi visible dans
   « Paramètres du projet » > « Propriétés du script » (`CLE`).
6. Dans TrameErgo, à l'accueil, « Questionnaire des parents : Régler » :
   coller ce lien, une fois par appareil. Il reste sur l'appareil après les
   mises à jour de TrameErgo ; il faut le recoller seulement après avoir
   effacé les données du navigateur, désinstallé l'application ou changé
   d'appareil.

Changer de formulaire : coller la nouvelle adresse dans `ADRESSE_FORMULAIRE`,
enregistrer et exécuter `installer` ; le lien de liaison ne change pas.

Mettre à jour le script : remplacer son code, enregistrer, puis « Déployer » >
« Gérer les déploiements » > crayon > Version : « Nouvelle version » >
« Déployer ». L'adresse et le lien de liaison ne changent pas.

## Ce que voit l'application

Le script ne répond qu'aux demandes qui portent la bonne clé, et ne renvoie
que les réponses de l'enfant demandé (comparaison du nom sans majuscules,
accents ni espaces, dans les deux ordres). `changerCle` crée une nouvelle
clé et affiche le nouveau lien : les appareils qui avaient l'ancien perdent
l'accès.

Le nom est lu dans la question « Nom et Prénom de l'enfant », ou dans les
questions « Nom » et « Prénom » placées sous un titre « Enfant ». Chaque
réponse est envoyée avec le titre de l'encadré ou de la section où elle se
trouve (« Parent 1 »…) : des questions courtes comme « Nom » peuvent donc se
répéter d'un encadré à l'autre. Les questions « Nom » et « Ville » sous un
titre « Médecin traitant » remplissent le médecin de l'écran Patient. Les lignes des
grilles ne sont pré-remplies que si l'activité existe dans
`contenu/questionnaire.json` avec le même libellé, aux majuscules et aux
accents près, et si la colonne cochée est « Rien à signaler » ou un niveau de
`otHope.niveaux` (« Avec aide »…). Les listes « cotation 0 à 4 » de l'ancien
formulaire ne sont pas reprises : leurs niveaux n'ont pas d'équivalent dans
l'application. La question « Pour quelle(s) raison(s) le bilan est
souhaité ? En lien avec quel trouble diagnostiqué ? » coche, dans l'écran
Demande (« Anamnèse / troubles »), les troubles au même libellé ; ses autres
réponses (« Autre »…) sont reportées telles quelles dans « Autre trouble »,
écrit dans le bilan à la suite des troubles cochés. Les autres réponses sont
montrées telles quelles dans l'encadré « Réponses des parents ».

## Fiche patient Word à chaque réponse

[`fiche-patient.gs`](fiche-patient.gs) s'ajoute au projet Apps Script de
`questionnaire-parents.gs` (même compte, même formulaire). À chaque réponse
envoyée, il crée dans le Google Drive, dossier « ERGO/questionnaire
pré-bilan » (créé s'il manque), un Word
`Fiche_patient_<NOM>_<Prénom>_<date>.docx` avec toutes les réponses, rangées
sous les titres du formulaire (sections et encadrés). Les grilles d'activités
deviennent des tableaux, les questions sans réponse sont omises.

1. Dans le projet Apps Script du questionnaire, « + » > « Script », nommer le
   fichier `fiche-patient`, coller tout `fiche-patient.gs`, enregistrer.
2. Choisir `installerFichePatient`, « Exécuter », et accepter les
   autorisations (Drive, Documents, Forms et « se connecter à un service
   externe », qui sert à convertir la fiche en Word).
3. Pour vérifier : `essayerFichePatient` crée la fiche de la dernière réponse
   reçue ; le journal donne son lien.

`retirerFichePatient` arrête la création automatique. En cas d'erreur, Google
envoie un courriel au propriétaire du script ; les exécutions sont listées
dans « Exécutions ».

Les fiches contiennent des données de santé d'enfants : les laisser dans un
Google Drive non certifié HDS le moins longtemps possible, et ne pas partager
le dossier.
