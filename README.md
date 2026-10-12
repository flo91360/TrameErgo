# TrameErgo

Logiciel Windows qui génère automatiquement des bilans d'ergothérapie au format
Word, à partir d'un questionnaire et de modèles `.docx`.

## Installer

Télécharger `TrameErgo-Installation-<version>.exe` depuis les
[Releases](https://github.com/flo91360/TrameErgo/releases) et lancer
l'installation. Microsoft Word doit être installé. Les bilans sont enregistrés
dans `Documents\TrameErgo`.

## Développer

Ouvrir `TrameErgo.pro` dans Qt Creator (Qt 6, kit MinGW 64 bits, module
ActiveQt). Chaque push compile l'application et l'installateur sur GitHub
Actions ; augmenter `VERSION` dans `TrameErgo.pro` publie une nouvelle Release.
Voir `CLAUDE.md` pour l'organisation du code.
