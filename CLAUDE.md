# TrameErgo

Génère des bilans d'ergothérapie Word, sur tablette et sur Windows. Une seule
application, `tablette/` (web, hors ligne), sert les deux : dans le
navigateur des tablettes et empaquetée par Tauri en `.exe` pour Windows.
Textes visibles, commentaires et messages de commit en français.

## Structure

- `contenu/` : le contenu de l'application.
  - `questionnaire.json` : toutes les listes de choix et les phrases du bilan.
    Changer une liste ne demande que de modifier ce fichier.
  - `bilan.docx` : modèle Word unique du bilan. Champs `{champ}` (syntaxe
    docxtemplater), mots accordés au sexe par des champs (`{il_elle}`,
    `{Il_Elle}`, `{ne_e}`, `{seul_e}`, `{type_bilan}`). Les activités OT Hope
    vont dans `{niveau_domaine}` (`{aide_maison}`…), construits à partir des
    identifiants du questionnaire.
- `tablette/` : l'application (Vue 3, TypeScript, Vite), installable depuis
  le navigateur et utilisable hors ligne (service worker, vite-plugin-pwa).
  Aucun serveur : le bilan est rempli sur l'appareil par docxtemplater et le
  brouillon reste sur l'appareil (localStorage).
  - `src-tauri/` : version Windows (Tauri 2, WebView2, installateur NSIS par
    utilisateur). `tauri.conf.json` prend la version de `package.json` ;
    `capabilities/default.json` n'autorise que l'écriture dans
    `Documents\TrameErgo` et l'ouverture des bilans.
  - `src/ordinateur.ts` : sous Tauri, le bilan est enregistré dans
    `Documents\TrameErgo` et ouvert dans Word ; dans un navigateur, il est
    téléchargé ou partagé. Tout le reste est commun.
  - `src/bilan.ts` : réponses (`Bilan`) et valeur de chaque champ du modèle
    (`champs`).
  - `src/etapes/` : un écran par étape, `src/composants/` : puces, segments,
    choix ordonnés (grosses cibles tactiles).
  - `tests/bilan.test.ts` : vérifie que `champs` fournit exactement les champs
    de `contenu/bilan.docx` et remplit le vrai modèle. Le relancer après avoir
    modifié le contenu.
  - `npm test`, `npm run build`, `npx tauri build` (Windows).

## CI et livraison

`.github/workflows/tablette.yml` teste et construit l'application à chaque
push et PR :

- job `tablette` : `npm test` et `npm run build` ; sur `main`, le job
  `publier` met `dist/` sur GitHub Pages (sans numéro de version).
- job `build` (Windows) : `npx tauri build`, installateur
  `TrameErgo-Installation-<version>.exe` en artefact
  (`TrameErgo-Windows-Tauri`). PlaniFiKateur exige ce job avant de fusionner.
  Une nouvelle `version` de `tablette/package.json` arrivée sur `main` publie
  la Release `v<version>` avec l'installateur ; une version déjà publiée n'est
  pas remplacée. Chaque livraison Windows augmente donc cette version (et
  celle de `src-tauri/Cargo.toml`). PlaniFiKateur archive les `.exe` des
  Releases dans Google Drive.
- `CHANGELOG.md` répertorie les modifications de chaque version. Toute
  modification visible pour l'utilisateur y est ajoutée sous « Non publié » ;
  quand la version augmente, cette section prend le numéro et la date de la
  livraison.

Ne pas committer `tablette/node_modules/`, `tablette/dist/`,
`tablette/installateur/` ni `tablette/src-tauri/target/` et `gen/`.

## Fusion des PR

Quand la CI est verte sur une PR (tous les jobs, dont `build` Windows, sur le
dernier commit) et qu'elle n'a pas de conflit, Claude la fusionne dans `main`
automatiquement, sans demander l'accord de l'utilisateur.
