# TrameErgo

Génère automatiquement des bilans d'ergothérapie au format Word, à partir d'un
questionnaire et d'un modèle `.docx`. La même application fonctionne sur
tablette (dans le navigateur) et sur Windows (installateur `.exe`).

## Tablette (iPad, Android)

Ouvrir <https://flo91360.github.io/TrameErgo/> dans le navigateur de la
tablette, puis l'ajouter à l'écran d'accueil (Safari : Partager, puis « Sur
l'écran d'accueil »). Elle fonctionne ensuite sans réseau. Le bilan Word est
créé sur la tablette et s'ouvre dans Word, Pages ou Fichiers. Les réponses
restent sur la tablette : rien n'est envoyé sur Internet.

## Windows

Télécharger `TrameErgo-Installation-<version>.exe` depuis les
[Releases](https://github.com/flo91360/TrameErgo/releases) et lancer
l'installation. Les bilans sont enregistrés dans `Documents\TrameErgo`.

La nouvelle version Windows (la même application que sur tablette) est en
cours de validation : son installateur est l'artefact `TrameErgo-Windows-Tauri`
de la dernière exécution « Application tablette et Windows » dans
[Actions](https://github.com/flo91360/TrameErgo/actions). Elle crée le bilan
sans Word, puis l'ouvre dans Word. Les Releases fournissent encore l'ancienne
application Windows, qui demande Microsoft Word. Les vérifications à faire
avant de passer à la nouvelle version sont dans [TESTER.md](TESTER.md).

## Développer

- Contenu commun : `contenu/questionnaire.json` (listes et phrases) et
  `contenu/bilan.docx` (modèle Word).
- Windows : ouvrir `TrameErgo.pro` dans Qt Creator (Qt 6, kit MinGW 64 bits,
  module ActiveQt). Chaque push compile l'application et l'installateur sur
  GitHub Actions ; augmenter `VERSION` dans `TrameErgo.pro` publie une nouvelle
  Release.
- Application (tablette et Windows) : dans `tablette/`, `npm install`, puis
  `npm run dev` (développement), `npm test`, `npm run build`, et
  `npx tauri build` pour l'installateur Windows (Rust nécessaire). Chaque
  arrivée sur `main` publie l'application sur GitHub Pages.

Voir `CLAUDE.md` pour l'organisation du code.
