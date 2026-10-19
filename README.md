# TrameErgo

TrameErgo transforme les réponses à un questionnaire d'ergothérapie en un
bilan Word modifiable. Ce guide explique son fonctionnement et comment
l'enrichir, pour l'ergothérapeute qui prépare le contenu et pour la personne
qui l'aide à modifier le logiciel.

Trois éléments doivent correspondre : **la question à l'écran, la réponse
mise en forme et son emplacement dans le document Word**.

Repères dans ce guide :

- [Utiliser l'application](#utiliser-lapplication)
- [Comprendre le fonctionnement et les fichiers](#comment-fonctionne-lapplication-commune)
- [Comprendre le modèle Word, le sexe et l'âge](#le-modèle-word-le-sexe-et-lâge)
- [Enrichir le logiciel](#comment-enrichir-le-logiciel)
- [Préparer une demande d'évolution](#fiche-pour-préparer-une-nouvelle-rubrique)
- [Vérifier et diffuser une évolution](#vérifier-et-diffuser-une-évolution)

## Utiliser l'application

### Sur tablette (iPad, Android)

Ouvrir <https://flo91360.github.io/TrameErgo/> dans le navigateur, puis ajouter
l'application à l'écran d'accueil (Safari : Partager, puis « Sur l'écran
d'accueil »). Après un premier chargement complet avec une connexion, elle est
prévue pour fonctionner hors ligne. Le bilan est créé sur l'appareil, puis
téléchargé. Le bouton de partage apparaît si le navigateur le permet. On peut
ensuite l'ouvrir dans Word, Pages ou une application compatible.

### Sur Windows

Télécharger `TrameErgo-Installation-<version>.exe` dans les
[Releases](https://github.com/flo91360/TrameErgo/releases), puis lancer
l'installation (aucun droit administrateur n'est demandé). Si Windows affiche
« Windows a protégé votre ordinateur » : « Informations complémentaires »,
puis « Exécuter quand même ».

C'est la même application que sur tablette, empaquetée pour Windows par
**Tauri** (`tablette/src-tauri/`). Elle crée le document sans avoir besoin de
Word, l'enregistre dans `Documents\TrameErgo`, puis l'ouvre avec le logiciel
associé aux `.docx`, généralement Word.

L'ancienne application Windows (C++/Qt, versions 1.0.0 et 1.1.0) n'est plus
maintenue. Si elle est encore installée sur un PC, la désinstaller depuis les
paramètres de Windows (Applications) pour ne garder qu'un TrameErgo.

## Comment fonctionne l'application commune

### Les étapes d'un bilan

On avance avec « Suivant », on revient avec « Précédent » ou on touche
directement le nom d'une étape. Les dix étapes actuelles sont :

| Étape | Ce que l'on renseigne |
| --- | --- |
| Patient | Sexe, choix Enfant/Adolescent, identité, dates, scolarisation, latéralité, situation familiale, médecin et ville. |
| Demande | Personne demandeuse, motifs, troubles et situation du dossier MDPH. |
| Suivis | Professionnels et fréquence de chaque suivi, ou « Aucun ». |
| Scolarité | Comportement, difficultés, matières préférées et moins appréciées. |
| OT Hope : activités de vie quotidienne | Activités du domaine `maison` et niveau d'aide ou de difficulté. |
| OT Hope : activités de vie scolaire | Activités du domaine `ecole`. |
| OT Hope : activités de loisirs | Activités du domaine `loisirs`. |
| Objectifs | Priorités par domaine, objectifs finaux, accord et remarques des parents. |
| Aménagements et loisirs | Aménagements scolaires, activités extra-scolaires, temps libre et difficultés pendant les loisirs. |
| Bilan | Récapitulatif, création du Word, téléchargement ou ouverture, puis « Nouveau bilan ». |

Dans OT Hope, seules les activités cotées « Avec aide », « Avec difficulté »
ou « Avec grande difficulté » sont reprises dans le bilan. « Rien à signaler »
est aussi la valeur de départ : le logiciel ne distingue pas une activité
laissée sans réponse d'une activité explicitement jugée sans difficulté.

On peut choisir **au plus cinq objectifs par domaine**, puis cinq objectifs
finaux et cinq objectifs des parents, parmi les objectifs des domaines. La
numérotation suit l'ordre des choix. Si une activité revient à « Rien à
signaler », elle cesse d'être proposée et reprise comme objectif. Les autres
listes du bilan suivent généralement l'ordre du questionnaire, pas les clics.

### Sauvegarde et limites actuelles

Les réponses sont sauvegardées automatiquement sur l'appareil, dans le
stockage local de l'application. À la réouverture, le brouillon est repris.
Il existe **un seul bilan en cours**, sans liste de dossiers patients ni
synchronisation entre tablette et ordinateur. Effacer les données du
navigateur peut faire perdre le brouillon. Si le stockage est indisponible,
les réponses restent seulement en mémoire pendant la session.

« Nouveau bilan » demande confirmation, puis remplace les réponses en cours.
Les fichiers Word déjà enregistrés restent indépendants. Une correction dans
Word ne revient pas dans le questionnaire. Pour tenir compte de nouvelles
réponses, il faut générer un nouveau document. Sous Windows, si un bilan du
même nom existe déjà, l'application demande s'il faut le remplacer (les
modifications faites dans Word sont alors perdues) ou enregistrer une copie
`…_2.docx` ; un document ouvert dans Word peut empêcher le remplacement.

Le nom suit la forme `Bilan_ergotherapie_Nom_Prénom_mois_année.docx`, avec le
mois et l'année de la passation.

Les réponses ne sont pas envoyées à un serveur par l'application. Partager
ensuite un document, par exemple par mail, passe par l'application choisie.

Le bilan reste à relire et à compléter par l'ergothérapeute : le logiciel ne
pose pas de diagnostic et ne calcule pas de scores cliniques. Les choix sans
réponse évidente (classe, établissement, latéralité, mode de garde, entente,
personne demandeuse, dossier MDPH, accord des parents) commencent à « — à
renseigner — » : rien n'entre dans le bilan sans avoir été choisi. Seuls le
sexe, Enfant/Adolescent et la date de passation (le jour même) ont une valeur
de départ. L'écran final signale l'absence de prénom, nom, date de naissance
ou date de passation, les choix encore à renseigner et une date de naissance
postérieure à la passation, mais **n'empêche pas la génération** d'un bilan
incomplet : la phrase d'une réponse vide est alors absente du Word.

Il n'y a actuellement ni éditeur de questionnaire dans l'application, ni
import de modèle Word, ni assemblage de modèles séparés par rubrique.
L'enrichissement passe par les fichiers du projet, puis par une nouvelle
construction et une diffusion de l'application.

### De la saisie au document : les fichiers à connaître

```text
Écrans du questionnaire + réponses saisies
                  ↓
Règles de rédaction : accords, listes, calcul de l'âge…
                  ↓
Remplacement des repères {…} dans le modèle Word
                  ↓
Document .docx téléchargé ou enregistré dans Documents\TrameErgo
```

| Élément | Fichier | Son rôle |
| --- | --- | --- |
| Choix et certaines phrases | [`contenu/questionnaire.json`](contenu/questionnaire.json) | Listes de motifs, troubles, professionnels, activités, aménagements, etc. C'est un fichier de texte structuré. |
| Écrans | [`tablette/src/etapes/`](tablette/src/etapes/) | Un fichier `.vue` décrit les champs visibles d'une étape. [`App.vue`](tablette/src/App.vue) fixe leur ordre. Les écrans OT Hope sont créés à partir des domaines du questionnaire. |
| Réponses et rédaction | [`tablette/src/bilan.ts`](tablette/src/bilan.ts) | `Bilan` décrit les réponses mémorisées ; `nouveauBilan()` fixe les valeurs de départ ; `champs()` transforme les réponses en textes à insérer dans Word. |
| Modèle Word | [`contenu/bilan.docx`](contenu/bilan.docx) | Mise en page, titres, texte fixe, coordonnées du cabinet et repères `{…}` à remplacer. |

[`brouillon.ts`](tablette/src/brouillon.ts) gère la sauvegarde locale.
[`generer.ts`](tablette/src/generer.ts) remplit le modèle avec la bibliothèque
Docxtemplater. [`Generation.vue`](tablette/src/etapes/Generation.vue) charge le
modèle et lance la création. [`ordinateur.ts`](tablette/src/ordinateur.ts)
gère les différences d'enregistrement entre Windows et le navigateur.

## Le modèle Word, le sexe et l'âge

### Un seul modèle d'entrée

Il n'existe pas quatre fichiers « fille/enfant », « garçon/enfant »,
« fille/adolescente » et « garçon/adolescent ». **Tous les bilans partent du
même fichier [`contenu/bilan.docx`](contenu/bilan.docx)**, livré avec
l'application et disponible hors ligne.

Un repère comme `{prenom}` est remplacé par une réponse. Exemple présent
dans le modèle :

```text
Je rencontre {prenom} {ne_e} le {date_de_naissance}, {il_elle} a {age}.
```

Pour Léa, née le 14 octobre 2015, avec une passation au 14 octobre 2026 :

```text
Je rencontre Léa née le 14-10-2015, elle a 11 ans et 0 mois.
```

### Les adaptations au sexe et au choix Enfant/Adolescent

| Repère Word | Fille | Garçon |
| --- | --- | --- |
| `{il_elle}` | elle | il |
| `{Il_Elle}` | Elle | Il |
| `{ne_e}` | née | né |
| `{seul_e}` | seule | seul |
| `{lateralite}` | droitière, gauchère ou ambidextre | droitier, gaucher ou ambidextre |
| `{type_bilan}` avec « Enfant » | Enfant | Enfant |
| `{type_bilan}` avec « Adolescent » | Adolescente | Adolescent |

Dans le code, le sexe est nommé `Femme` ou `Homme`, même si l'écran affiche
« Fille » et « Garçon ».

L'âge `{age}` est calculé en années et mois révolus entre la naissance et la
**date de passation**, initialisée à la date du jour et modifiable. En revanche,
**Enfant/Adolescent est un choix manuel** : aucun seuil d'âge ne le détermine.
Ce choix change le titre `{type_bilan}`, sans changer les questions ni les
activités proposées.

Les accords concernent seulement les repères et les règles prévus dans le
code. Un mot fixe dans Word, comme « l'enfant », ne devient pas automatiquement
« l'adolescente ». Une telle adaptation nécessite un repère et une règle de
rédaction. Les phrases libres saisies ne sont pas réaccordées non plus.

### Les repères disponibles dans Word

Le modèle contient actuellement **47 noms de repères distincts**, dont certains
sont réutilisés. En complément du tableau des accords ci-dessus :

| Partie | Repères |
| --- | --- |
| Identité et dates | `{prenom}`, `{nom}`, `{date_de_naissance}`, `{date_de_passation}`, `{age}` |
| Établissement | `{classe}`, `{type_etablissement}`, `{nom_etablissement}` |
| Famille et médecin | `{mode_de_garde}`, `{fratrie}`, `{entente}`, `{medecin_traitant}`, `{ville}` |
| Demande et anamnèse | `{personne_demandeuse}`, `{motifs}`, `{troubles}`, `{dossier_mdph}` |
| Suivis | `{professionnels}` : professionnels avec leur fréquence, ou « aucun ». |
| Scolarité | `{comportement_en_classe}`, `{difficultes_en_classe}`, `{matieres_preferees}`, `{matieres_moins_appreciees}` |
| OT Hope : avec aide | `{aide_maison}`, `{aide_ecole}`, `{aide_loisirs}` |
| OT Hope : avec difficulté | `{difficulte_maison}`, `{difficulte_ecole}`, `{difficulte_loisirs}` |
| OT Hope : avec grande difficulté | `{grande_difficulte_maison}`, `{grande_difficulte_ecole}`, `{grande_difficulte_loisirs}` |
| Objectifs par domaine | `{objectifs_maison}`, `{objectifs_ecole}`, `{objectifs_loisirs}` |
| Synthèse des objectifs | `{objectifs_finaux}`, `{accord_parents}`, `{objectifs_parents}` |
| Aménagements et loisirs | `{amenagements_scolaires}`, `{activites_extra_scolaires}`, `{activites_temps_libre}`, `{difficultes_loisirs}` |

Un écran de saisie ne correspond pas obligatoirement à une page Word. On peut
déplacer un repère dans le document sans déplacer son écran. La pagination
dépend de la mise en page du modèle et de la longueur des réponses.

## Comment enrichir le logiciel

L'ergothérapeute peut préparer les choix, la rédaction et le document Word.
Créer une nouvelle zone de saisie demande aussi une modification du code :
la recette ci-dessous et la fiche de demande servent à la guider, seule avec
un assistant de développement ou avec l'aide d'une personne qui programme.

### Choisir le bon type de modification

| Besoin | Modification nécessaire |
| --- | --- |
| Ajouter une option à une liste : trouble, professionnel, fréquence, activité, aménagement… | Généralement `contenu/questionnaire.json`. L'écran et le repère Word existants reprennent la nouvelle option. |
| Changer un titre, un texte fixe, les coordonnées ou la mise en page | `contenu/bilan.docx`, en conservant les repères nécessaires. |
| Changer une phrase liée à un choix | Certaines sont dans le JSON (`identite.entente`, `objectifs.accordParents`), d'autres dans `champs()` ou le texte fixe du Word. |
| Ajouter une information à saisir | Le type `Bilan`, sa valeur de départ, l'écran, sa correspondance dans `champs()` et son repère dans Word. |
| Ajouter un domaine OT Hope | Un domaine dans le JSON et ses repères dans Word ; le nouvel écran est créé automatiquement. |
| Choisir entre plusieurs modèles Word ou ajouter un type de bilan | Une évolution du code et des tests ; déposer plusieurs `.docx` ne suffit pas. |

### 1. Compléter une liste existante

Exemple : ajouter « Casque antibruit » dans la liste `amenagements` de
`contenu/questionnaire.json`. Les textes sont entre guillemets et séparés par
des virgules. Extrait illustratif :

```json
"amenagements": [
  "AESH",
  "Ordinateur",
  "Casque antibruit"
]
```

Conserver les autres éléments du fichier : cet extrait ne remplace pas la
liste complète. L'option apparaîtra à l'écran « Aménagements et loisirs » et,
si elle est choisie, dans `{amenagements_scolaires}`. Aucun nouveau repère
n'est nécessaire.

Même principe pour `demande.troubles`, `suivis.professionnels`,
`scolarite.matieres` ou les `activites` d'un domaine OT Hope. Conserver le
format des entrées : une activité est un texte ; un domaine possède un
identifiant, un titre et une liste d'activités.

Les textes des options servent aussi à retrouver les réponses sauvegardées.
Si une option est renommée ou supprimée, un brouillon qui l'avait choisie la
perd à la réouverture : un bandeau liste les réponses retirées, à choisir à
nouveau ([`reprise.ts`](tablette/src/reprise.ts)). Pour la latéralité, garder
les listes féminine et masculine dans le même ordre : la réponse est
mémorisée par sa position dans la liste.

### 2. Retoucher le modèle Word

Ouvrir `contenu/bilan.docx` dans Word, modifier puis enregistrer en `.docx`
dans le projet. Modifier un bilan déjà généré ne change pas le modèle.

- Conserver les accolades simples, sans espaces, et la casse : `{Il_Elle}`
  et `{il_elle}` sont deux repères différents.
- Un repère doit être du texte dans Word, pas une image ni un champ de
  publipostage. Pour un nouveau nom, utiliser des lettres sans accents et
  des tirets bas, par exemple `{observations_sommeil}`.
- Un repère peut apparaître plusieurs fois. Supprimer sa dernière occurrence
  demande de revoir sa correspondance dans le code : les tests contrôlent
  que les repères du modèle et du code correspondent exactement.
- Un repère peut recevoir plusieurs lignes. Prévoir assez de place dans les
  tableaux et vérifier la mise en page avec des réponses longues.
- Pour qu'un texte n'apparaisse que si une réponse est remplie, l'encadrer
  par `{#champ}` et `{/champ}` : `{#medecin_traitant}Nom du médecin
  traitant : Dr {medecin_traitant}.{/medecin_traitant}`. À l'inverse,
  `{^champ}…{/champ}` n'apparaît que si la réponse est vide. Le modèle
  utilise déjà ces conditions dans la phrase d'identité, la personne
  demandeuse et le motif. Une réponse vide ne supprime pas, en revanche, un
  titre ou un tableau placé hors de ces conditions.

Écrire `{nouvelle_information}` dans Word ne crée pas de question à l'écran.
Sans correspondance dans `champs()`, elle ne sera pas renseignée et peut
devenir un texte vide ; les tests doivent détecter cette incohérence.

### 3. Ajouter une rubrique de saisie : exemple « Sommeil »

Cette recette peut être confiée à la personne qui modifie le code ou à un
assistant de développement. **C'est un exemple à réaliser : cette rubrique
n'existe pas aujourd'hui.**

Le besoin : une étape « Sommeil » avec du texte libre, repris dans Word sous
le même titre. Nom interne de la réponse : `observationsSommeil`. Repère Word :
`{observations_sommeil}`.

**A. Définir la réponse.** Dans `tablette/src/bilan.ts`, ajouter à l'interface
`Bilan` :

```ts
observationsSommeil: string
```

Puis ajouter dans l'objet renvoyé par `nouveauBilan()` :

```ts
observationsSommeil: '',
```

Cela initialise la zone à vide et permet à « Nouveau bilan » de l'effacer.
La reprise d'un ancien brouillon ([`reprise.ts`](tablette/src/reprise.ts))
complète déjà les nouveaux champs avec cette valeur de départ. Changer la
forme d'une réponse existante (texte devenu liste…) demande d'augmenter
`VERSION_BROUILLON` et d'adapter `reprendre()`, avec un test dans
`tests/reprise.test.ts`.

**B. Créer l'écran.** Créer `tablette/src/etapes/Sommeil.vue` :

```vue
<script setup lang="ts">
import { bilan } from '../brouillon'
</script>

<template>
  <section class="carte">
    <label>Observations sur le sommeil
      <textarea v-model="bilan.observationsSommeil" rows="5"
                placeholder="Endormissement, réveils, fatigue au réveil…" />
    </label>
  </section>
</template>
```

`v-model` relie la saisie à la réponse ; la sauvegarde locale existante la
prendra en compte. Pour enrichir un écran existant, y ajouter seulement le
bloc `<label>…</label>` et s'assurer qu'il importe `bilan`.

**C. Insérer l'étape.** Dans `tablette/src/App.vue`, importer :

```ts
import Sommeil from './etapes/Sommeil.vue'
```

Puis insérer dans la liste `etapes`, à l'endroit souhaité avant « Bilan » :

```ts
{ titre: 'Sommeil', composant: Sommeil },
```

La numérotation et les boutons de navigation s'adaptent. Cette étape C est
inutile si la zone est ajoutée à un écran existant.

**D. Relier la réponse au Word.** Dans l'objet `valeurs` de la fonction
`champs()` de `bilan.ts`, ajouter :

```ts
observations_sommeil: bilan.observationsSommeil.trim(),
```

`trim()` retire les espaces au début et à la fin. C'est ici qu'une règle
pourrait construire une phrase plutôt que reprendre le texte tel quel.

**E. Fournir la partie Word correspondante.** À l'endroit souhaité dans
`contenu/bilan.docx`, ajouter :

```text
Sommeil
{observations_sommeil}
```

Mettre « Sommeil » en style de titre et le repère dans le paragraphe suivant.
Pour commencer sur une nouvelle page Word, insérer un saut de page. Cette
section et son repère serviront aux quatre combinaisons sexe/Enfant-Adolescent.

Si l'ergothérapeute fournit un fichier séparé `Sommeil.docx` pour préparer
cette partie, il faut en intégrer le contenu au modèle principal : le logiciel
ne lit pas ce deuxième fichier automatiquement.

**F. Vérifier.** Ajouter un cas de génération dans
`tablette/tests/bilan.test.ts`. Les fonctions et le modèle ci-dessous y
existent déjà :

```ts
it('reprend les observations sur le sommeil dans le Word', () => {
  const bilan = nouveauBilan()
  bilan.observationsSommeil = 'Réveils nocturnes fréquents.'
  const texte = texteDuBilan(remplirModele(modele, champs(bilan)))
  expect(texte).toContain('Réveils nocturnes fréquents.')
  expect(texte).not.toMatch(/[{}]/)
})
```

Le test existant des repères vérifiera aussi la correspondance entre le code
et le modèle. Tester la saisie, la réouverture du brouillon et sa remise à
zéro.

### 4. Ajouter un domaine OT Hope

Pour ajouter par exemple « Déplacements », insérer un objet dans
`otHope.domaines` du JSON, avec un identifiant unique et stable :

```json
{
  "id": "deplacements",
  "titre": "Déplacements",
  "activites": [
    "Préparer mon trajet",
    "Repérer mon arrêt de bus"
  ]
}
```

L'étape OT Hope, les niveaux de difficulté et la sélection des objectifs de
ce domaine seront créés automatiquement. Le code calcule les repères
correspondants ; **il faut les ajouter au Word**, par exemple :

```text
Déplacements

Activités faites avec aide
{aide_deplacements}

Activités faites avec difficulté
{difficulte_deplacements}

Activités faites avec grande difficulté
{grande_difficulte_deplacements}

Objectifs de {prenom} pour les déplacements
{objectifs_deplacements}
```

On peut aussi intégrer ces repères aux tableaux existants. Leur nom suit la
règle « identifiant du niveau + tiret bas + identifiant du domaine », puis
« objectifs + tiret bas + identifiant du domaine ». Ne pas renommer les
identifiants existants sans examiner les réponses déjà sauvegardées.

### 5. Prévoir plusieurs modèles à l'avenir

Pour des documents de structures différentes, par exemple un bilan adulte et
un bilan pédiatrique, il faudra faire évoluer le chargement du modèle dans
`Generation.vue`, définir une règle de sélection, adapter les questions et
tester chaque modèle. Il faudra aussi prévoir leur disponibilité hors ligne.

Avant ce développement, préciser qui choisit le type de bilan, si l'âge doit
intervenir, et quels textes ou rubriques changent. Pour des accords et des
variations de phrases, le modèle unique avec de nouveaux repères peut suffire.

## Fiche pour préparer une nouvelle rubrique

L'ergothérapeute peut remplir cette fiche, joindre un Word d'exemple et la
transmettre à la personne qui développe, sans avoir à commencer par le code.

```text
Nom de la rubrique : Sommeil
Écran souhaité : nouvelle étape, après « Suivis »
Personnes concernées : tous les patients ; pas de différence selon le sexe
Question affichée : Observations sur le sommeil
Réponse attendue : texte libre, plusieurs lignes
Obligatoire : non
Si la réponse est vide : laisser le titre et une zone vide dans le bilan
Emplacement dans Word : après l'anamnèse, avant l'évaluation OT Hope
Titre Word : Sommeil
Repère proposé : {observations_sommeil}
Exemple fictif : Réveils nocturnes fréquents.
Résultat attendu : ce texte sous le titre « Sommeil »
```

Joindre une copie du modèle principal annotée ou une section `.docx` avec les
titres, paragraphes, tableaux et repères souhaités. Donner pour chaque question
la correspondance « question à l'écran → repère Word → exemple de résultat ».
Préciser les choix possibles, les unités, l'ordre des réponses et les
variations liées au sexe ou à l'âge. Un document rempli avec un patient fictif
permet de valider la rédaction.

## Vérifier et diffuser une évolution

### Préparer et vérifier sur un ordinateur de développement

Les contrôles automatiques de GitHub (la « CI ») utilisent Node.js 22 ;
l'environnement cloud a aussi été validé avec Node.js 24.19.0. Depuis la
racine du projet :

```bash
cd tablette
npm ci
npm run dev
```

Le serveur de développement permet d'essayer les écrans. Dans un autre
terminal, depuis la racine, lancer :

```bash
cd tablette
npm test
npm run build
npm run e2e
```

`npm test` compare les repères du code à ceux du modèle, remplit le vrai
Word et vérifie la reprise des brouillons. Ajouter des cas pour les nouvelles
règles. `npm run build` vérifie le code TypeScript et construit l'application
web avec ses fichiers hors ligne. `npm run e2e` remplit un bilan dans un vrai
navigateur (Playwright, dossier `e2e/`), jusqu'au Word téléchargé. La mise en
page doit aussi être relue dans Word.

### Relire avec des cas représentatifs

- Essayer fille et garçon, Enfant et Adolescent, et vérifier les accords.
- Vérifier l'âge à la date de passation, avant/après un anniversaire.
- Essayer la nouvelle rubrique vide et remplie, avec un texte long et des
  retours à la ligne ; examiner les tableaux et les sauts de page du Word.
- Reprendre un ancien brouillon, fermer et rouvrir l'application, puis
  commencer un nouveau bilan pour vérifier la remise à zéro.
- Vérifier les objectifs après modification des cotations OT Hope.
- Faire les essais sur tablette hors ligne et sous Windows de
  [TESTER.md](TESTER.md), avec des patients fictifs.

### Mettre la nouvelle version à disposition

Modifier les fichiers ne met pas immédiatement à jour les appareils. Le
workflow [Application tablette et Windows](.github/workflows/tablette.yml)
teste et construit les modifications de `tablette/` ou `contenu/` :

- Sur `main`, la version web est publiée sur GitHub Pages si le job web et
  les réglages Pages le permettent. Reconnecter la tablette pour charger
  la mise à jour, puis vérifier le nouveau contenu hors ligne.
- Le job Windows (`build`) crée l'installateur dans les artefacts de
  l'exécution (`TrameErgo-Windows-Tauri`). Sur `main`, une nouvelle version
  de `tablette/package.json` publie aussi la Release `v<version>` avec cet
  installateur ; une version déjà publiée n'est pas remplacée. Augmenter
  `version` dans `tablette/package.json` pour chaque livraison Windows et
  noter les modifications de cette version dans [CHANGELOG.md](CHANGELOG.md). Pour
  le construire localement, il faut Windows, Rust et les prérequis Tauri,
  puis `npx tauri build` dans `tablette/`.

Pour les détails techniques complémentaires, voir [CLAUDE.md](CLAUDE.md).
