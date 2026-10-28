# TrameErgo

Génère des bilans d'ergothérapie Word, sur tablette et sur Windows. Une seule
application, `tablette/` (web, hors ligne), sert les deux : dans le
navigateur des tablettes et empaquetée par Tauri en `.exe` pour Windows.
Textes visibles, commentaires et messages de commit en français.

## Structure

- `contenu/` : le contenu de l'application.
  - `questionnaire.json` : toutes les listes de choix et les phrases du bilan.
    Changer une liste ne demande que de modifier ce fichier. Un trait de
    `caractere` formulé avec un verbe (« teste souvent le cadre ») porte un
    `infinitif` : le bilan l'écrit alors sans « est » ni « d'être ».
  - `bilan.docx` : modèle Word unique du bilan, lisible par un humain :
    champs simples `{champ}` (syntaxe docxtemplater), sans conditions
    `{#…}` (un test les refuse), mots accordés au sexe par des champs (`{il_elle}`,
    `{Il_Elle}`, `{ne_e}`, `{seul_e}`, `{type_bilan}`). Les activités OT Hope
    vont dans `{niveau_domaine}` (`{aide_maison}`…), construits à partir des
    identifiants du questionnaire.
- `formulaire/` : questionnaire des parents. `creer-formulaire.gs` crée le
  Google Form (grilles aux niveaux OT Hope), `questionnaire-parents.gs` est
  le script de lecture publié en application web ; mode d'emploi dans
  `formulaire/README.md`.
- `tablette/` : l'application (Vue 3, TypeScript, Vite), installable depuis
  le navigateur et utilisable hors ligne (service worker, vite-plugin-pwa).
  Aucun serveur : le bilan est rempli sur l'appareil par docxtemplater et le
  brouillon reste sur l'appareil (localStorage). Seul accès réseau : le script
  Google du questionnaire des parents, s'il est relié.
  - `src-tauri/` : version Windows (Tauri 2, WebView2, installateur NSIS par
    utilisateur). `tauri.conf.json` prend la version de `package.json` ;
    `capabilities/default.json` n'autorise, dans `Documents\TrameErgo`, que
    la création du dossier, le test d'existence d'un bilan, son écriture et
    son ouverture, plus une fenêtre de message (plugin dialog). La CSP de
    `tauri.conf.json` n'ouvre le réseau qu'à `script.google.com` (et
    `script.googleusercontent.com`, où il redirige).
  - `src/ordinateur.ts` : sous Tauri, le bilan est enregistré dans
    `Documents\TrameErgo` et ouvert dans Word ; dans un navigateur, il est
    téléchargé ou partagé. Tout le reste est commun.
  - `src/bilan.ts` : réponses (`Bilan`) et valeur de chaque champ du modèle
    (`champs`). Pas de valeur par défaut pour les choix cliniques.
    `obligatoires` : réponses à remplir pour quitter chaque écran ; le
    modèle les écrit sans condition. `reevaluation` : nouveau bilan d'un
    enfant déjà vu.
  - `src/questionnaireParents.ts` : questionnaire des parents (Google Forms) :
    recherche par nom auprès du script `formulaire/questionnaire-parents.gs`
    (adresse et clé propres à l'appareil, seul accès réseau de l'application)
    et pré-remplissage des réponses au même libellé que l'application (ou
    équivalence déclarée, ou libellé rapproché sans ambiguïté).
  - `src/historique.ts` : bilans créés sur l'appareil (localStorage), avec
    leurs réponses ; sauvegarde et import en `.json`.
  - `src/ecrans/` : accueil (nouveau, reprendre, historique), nouveau bilan
    (nom de l'enfant, questionnaire des parents), réglages et historique.
  - `src/reprise.ts` : relit le brouillon (format `VERSION_BROUILLON`) et
    retire, en les signalant, les réponses absentes du questionnaire.
  - `src/etapes/` : un écran par étape, `src/composants/` : puces, segments,
    choix ordonnés (grosses cibles tactiles).
  - `tests/bilan.test.ts` : vérifie que `champs` fournit exactement les champs
    (et conditions) de `contenu/bilan.docx` et remplit le vrai modèle. Le
    relancer après avoir modifié le contenu. `tests/reprise.test.ts` : reprise
    des brouillons.
    `tests/historique.test.ts` : historique. `tests/questionnaireParents.test.ts` :
    questionnaire des parents. `tests/questionnaire.test.ts` : règles de
    `questionnaire.json` (doublons, identifiants, latéralités, phrases).
    `e2e/` : parcours Playwright sur l'application construite, avec Chromium
    et WebKit (iPad).
  - `npm test`, `npm run build`, `npm run e2e`, `npx tauri build` (Windows).

## CI et livraison

`.github/workflows/tablette.yml` teste et construit l'application à chaque
PR vers `main` et à chaque push sur `main` :

- job `tablette` : vérifie que `package.json`, `src-tauri/Cargo.toml`,
  `Cargo.lock` ont la même version et que `CHANGELOG.md` a sa section, puis
  `npm test`, `npm run build` et `npm run e2e` ; sur `main`, le job
  `publier` met `dist/` sur GitHub Pages (sans numéro de version). Le
  brouillon est stocké pour toute l'adresse `flo91360.github.io` : ne publier
  aucun autre site GitHub Pages depuis ce compte (voir le README).
- job `build` (Windows, après `tablette`) : `npx tauri build`, installateur
  `TrameErgo-Installation-<version>.exe` en artefact
  (`TrameErgo-Windows-Tauri`). PlaniFiKateur exige ce job avant de fusionner.
  Une nouvelle `version` de `tablette/package.json` arrivée sur `main` publie
  la Release `v<version>` avec l'installateur ; une version déjà publiée n'est
  pas remplacée. PlaniFiKateur archive les `.exe` des Releases dans Google
  Drive.
- **Chaque PR livre une nouvelle version** : elle augmente `version` dans
  `tablette/package.json`, `src-tauri/Cargo.toml` et `Cargo.lock` (dernier
  chiffre en général : 1.2.3 → 1.2.4 ; `npm version <v> --no-git-tag-version`
  puis `cargo metadata` dans `src-tauri/`) et ajoute à `CHANGELOG.md` la
  section `## [<version>] - <date>` avec ses modifications. Sur une PR, le
  job `tablette` échoue si la version n'est pas supérieure à celle de
  `main`. Si `main` a avancé entre-temps, reprendre la version suivante.

Ne pas committer `tablette/node_modules/`, `tablette/dist/`,
`tablette/installateur/` ni `tablette/src-tauri/target/` et `gen/`.

## Fusion des PR

Quand la CI est verte sur une PR (tous les jobs, dont `build` Windows, sur le
dernier commit) et qu'elle n'a pas de conflit, Claude la fusionne dans `main`
automatiquement, sans demander l'accord de l'utilisateur.
