# TrameErgo

Application Windows (C++ / Qt 6, qmake) qui génère des bilans d'ergothérapie
Word. Textes visibles, commentaires et messages de commit en français.

## Structure

- `TrameErgo.pro` : projet qmake. Tout fichier ajouté doit y être déclaré dans
  `SOURCES`, `HEADERS` ou `FORMS`. `VERSION = x.y.z` fixe la version de l'exe,
  de l'installateur et de la Release.
- `mainwindow.*` puis `interface0` à `interface5` (et `interface2_x`,
  `interface4_x`) : écrans successifs du questionnaire. Chaque écran a son
  `.ui` (Qt Designer), son `.h` et son `.cpp`.
- `word.*` : pilotage de Microsoft Word par ActiveQt (`QAxObject`).
  `Word::modele("interfaceN")` donne le modèle de l'écran pour le sexe et l'âge
  du patient, `Word::copieCree` crée le bilan à partir d'un modèle,
  `Word::copieColle` ajoute un modèle à la fin du bilan, `Word::insereModele`
  l'insère à la place d'un champ, `Word::replaceText` remplace les champs
  `i_…` des modèles par les réponses. Utiliser `Word::ouvrir` et vérifier les
  pointeurs : Word ou un modèle peuvent manquer.
- `patient.*` : données partagées entre les écrans. `sexePatient` et
  `typeBilan` sont les noms des dossiers de modèles.
- `arborescence/<Femme|Homme>/<Enfant|Ado>/interfaceN/interfaceN.docx` :
  modèles Word, un par écran et par variante. `interface4` est inséré à la
  place du champ `i_interface4` d'`interface3`. Installés dans
  `%LOCALAPPDATA%\TrameErgo\arborescence`, lus via `Word::pathToArbo`. Les
  bilans sont enregistrés dans `Documents\TrameErgo`.
- `outils/verifier_modeles.py` : vérifie que chaque champ `i_…` des modèles est
  remplacé par le code et inversement, que chaque variante a tous ses modèles et
  qu'aucun champ n'en contient un autre. Lancé par la CI ; le relancer après
  avoir modifié un modèle ou un `replaceText` : `python outils/verifier_modeles.py`.
- `installer/TrameErgo.iss` : installateur Inno Setup.
- `interface1_old.*` et `interface_piliz1.*` ne sont pas compilés.

## Compilation

ActiveQt n'existe que sous Windows : le projet ne compile pas sous Linux.
`.github/workflows/build-windows.yml` (job `build`) compile avec Qt 6.8.3 et
MinGW 13.1, rassemble les DLL (windeployqt) et fabrique l'installateur. Sous
Windows avec Qt Creator : ouvrir `TrameErgo.pro`, kit Desktop Qt 6 MinGW 64 bits.

## Livraison

- Chaque livraison augmente `VERSION` dans `TrameErgo.pro`. Une nouvelle version
  arrivée sur `main` publie la Release `v<VERSION>` avec l'installateur ; une
  version déjà publiée n'est pas remplacée. PlaniFiKateur archive ses `.exe`
  dans Google Drive.
- Ne pas committer `build/`, `release/`, `deploy/`, `Output/` ni les fichiers
  `*.pro.user` de Qt Creator.
