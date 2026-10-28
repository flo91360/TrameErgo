# Journal des modifications

Toutes les modifications notables de TrameErgo, version par version. La
version est celle de `tablette/package.json` ; chaque version arrivée sur
`main` est publiée dans les
[Releases](https://github.com/flo91360/TrameErgo/releases) avec
l'installateur Windows.

Chaque PR fusionnée publie une nouvelle version : elle augmente le numéro
et ajoute ici sa section, datée.

## [1.6.8] - 2026-10-28
<!-- planifikateur:00412af8-d723-4666-8f64-4273b2795eab -->

- **harmonisation entre le lien google form rempli par les parent et le logiciel TramErgo** : Toutes les modifications du document « modification TramErgo » (pièce jointe : il n'était pas dans le dépôt) sont appliquées dans TrameErgo. L'import des réponses des parents pré-remplit maintenant les nouveaux libellés. Le questionnaire Google Forms n'a pas été modifié. `npm test` (65 tests) et `npm run build` passent ; les tests de parcours (e2e) n'ont pas été lancés. **Changements dans `contenu/questionnaire.json`** - **Difficultés en classe (onglet 4)** : la liste reprend les 10 propositions du document. Un champ « Autre » a été ajouté à l'écran Scolarité ; il est écrit dans le bilan Word après les choix cochés. - **OT Hope, vie quotidienne (onglet 6)** : 15 activités ajoutées, 11 renommées, « Utiliser un cadenas » et « Me raser » retirés. - **OT Hope, vie scolaire (onglet 7)** : 5 activités ajoutées et 10 renommées. Les trois « Tracer un carré / rond / triangle » deviennent une seule activité. « M'organiser pour faire mes devoirs » est retiré. - **OT Hope, loisirs (onglet 8)** : 7 activités ajoutées. - **Aménagements (onglet 10)** : « Adaptation des barèmes », « Texte plus grand et/ou bien espacé » et « Polycopier à trou » ajoutés. Les activités prennent une majuscule initiale, comme le reste des listes. L'orthographe du document est gardée telle quelle (« ses vêtement », « dans la cours »), car c'est aussi celle du formulaire et c'est ce qui permet le pré-remplissage. Ces libellés apparaissent donc tels quels dans le bilan Word. **Changements dans le pré-remplissage (`tablette/src/questionnaireParents.ts`)** - **Correspondances demandées par le document** : « Polycopier fournis dans certaines matières » coche « Polycopiés donnés », « réduction du nombre d'exercice lors des évaluations » coche « Moins d'exercices », et « pour participer » coche « Participer ». - **Libellés rapprochés** : si aucun libellé n'est identique, la parenthèse est ignorée et « me »/« se », « mon »/« son »… se valent, à condition qu'un seul choix corresponde. Par exemple, « se couper les

## [1.6.7] - 2026-10-28

### Ajouté

- `formulaire/fiche-patient.gs` : à chaque fiche patient créée, un mail avec
  son lien est envoyé au compte qui a installé le script (ou à
  `DESTINATAIRE_FICHES`). Le mail ne contient pas les réponses.

## [1.6.6] - 2026-10-24
<!-- planifikateur:b0bc4d55-8325-449b-abad-f38959756fe1 -->

- **lien entre google form et tramErgo onglet 5** : J'ai corrigé les deux tests qui échouaient. Ils cassaient parce que `main` avait avancé : la carte « rajouter des caractères possibles » (#28) a ajouté 9 traits à TrameErgo, dont « très sensible ». Après correction, les tests (59/59, `npm test`) et la construction (`npm run build`) passent. **Corrections :** - **`formulaire/creer-formulaire.gs`** : la liste des cases de la question « Actuellement votre enfant est : (qualités et défauts) » contient maintenant les 35 traits de `contenu/questionnaire.json`, avec les mêmes libellés et dans le même ordre. Les 9 nouveaux sont : peu sociable, très sensible, empathique, intolérant à l'injustice, intolérant à la frustration, facilement dans le conflit, influençable, teste souvent le cadre, provocateur. Ce sont les cases de l'ancien formulaire, sauf « Sociable », qui existait déjà. Le formulaire et l'application proposent donc à nouveau exactement les mêmes items. - **`tablette/tests/questionnaireParents.test.ts`** : le test se servait de « Très sensible » comme exemple d'item absent de TrameErgo. Ce n'est plus vrai, il utilise maintenant « Rêveur ». Le pré-remplissage lui-même n'a pas changé : - Les qualités et défauts cochés par les parents s'ajoutent à « Selon les parents » de l'étape 5, sans retirer ni dupliquer ce qui était déjà coché. - Ils sont reconnus au masculin comme au féminin. - Un item inconnu de TrameErgo n'est pas coché et apparaît seulement dans l'encadré « Réponses des parents ». - « Selon l'enfant » et les autres étapes ne sont pas touchés. Comme avant, seul le script de création est mis à jour : un formulaire Google déjà créé doit proposer ces mêmes cases pour que les réponses soient reportées.

## [1.6.5] - 2026-10-24
<!-- planifikateur:e5a5129e-a104-47d7-87d1-2d8c82e33843 -->

- **dans l'onglet 5 de tramErgo rajouter des caractères possible** : Les neuf traits demandés sont ajoutés à l'onglet 5 « Caractère du patient » et sortent correctement dans le bilan Word. `npm test` (58 tests) et `npm run build` passent. Je n'ai pas ouvert l'application ni généré de bilan à la main, et les parcours Playwright (`npm run e2e`) n'ont pas été lancés. **Ajouts :** peu sociable, très sensible, empathique, intolérant à l'injustice, intolérant à la frustration, facilement dans le conflit, influençable, teste souvent le cadre, provocateur. L'orthographe est corrigée (« influençable », « teste souvent le cadre »), en minuscules comme les autres items. Ils sont placés après les items existants, que je n'ai pas modifiés. La liste est dans `contenu/questionnaire.json`. **Les nouveaux traits apparaissent aussi du côté de l'enfant.** L'application utilise une seule liste pour les parents et pour l'auto-évaluation de l'enfant. Pour qu'ils se comportent comme les autres, j'ai donc rédigé pour chacun une phrase à la première personne et un classement qualité/défaut : - **Qualité :** empathique (« Je comprends ce que ressentent les autres »). - **Défauts :** les huit autres, dont très sensible (« Je ressens les émotions très fort »), influençable (« Je fais souvent comme les autres, même quand ce n'est pas bien ») et teste souvent le cadre (« J'essaie souvent de voir jusqu'où je peux aller »). Si vous préférez que ces traits ne soient proposés qu'aux parents, il faudra le préciser. **Formes au féminin :** intolérante à l'injustice, intolérante à la frustration et provocatrice ; les autres ne changent pas. **Phrase du bilan pour « teste souvent le cadre » :** écrite telle quelle, elle aurait donné « Lucas est … teste souvent le cadre ». J'ai ajouté un champ facultatif `infinitif` aux traits formulés avec un verbe ; ce trait s'écrit alors sans « est » ni « d'être » : - « D'après ses parents, Lucas est peu sociable et provocateur, et teste souvent le cadre. » - « Léa se reconnaît comme défauts d'être influençable et de tester souvent le

## [1.6.4] - 2026-10-24
<!-- planifikateur:13b9e8ed-02f4-479c-9a30-b7011f9acfbc -->

- **lien entre google form et TramErgo** : J'ai corrigé l'échec : `npm test` (56 tests) et `npm run build` passent maintenant. **Cause** : entre-temps, la carte fusionnée dans `main` (PR #26) a changé la liste des troubles de `contenu/questionnaire.json`. Elle a ajouté « Trouble oppositionnel » et retiré « Trouble autistique de type asperger ». La liste que j'avais ajoutée au script de création du formulaire (`formulaire/creer-formulaire.gs`) ne correspondait plus, et le test qui compare les deux a échoué. **Correction** : cette liste reprend maintenant exactement la nouvelle liste de TrameErgo. C'est le seul changement ; le reste de la livraison précédente est identique. **Rappel du fonctionnement** - Quand les parents cochent, dans la question « Pour quelle(s) raison(s) le bilan est souhaité ? En lien avec quel trouble diagnostiqué ? », un trouble de la liste de TrameErgo, il est coché dans « Anamnèse / troubles » de l'étape Demande. - Une réponse qui ne correspond à aucun choix (par exemple l'option « Autre ») est recopiée telle quelle dans le champ « Autre trouble », qui existait déjà. Le Word l'écrit à la suite des troubles cochés ; `contenu/bilan.docx` n'a pas été modifié. - Les autres questions et le bilan sans connexion ou sans réponse des parents fonctionnent comme avant. **À vérifier dans votre formulaire Google** : il n'est pas modifié automatiquement, ses cases doivent donc reprendre la liste à jour de TrameErgo. Un parent qui y coche « Trouble autistique de type asperger » verra ce texte reporté dans « Autre trouble », car ce choix n'existe plus dans l'application. « Trouble oppositionnel » ne sera coché que si votre formulaire propose cette case.

## [1.6.3] - 2026-10-24
<!-- planifikateur:8e1c13ce-107e-47e8-800d-5c4c19d1b433 -->

- **ajouter et retirer des éléments dans la section 2 "demande" dans la p** : Dans l'étape « Demande », la liste des troubles propose maintenant « Trouble oppositionnel », et « Trouble autistique de type asperger » n'y figure plus. Les tests (55 réussis) et la compilation passent. Seul `contenu/questionnaire.json` a dû changer. Le nouveau trouble est placé juste après « TDA avec hyperactivité ». Rien d'autre n'était nécessaire : - **Écran Demande** : il affiche directement la liste du questionnaire. - **Bilan Word** : `contenu/bilan.docx` reprend les troubles cochés dans un seul champ `{troubles}`, dans l'ordre de la liste. « Trouble oppositionnel » y apparaît donc sans modifier le modèle. Le trouble retiré n'est utilisé dans aucun test, parcours e2e ou fichier du dépôt. Si un brouillon sur un appareil contient encore cette réponse, la reprise l'enlèvera et le signalera, comme pour toute réponse qui n'est plus dans le questionnaire. Je n'ai pas pu vérifier l'historique des bilans déjà créés, qui est stocké sur chaque appareil. Le Google Form des parents (`formulaire/creer-formulaire.gs`) a son propre libellé, « Trouble du spectre Autistique - type Asperger ». Comme il est différent de celui de l'application, il ne pré-remplissait déjà pas cette case. Je ne l'ai pas modifié, la carte ne portant que sur l'application. J'ai ajouté un test dans `tablette/tests/bilan.test.ts`. Il vérifie que la liste contient le nouveau trouble et plus l'ancien, et qu'un « Trouble oppositionnel » coché est écrit dans le bilan Word généré à partir du vrai modèle.

## [1.6.2] - 2026-10-24
<!-- planifikateur:51870936-dbfb-4fc5-9805-2d6e69617e6e -->

- **lien entre google form et tramErgo** : Quand on pré-remplit un bilan à partir du questionnaire des parents, le champ « Personne demandeuse » de l'étape Demande prend maintenant la réponse à la question « Qui est à l'origine de la demande de réalisation du bilan en ergothérapie ? ». Les tests (`npm test`) et la construction (`npm run build`) passent. **Ce qui ne fonctionnait pas :** l'application cherchait cette réponse sous l'ancien intitulé de la question (« … du bilan (médecin traitant ou autre professionnel de santé, instituteurs/professeurs…) ? »). Avec le formulaire actuel, elle ne la trouvait donc jamais. **Modifications :** - `tablette/src/questionnaireParents.ts` : - l'application cherche maintenant la question sous son nouvel intitulé. Les différences de majuscules, d'accents et d'apostrophe (’ ou ') ne gênent pas. - quand la réponse est exactement l'un des choix de « Personne demandeuse », ce choix est sélectionné, sans table de correspondance. - « Autre » est mis de côté : si les parents ont choisi « Autre » et écrit un texte libre, ou si la réponse ne correspond à aucun choix, le champ reste à « — à renseigner — ». - `formulaire/creer-formulaire.gs` : le script qui crée le Google Form ne génère plus une question texte, mais une question à choix unique sous le nouvel intitulé. Les options sont celles de l'application (le médecin traitant, la neuropédiatre, l'enseignant, la psychomotricienne, la neuropsychologue, le(s) parent(s), le père, la mère), plus l'option « Autre » de Google Forms avec texte libre. Seul ce script est modifié : le formulaire déjà en ligne n'est pas touché. - `tablette/tests/questionnaireParents.test.ts` : - un nouveau test vérifie qu'une réponse « la mère » ou « l'enseignant » est sélectionnée, et qu'une réponse « l'orthoptiste », « Autre » ou absente laisse le champ vide. - un autre test échoue si la liste de choix du script et celle de l'application (`contenu/questionnaire.json`) ne sont plus identiques.

## [1.6.1] - 2026-10-24

### Modifié

- `formulaire/fiche-patient.gs` : les fiches patients sont enregistrées dans
  le dossier ERGO/questionnaire pré-bilan du Google Drive (créé s'il manque).

## [1.6.0] - 2026-10-24

### Ajouté

- `formulaire/fiche-patient.gs` : à chaque réponse au questionnaire des
  parents, une fiche patient Word avec toutes les réponses (rangées sous les
  titres du formulaire, grilles en tableaux) est créée dans le Google Drive
  du formulaire, dossier « Fiches patients ».

### Retiré

- La fiche patient de TrameErgo (bouton de l'écran Patient, modèle
  `contenu/fiche.docx`) : elle est désormais créée côté Google. Le médecin
  traitant du questionnaire pré-remplit toujours l'écran Patient.

## [1.5.4] - 2026-10-24
<!-- planifikateur:72c2ca13-2db9-4d3b-a150-05349bafd018 -->

- **dans la partie suivi par des professionnels** : Les deux « Autre » sont en place : jusqu'à 3 autres thérapeutes dans l'étape Suivis, et un choix « Autre » pour la personne demandeuse, comme répondu dans les échanges. Les conflits avec main sont résolus. `npm test` passe (57 tests) et `npm run build` aussi. Les nouveaux parcours Playwright n'ont pas été lancés : les navigateurs ne sont pas installés ici. **Étape Suivis : autres thérapeutes** - Une puce « Autre » est ajoutée après les professionnels de la liste. Cochée, elle affiche une ligne avec un champ libre (nom ou profession) et la fréquence du suivi. - « Ajouter un autre thérapeute » permet d'aller jusqu'à 3 lignes, puis le bouton disparaît : un 4e est impossible. Chaque ligne peut être retirée, et décocher « Autre » les retire toutes. - On ne peut pas quitter l'écran sans le nom et la fréquence de chaque « Autre ». Cocher seulement « Autre » suffit à la place d'un professionnel de la liste ou de « Aucun ». - **Word** : le repère `{autre}` est placé dans `contenu/bilan.docx` juste après `{professionnels}`, dans le même paragraphe. Il est rempli par `champs()` avec une ligne « - nom : fréquence » par thérapeute. Sans « Autre », ou si « Aucun » est coché, il reste vide et ne laisse aucune trace, pas même une ligne vide. Le modèle reste sans conditions `{#…}`. **Étape Demande : personne demandeuse « Autre »** - « Autre » est ajouté à la fin de la liste dans `questionnaire.json`. Une fois choisi, un champ « Autre personne demandeuse » apparaît et doit être rempli pour continuer. - Le Word écrit le texte saisi, par exemple « le bilan a été demandé par l'orthoptiste », et jamais le mot « Autre ». **Réponses mémorisées et brouillons** - Deux nouvelles réponses sont mémorisées : `autresProfessionnels` (vide au départ) et `autrePersonneDemandeuse`. - À la reprise d'un brouillon, au plus 3 thérapeutes sont gardés. Une fréquence qui n'est plus dans la liste est retirée et signalée. **Conflits avec main** - `bilan.ts`, `reprise.ts` et le test e2e : les deux versions son

## [1.5.3] - 2026-10-23
<!-- planifikateur:053b7866-0f1a-4e36-b900-066880ba1e4c -->

- **dans l'onglet 9 aménagement scolaire** : L'option « Autre / aménagement scolaire » est ajoutée à l'étape 9, avec une zone de texte libre. Les tests (`npm test`, 45 réussis) et `npm run build` passent ; le parcours Playwright n'a pas été lancé. **Point « À préciser » : j'ai tranché moi-même, à vous de confirmer.** Si du texte est saisi sans que la case soit cochée, il va quand même dans le Word. C'est déjà ce que font « Autre motif », « Autre trouble » et les « Autre » des matières, j'ai donc gardé la même règle. Si vous préférez ignorer ce texte ou cocher la case automatiquement, c'est un petit changement. **Ce qui change :** - **Liste** : « Autre / aménagement scolaire » est ajouté en fin de liste des aménagements dans `contenu/questionnaire.json`. - **Écran** : une zone de texte multiligne « Autre / aménagement scolaire (un par ligne) » s'affiche toujours sous la liste, que la case soit cochée ou non. - **Blocage** : si la case est cochée et la zone vide (ou seulement des espaces), « Suivant » reste bloqué. La liste en bas de l'écran indique « l'aménagement scolaire « Autre » à préciser ». Ce manque bloque aussi la création du Word. - **Bilan Word** : rien ne change dans le modèle `bilan.docx`. Le texte libre s'ajoute à la fin de la liste « - … » des aménagements scolaires, une puce par ligne saisie (lignes vides ignorées). Le libellé « Autre / aménagement scolaire » lui-même n'apparaît pas dans le Word. - **Brouillons et historique** : un nouveau champ `autreAmenagement` (vide au départ) s'ajoute aux réponses. Les brouillons et bilans enregistrés avant ce changement se rouvrent normalement : le champ y est simplement vide. Aucun numéro de version du brouillon n'a dû être changé. **Tests ajoutés** (`tests/bilan.test.ts`, `tests/reprise.test.ts`) : le blocage case cochée / zone vide, l'ordre et le contenu de la liste dans le Word généré, le texte saisi sans case cochée, et la reprise d'un ancien brouillon sans ce champ.

## [1.5.2] - 2026-10-23
<!-- planifikateur:22e27d62-42ee-44e8-abbc-1f5a107d652e -->

- **nouvel onglet appelé caractère du patient** : J'ai ajouté l'étape facultative « Caractère du patient », placée entre Scolarité et la première étape OT Hope, et ses deux phrases dans le bilan Word. Le modèle ne contient pas de partie « comportement de l'enfant durant le bilan ». J'ai donc placé la nouvelle partie juste avant « Comportement en classe », la seule partie du modèle qui traite du comportement. À vous de confirmer ou de m'indiquer une autre place. `npm test` et `npm run build` passent. Les parcours dans le navigateur (`npm run e2e`) n'ont pas pu être lancés ici, car les navigateurs Playwright ne sont pas installés : leurs nouveaux contrôles n'ont donc pas encore tourné. **Liste proposée (à faire valider)** : 26 items dans `contenu/questionnaire.json`, 13 qualités et 13 défauts, en une seule liste mélangée. - Qualités : curieux, gentil, drôle, serviable, joyeux, courageux, créatif, sociable, calme, autonome, affectueux, honnête, généreux. - Défauts : impatient, têtu, colérique, timide, distrait, bavard, désordonné, susceptible, agité, anxieux, peu motivé par l'effort, jaloux, mauvais perdant. - Chaque item a une forme masculine, une forme féminine et une phrase simple pour l'enfant (« Je parle beaucoup », « Je fais rire les autres »…). Les phrases pour l'enfant ne dépendent pas du sexe. - Pour changer la liste, il suffit de modifier ce fichier. **Écran** - Partie parents : une seule liste de puces, affichée au masculin ou au féminin selon le sexe de l'enfant. - Partie enfant : deux blocs séparés, « mes qualités » et « mes défauts », avec les mêmes items en mots simples. Chaque case de l'enfant correspond à un item de la partie parents. - Aucune réponse n'est obligatoire : on passe à l'écran suivant sans rien cocher. **Bilan Word** : nouvelle partie « Comportement de l'enfant de manière générale » dans `contenu/bilan.docx`, avec deux champs simples, sans conditions. - `{caractere_parents}` : « D'après ses parents, Lucas est curieux, têtu et joyeux. » - `{caractere_enfant}` : « Lors de son auto-évaluatio

## [1.5.1] - 2026-10-23

### Modifié

- Fiche patient sous Windows : le bouton « Créer la fiche patient »
  l'enregistre dans Documents\TrameErgo sans l'ouvrir dans Word ; le bouton
  « Ouvrir dans Word » reste proposé.

## [1.5.0] - 2026-10-23

### Ajouté

- Fiche patient Word (`contenu/fiche.docx`) : bouton « Créer la fiche
  patient » sur l'écran Patient. Elle reprend les coordonnées de l'enfant,
  du médecin traitant, des parents 1 et 2 (nom, prénom, adresse, téléphone,
  adresse mail, profession) et de la famille (fratrie, mode de garde).
  L'écran Patient l'emporte sur le questionnaire des parents ; elle est
  enregistrée comme le bilan (Documents\TrameErgo ou téléchargement).
- Questionnaire des parents : les réponses des encadrés « Enfant »,
  « Médecin traitant », « Parent 1 », « Parent 2 » et « Famille » sont
  gardées par partie (`parent1.telephone`, `medecin.ville`…) et le médecin
  traitant (nom, ville) pré-remplit l'écran Patient.

## [1.4.3] - 2026-10-23

### Corrigé

- Questionnaire des parents : les intitulés suivis de deux-points
  (« Date de naissance : », « Nom et Prénom de l’enfant : ») sont reconnus,
  pour retrouver l'enfant comme pour pré-remplir les réponses.

## [1.4.2] - 2026-10-23

### Modifié

- Questionnaire des parents : le script de lecture retrouve aussi l'enfant
  quand son nom est découpé en deux questions « Nom » et « Prénom » sous un
  titre « Enfant ». Il indique pour chaque réponse le titre de l'encadré ou
  de la section où elle se trouve (« Parent 1 »…).
- Encadré « Réponses des parents » : une question au même intitulé qu'une
  autre (« Nom » de l'enfant, d'un parent, du médecin) est précédée de ce
  titre (« Parent 1 - Nom »).
- Script de lecture : retrait de fonctions de création du formulaire qui n'y
  servaient pas.

## [1.4.1] - 2026-10-22

### Corrigé

- Questionnaire des parents : `lienDeLiaison` ne s'arrête plus en erreur
  quand Google lui donne l'adresse de test du script au lieu de celle de
  l'application web ; il affiche alors la clé à ajouter à l'URL copiée dans
  « Gérer les déploiements ».

## [1.4.0] - 2026-10-22

### Ajouté

- Questionnaire des parents : à la création d'un bilan, TrameErgo cherche
  les réponses du questionnaire Google Forms au nom de l'enfant (coche verte,
  croix rouge, ou « non vérifié » sans connexion) et propose de les importer.
- L'import pré-remplit les activités OT Hope dont le libellé est celui de
  l'application (aux majuscules et aux accents près), ainsi que la date de
  naissance, la latéralité, la classe, les troubles, les matières, les
  aménagements et les loisirs quand la réponse est un choix de
  l'application. Toutes les réponses restent consultables pendant la saisie
  (« Réponses des parents au questionnaire »).
- Réglage « Questionnaire des parents » à l'accueil : un lien de liaison
  (affiché par le script Google), collé une fois par appareil et gardé après
  les mises à jour.
- `formulaire/` : script qui crée le formulaire, script de lecture des
  réponses à publier en application web, et leur mode d'emploi.

### Modifié

- « Nouveau bilan » demande d'abord le prénom et le nom de l'enfant.

## [1.3.0] - 2026-10-20

### Ajouté

- Écran d'accueil : « Nouveau bilan », « Reprendre le bilan en cours » ou
  « Historique des bilans ».
- Historique des bilans créés sur l'appareil : recherche par patient,
  ouverture d'un bilan pour le corriger ou recréer le Word, réévaluation
  (nouveau bilan daté du jour qui reprend l'identité de l'enfant),
  sauvegarde et import en fichier `.json`.

### Modifié

- On ne passe à l'écran suivant que lorsque ses réponses obligatoires sont
  remplies ; ce qui manque est listé en bas de l'écran.
- Le modèle Word est allégé : plus aucune condition `{#…}{/…}`, seulement
  des champs `{champ}` dans des phrases lisibles.
- « Nouveau bilan » ne demande confirmation que si le bilan en cours n'a pas
  été créé en Word depuis ses dernières modifications.

## [1.2.3] - 2026-10-19

### Modifié

- Windows : quand un bilan du même nom existe, une vraie fenêtre propose
  « Remplacer », « Garder les deux » ou « Annuler » (avant : « OK / Annuler »,
  où « Annuler » créait une copie).
- Au clavier, les flèches changent le choix d'un groupe de segments (sexe,
  entente, niveaux OT Hope…), qui ne compte plus qu'un arrêt de tabulation.
- Choisir un professionnel ne remplit plus sa fréquence de suivi d'office
  (« une fois par semaine ») : elle est « à renseigner ».
- L'écran Bilan liste aussi la fratrie, le nom de l'établissement, le
  médecin traitant, la ville du médecin et les fréquences de suivi
  manquantes : sans eux, une partie du bilan (dont l'entente, ou la ville)
  n'est pas imprimée.

### Corrigé

- Une date illisible dans un brouillon n'écrit plus « NaN an et NaN mois »
  dans le bilan : elle est retirée et signalée.
- Plus d'interstice entre l'en-tête et la barre d'étapes quand la page
  défile.

## [1.2.2] - 2026-10-19

### Modifié

- Aucun choix clinique n'est plus pré-rempli : classe, établissement,
  latéralité, mode de garde, entente, personne demandeuse, dossier MDPH et
  accord des parents commencent à « — à renseigner — ». L'écran Bilan liste
  ceux qui restent vides.
- Une réponse vide ne laisse plus de phrase cassée dans le bilan (« Dr , à
  . », « Motif : . », « il a  () ») : la phrase est omise.

### Corrigé

- Un brouillon dont une réponse n'existe plus dans le questionnaire (option
  renommée ou supprimée) ne l'écrit plus dans le bilan : elle est retirée et
  signalée une fois à l'ouverture.

## [1.2.1] - 2026-10-19

Corrections relevées par l'audit du projet.

### Ajouté

- Ce journal des modifications (`CHANGELOG.md`).
- Windows : si un bilan du même nom existe déjà dans `Documents\TrameErgo`,
  l'application demande s'il faut le remplacer ou enregistrer une copie
  (`…_2.docx`) : un bilan complété dans Word n'est plus écrasé sans accord.
- Alerte quand la date de naissance est après la date de passation, et quand
  la date de passation manque.

### Corrigé

- Toucher le titre « Sexe », « Bilan », « Entente » ou « Les parents sont-ils
  en accord… » choisissait la première réponse (Fille, Enfant, Bonne, Oui).
- Âge négatif (« -1 an et -2 mois ») écrit dans le bilan quand la date de
  naissance était après la passation : l'âge est maintenant laissé vide.
- Le bandeau « Bilan en cours repris » restait affiché après « Nouveau bilan ».
- Le récapitulatif et l'écran OT Hope comptent les objectifs et les activités
  comme le bilan Word.
- Windows : message distinct quand le bilan est enregistré mais que Word ne
  s'ouvre pas ; le bouton « Créer le bilan Word » est désactivé pendant la
  création.
- Modèle Word : « Préférées » et « Les moins appréciées ».

### Sécurité

- Windows : politique de sécurité du contenu (CSP) activée.

## [1.2.0] - 2026-10-18

Une seule application pour la tablette et Windows.

### Ajouté

- Application tablette (`tablette/`, Vue 3) installable depuis le navigateur
  et utilisable hors ligne, publiée sur
  [GitHub Pages](https://flo91360.github.io/TrameErgo/). Le bilan est rempli
  sur l'appareil, rien n'est envoyé sur Internet.
  - Dix étapes tactiles : patient, demande, suivis, scolarité, OT Hope par
    domaine (« Rien à signaler » par défaut), objectifs numérotés dans
    l'ordre du toucher, aménagements, création du bilan.
  - Âge calculé à la date de passation, modifiable.
  - Brouillon enregistré sur l'appareil à chaque modification et repris au
    retour ; bouton « Nouveau bilan » pour l'effacer.
  - Bilan téléchargé ou partagé (Word, Mail…).
- Version Windows de cette même application, empaquetée par Tauri :
  installateur `TrameErgo-Installation-<version>.exe` installé pour
  l'utilisateur courant, sans droit administrateur. Le bilan est enregistré
  dans `Documents\TrameErgo` puis ouvert dans Word ; Word n'est plus
  nécessaire pour le créer.
- `TESTER.md` : vérifications à faire sur Windows et sur tablette.
- README réécrit : fonctionnement de l'application et façon de l'enrichir.

### Supprimé

- Ancienne application Windows C++/Qt, son installateur Inno Setup et sa
  compilation en CI. Les Releases fournissent désormais l'installateur Tauri.

## [1.1.0] - 2026-10-14

Le contenu du bilan sort du code. Cette version inclut aussi les corrections
prévues pour une 1.0.1, jamais publiée séparément.

### Modifié

- `contenu/questionnaire.json` regroupe toutes les listes de choix et les
  phrases du bilan (classes, motifs, troubles, professionnels, fréquences,
  scolarité, 135 activités OT Hope, aménagements, accord des parents).
  Changer une liste ne demande plus de toucher au code.
- Un seul modèle Word, `contenu/bilan.docx`, au lieu de 20 ; les mots sont
  accordés au sexe par des champs (`{il_elle}`, `{ne_e}`…).
- Un écran OT Hope par domaine avec « Rien à signaler » par défaut ; une
  réponse peut être corrigée.

### Corrigé

- Le modèle était toujours celui d'une fille enfant : il est maintenant
  choisi selon le sexe et l'âge.
- La partie OT Hope et objectifs n'était jamais ajoutée au bilan ; la page
  aménagements et loisirs n'existait pas.
- Âge calculé en mois révolus (10 ans et 11 mois s'affichait 11 ans et
  0 mois).
- Fratrie : « () » quand « Bonne » restait cochée par défaut ; « Enfant
  unique » ne se décochait plus.
- Objectifs : « Aucun » par défaut, sans doublons ; objectifs et remarques
  des parents écrits dans le bilan.
- Liste des troubles en double, « vit avec avec ses 2 parents », tirets
  doublés dans les listes à puces, liste du comportement en classe collée au
  titre, latéralité accordée au masculin.
- Écran de fin : une activité par ligne, message avec le chemin du bilan,
  Word fermé s'il n'a plus de document ouvert.
- Contrôle en CI que les champs du modèle Word correspondent au code.

## [1.0.0] - 2026-10-12

Première version publiée : application Windows C++/Qt.

### Ajouté

- Compilation de l'application et installateur Windows sur GitHub ; Release
  publiée pour chaque nouvelle version, jamais remplacée.
- Installation par utilisateur, modèles copiés dans
  `%LOCALAPPDATA%\TrameErgo`.

### Corrigé

- Ouverture des modèles Word (noms et chemins des écrans 1, 2, 3 et 5).
- Message clair quand Word est absent ou qu'un modèle manque, au lieu d'un
  plantage ; dossier `Documents\TrameErgo` créé si besoin.

[1.2.3]: https://github.com/flo91360/TrameErgo/releases/tag/v1.2.3
[1.2.2]: https://github.com/flo91360/TrameErgo/releases/tag/v1.2.2
[1.2.1]: https://github.com/flo91360/TrameErgo/releases/tag/v1.2.1
[1.2.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.2.0
[1.1.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.1.0
[1.0.0]: https://github.com/flo91360/TrameErgo/releases/tag/v1.0.0
