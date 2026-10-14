# TrameErgo

Application Windows (C++ / Qt 6, qmake) qui génère des bilans d'ergothérapie
Word. Textes visibles, commentaires et messages de commit en français.

## Structure

- `TrameErgo.pro` : projet qmake. Tout fichier ajouté doit y être déclaré dans
  `SOURCES`, `HEADERS` ou `FORMS`. `VERSION = x.y.z` fixe la version de l'exe,
  de l'installateur et de la Release.
- `mainwindow.*` puis `interface0` à `interface5` (et `interface2_x`,
  `interface4_7`, `interface4_8`) : écrans successifs du questionnaire. Chaque
  écran a son `.ui` (Qt Designer), son `.h` et son `.cpp`. `interface4` est
  l'écran OT Hope, ouvert une fois par domaine de `otHope/domaines`.
- `contenu/` : le contenu, indépendant de Qt, à réutiliser tel quel par une
  future version tablette.
  - `questionnaire.json` : toutes les listes de choix et les phrases du bilan.
    Intégré à l'exécutable (`contenu.qrc`), lu par `Questionnaire::liste`,
    `valeur` et `phrase` avec un chemin `"scolarite/matieres"`. Changer une
    liste ne demande que de modifier ce fichier.
  - `bilan.docx` : modèle Word unique du bilan. Champs `{champ}` (syntaxe
    docxtemplater), mots accordés au sexe par des champs (`{il_elle}`,
    `{Il_Elle}`, `{ne_e}`, `{seul_e}`, `{type_bilan}`). Les activités OT Hope
    vont dans `{niveau_domaine}` (`{aide_maison}`…), construits à partir des
    identifiants du questionnaire. Installé dans
    `%LOCALAPPDATA%\TrameErgo\contenu` (écrasé à chaque installation : modifier
    celui du dépôt).
- `listecases.*` : liste de cases à cocher remplie depuis le questionnaire
  (QWidget promu en `ListeCases` dans les `.ui`).
- `word.*` : pilotage de Microsoft Word par ActiveQt (`QAxObject`).
  `Word::creerBilan` copie le modèle dans `Documents\TrameErgo`, puis chaque
  écran ouvre le bilan (`Word::ouvrir`) et remplace ses champs
  (`Word::replaceText`, `Word::replaceTextFromZoneText` pour la page de garde,
  casse respectée). Vérifier les pointeurs : Word peut manquer.
- `patient.*` : données partagées entre les écrans.
- `outils/verifier_contenu.py` : vérifie que chaque champ `{…}` du modèle est
  remplacé par le code et inversement, et que chaque chemin lu dans
  `questionnaire.json` existe. Lancé par la CI ; le relancer après avoir
  modifié le contenu ou un `replaceText` : `python outils/verifier_contenu.py`.
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
