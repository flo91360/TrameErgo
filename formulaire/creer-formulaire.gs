/**
 * Crée dans votre Google Drive le « Questionnaire Pré bilan ergothérapie »,
 * repris à l'identique, sauf les listes « cotation » des parties AU QUOTIDEN,
 * A L'ECOLE et LOISIRS : chacune devient une seule grille, comme les écrans
 * OT Hope de TrameErgo.
 *
 * Utilisation : script.google.com > Nouveau projet > coller ce fichier >
 * Enregistrer > choisir creerFormulaire > Exécuter. Les liens s'affichent
 * dans le journal d'exécution.
 */

const NIVEAUX = ['Rien à signaler', 'Avec aide', 'Avec difficulté', 'Avec grande difficulté'];
const CONSIGNE_GRILLE = "Pour chaque activité, cochez « Rien à signaler » si votre enfant la fait seul sans difficulté, " +
  "sinon le niveau d'aide dont il a besoin. Si votre enfant ne fait pas encore cette activité, laissez la ligne vide.";

const ACTIVITES_QUOTIDIEN = [
  'Faire ses lacets', 'Enfiler ses vêtement (dans le bon sens)', 'Manipuler les boutons',
  'manipuler une fermeture éclair', 'Prendre sa douche seul(e)', 'Se coiffer', 'Se brosser les dents',
  'se couper les ongles', 'tenir ses couverts', 'couper sa viande', "se servir de l'eau",
  'manger et boire proprement', 'circuler sans se heurter', 'traver la rue en sécurité', 'sauter',
  "monter les marches d'escalier", 'plier le linge', 'étendre le linge', 'mettre la table',
  'débarrasser la table', 'éplucher un fruit/ légume', 'téléphoner', 'acheter le pain',
  'Faire son cartable', 'ordonner son bureau/ casier', 'regarder ses devoir sur son agenda/ ENT',
  "s'organiser lors des devoirs à la maison", 'faire ses exercice pour les devoirs',
  'apprendre ses leçons lors de ses devoirs', 'autonomie pour les devoirs',
  "savoir demandé de l'aide pour les devoirs si besoin", 'balayer', "compter l'argent",
  'cuisiner un plat simple', 'enlever la poussière', "passer l'aspirateur", 'ranger sa chambre',
  'sortir les poubelles', "s'occuper des animaux", 'utiliser le micro-onde',
  "s'essuyer quand il est au WC", 'dormir dans son lit toute la nuit', "S'endormir facilement",
  'vider le lave-vaisselle', 'se moucher', 'se réveiller seul', 'attacher sa ceinture en voiture',
  'utiliser des clés',
];
const ACTIVITES_ECOLE = [
  'écrire lisiblement', 'Former toutes les lettres correctement', 'écrire sur les lignes',
  'réussir à se relire', 'savoir où écrire', 'écrire toute une leçon sans se fatiguer', 'écrire au tableau',
  'écrire au bon endroit sur une feuille', 'savoir quoi apprendre', 'dessiner/ colorier', 'Découper',
  'Plier', 'Coller', 'Gommer', 'Souligner', 'Manipuler les outils de géométrie (règle / équerre)',
  'Manipuler le compas', 'Tailler ses crayons de couleurs/ papiers',
  'Tracer un rond/ carré/ triangle à main levée', 'Utiliser la calculatrice', 'Lecture dans sa tête',
  'Lecture voix haute', 'Compter', 'Poser une opération', 'Mémoriser', 'Etre délégué de classe',
  'jouer/ discuter dans la cours de récréation avec des amis', 'se changer correctement lors du sport',
  "Lire l'heure avec les aiguilles", "se repérer dans l'école/ collège", 'ranger ses classeur',
  'Préparer son cartable', "s'installer confortablement à sa place en classe",
  'Retrouver ses affaires dans sa case/ dans son casier', "Utiliser l'ordinateur",
];
const ACTIVITES_LOISIRS = [
  'taper dans le ballon', 'lancer une balle', 'faire de la corde à sauter', 'faire de la trottinette/ vélo',
  'nager', 'activités manuelles', 'dessiner', 'peindre', 'faire des jeux de construction',
  'faire des puzzles', 'enfiler des perles', 'communiquer avec les adultes',
  "s'intégrer avec des camarades", "demande de l'aide", "s'exprimer (écrit, oral)", 'faire du foot',
  'faire du hand', 'faire du basket', 'faire de la danse/ gym', 'faire du volley', 'faire du roller',
  'faire du patin à glace', 'jouer au jeux vidéo', 'écoute de la musique', 'courrir',
  'faire du badminton/ tennis', 'faire du judo/karaté', 'faire du rugby', 'faire du ski', 'bricoler',
  'écrire des histoires', 'jouer au fléchettes', "jouer d'un instrument de musique", 'lire des histoires',
  'faire de la balançoire', 'faire du trampoline', 'grimper', 'jouer à la pétanque/ palet',
  "jouer dans l'eau", 'jouer dans le sable', 'jouer dans la neige', 'se retrouver entre amis',
];
const MATIERES = [
  'Français', 'Histoire-géographie', 'Mathématique', 'SVT', 'Musique', 'Techno', 'Anglais', 'Espagnol',
  'Physique-chimie', 'Art plastique',
];

function creerFormulaire() {
  const form = FormApp.create('Questionnaire Pré bilan ergothérapie')
    .setDescription([
      'Bonjour,',
      'Merci beaucoup de prendre le temps de compléter ce questionnaire.',
      'Il  nous permettra de mieux faire connaissance avec votre enfant avant le bilan, afin de préparer une évaluation',
      'la plus adaptée possible et de personnaliser au mieux notre accompagnement.',
      'Ces informations sont précieuses et contribueront à ce que le temps du bilan se déroule dans les meilleures conditions',
      'pour votre enfant et pour vous.',
      'Merci encore pour votre collaboration.',
    ].join('\n'));

  texte(form, "Nom et Prénom de l'enfant");
  texte(form, 'Date de naissance');
  choix(form, 'Latéralité', ['Droitier', 'Gaucher'], false);
  choix(form, 'Classe', ['CP', 'CE1', 'CE2', 'CM1', 'CM2', '6ème', '5ème', '4ème', '3ème', '2nd', 'Première'], true);
  texte(form, 'Médecin traitant (nom + ville)');
  texte(form, 'Nom + prénom + adresse + téléphone + adresse mail + Profession du parent 1');
  texte(form, 'Nom + prénom + adresse + téléphone + adresse mail + Profession du parent 2');
  texte(form, 'Fraterie');
  texte(form, 'Mode de garde (si parents séparés)');
  texte(form, "Qui est à l'origine de la demande de réalisation du bilan (médecin traitant ou autre professionnel de santé, instituteurs/professeurs…) ?");
  cases(form, 'Quel est le motif du Bilan, quelles problématiques rencontrez-vous ?', [
    "difficulté d'écriture", 'difficulté de concentration', "difficulté de visualisation dans l'espace",
    'difficulté de coordination',
  ]);
  texte(form, 'Avez vous des inquiétudes particulières ?');
  cases(form, "Y a-t-il d'autres bilans qui ont été réalisé précédemment ?", [
    'Bilan psychomoteur', 'Bilan orthophonique', 'Bilan Orthoptique', 'Bilan neuropsychologique',
    'Bilan ophtalmologique', 'Bilan audio (ORL)',
  ]);
  cases(form, 'A ce jour, quel(s) trouble(s) ont été diagnostiqués ?', [
    'Dyslexie', 'Dysorthographie', "Dyspraxie / trouble de l'acquisition des coordination",
    'Trouble du spectre Autistique', 'Trouble du spectre Autistique - type Asperger', 'Dysgraphie',
    "Trouble de l'attention sans hyperactivité sans trouble oppositionnel",
    "Trouble de l'attention avec hyperactivité sans trouble oppositionnel",
    "Trouble de l'attention sans hyperactivité avec trouble oppositionnel",
    "Trouble de l'attention avec hyperactivité avec trouble oppositionnel",
  ]);
  choix(form, 'Porte des lunettes ? (si oui pensez à les amener au bilan)', ['Oui', 'Non', 'Parfois'], true);
  choix(form, 'Porte un appareil auditif ? (si oui le porter le jour du bilan)', ['Oui', 'Non', 'Parfois'], true);
  texte(form, "Autre professionnel suivant l'enfant ? (avec la fréquence de suivi)");
  choix(form, 'Dossier MDPH', ['En cours de création', 'NON', 'En renouvellement'], true);
  texte(form, "Antécédents familiaux en lien avec la/les difficultés de l'enfant qui amène(nt) à consulter :");
  cases(form, 'Déroulement de la grossesse ?', [
    'Classique', 'quelques complications (médicales ou autres)', 'dépression pré natale',
  ]);
  cases(form, "Déroulement de l'accouchement ?", [
    'à terme', 'Prématuré', 'voie basse', 'césarienne', 'Forceps', "score d'Apgar si connu",
  ]);
  texte(form, 'Santé globale (Hospitalisations, opérations, otites à répétition, troubles du sommeil ou de l\'alimentation.)');
  texte(form, 'Développement : A quel âge le retournement a t il été acquis ?');
  texte(form, 'Développement : A quel âge la station assise a t elle été acquise ?');
  texte(form, 'Développement : A quel âge le quatre-pattes et/ou ramper ont ils été acquis ?');
  choix(form, "Développement : S'est déplacé(e) au sol", [
    "S'est déplacé(e) au sol 4 pattes ?", "S'est déplacé(e) au sol en rampant",
    "S'est déplacé(e) sur les fesses", "Ne s'est pas déplacé(e) au sol",
  ], true);
  texte(form, 'Développement : station debout et marche autonome');
  texte(form, 'Développement : de la propreté (diurne/ nocture)');
  cases(form, "Plus jeune, l'enfant était :", ['Plutôt actif', 'plutôt passif', 'qui pleurait peu', 'qui pleurait beaucoup']);
  cases(form, 'Actuellement votre enfant est :', [
    'Sociable', 'Peu sociable', 'Très sensible', 'Empathique', "Intolérant à l'injustice",
    'Intolérant à la frustration', 'Facilement dans le conflit', 'Influençable', 'Teste souvent le cadre',
    'Provocateur',
  ]);
  cases(form, 'Sur le plan de la motricité globale et de la coordination :', [
    'Est plutôt adroit(e)', 'Est plutôt maladroit(e)', "Est à l'aise dans son corps",
    "N'est pas très à l'aise dans son corps", "Est à l'aise dans diverses activités (course, nage, vélo, etc.)",
    "N'est pas à l'aise dans diverses activités (course, le vélo, etc.)",
  ]);
  cases(form, 'Sur le plan de la motricité fine :', [
    "Est plutôt adroit(e) lorsqu'il s'agit de faire des tâches nécessitants minutie (faire ses lacets: tenir des couverts, faire un puzzle; ect.)",
    'Est plutôt maladroit(e) dans les tâches nécessitants minutie (faire ses lacets ; tenir des couverts; faire un puzzle; ect.)',
  ]);
  texte(form, 'Langage : Âge des premiers mots, premières phrases.');
  cases(form, 'Gestion des émotions :', [
    'Est de nature anxieuse', 'Sujet à des colères fréquentes', 'Verbalise ses émotions facilement',
    'Garde ses émotions (garde tout pour lui)', 'Exprime ses frustrations en "non verbal" (action, mimique, attitude...)',
  ]);
  cases(form, "L'attention", [
    'Peut-il rester concentré sur une tâche ?', "Est-il facilement distrait par les bruits ou l'environnement ?",
  ]);

  // AU QUOTIDEN : la grille remplace les 5 listes « cotation 0 à 4 » et leur consigne
  form.addSectionHeaderItem().setTitle('Questions concernant les facilités et difficultés de votre enfant - AU QUOTIDEN');
  grille(form, ACTIVITES_QUOTIDIEN);
  texte(form, 'Y a t il des précisions sur certaines activités ?');

  // A L'ECOLE : la grille remplace les 6 listes « cotation 0 à 5 » et leur consigne
  form.addSectionHeaderItem().setTitle("Questions concernant les facilités et difficultés de votre enfant - A L'ECOLE");
  grille(form, ACTIVITES_ECOLE);
  texte(form, 'Y a t il des précisions sur certaines activités ?');
  cases(form, 'Matières préférées', MATIERES);
  cases(form, 'Matières moins appréciées', MATIERES);
  cases(form, "Qu'est-ce qui est difficile en classe ?", [
    'la concentration toute la journée', 'la concentration le matin', "la concentration l'après-midi",
    'Ecrire vite et bien', "s'organiser", "douleur à l'écriture", 'pour participer',
  ]);
  cases(form, 'Y a t il eu des aménagements ?', [
    'AESH', 'Polycopier fournis dans certaines matières', 'Tiers-temps',
    "réduction du nombre d'exercice lors des évaluations", 'adaptation des barèmes',
    'Texte plus grand et/ou bien espacé', 'dictée à trou', 'polycopier à trou', 'PAP', 'PPS', 'PPRE',
  ]);
  texte(form, 'Avez vous des choses à rajouter ?');

  // LOISIRS : la grille remplace les 6 listes « cotation 0 à 5 » et leur consigne
  form.addSectionHeaderItem().setTitle('Questions concernant les facilités et difficultés de votre enfant - dans les LOISIRS');
  grille(form, ACTIVITES_LOISIRS);
  texte(form, 'Quelles sont les activités extra-scolaire ? A quelle fréquence ?');
  texte(form, 'Quelles sont les activités de temps libre ?');
  texte(form, 'Y a t il des difficultés lors des loisirs ?');
  choix(form, "Votre enfant a t il déjà un connaissance de l'outil informatique ?", ['Oui', 'Un peu', 'Moyennement', 'Non'], true);
  texte(form, 'Avez vous des choses à rajouter ?');

  try { form.setPublished(true); } catch (e) { /* ancienne version de Google Forms */ }

  Logger.log('Modifier le formulaire : ' + form.getEditUrl());
  Logger.log('Lien à envoyer aux parents : ' + form.getPublishedUrl());
}

function grille(form, activites) {
  form.addGridItem()
    .setTitle("Niveau d'aide pour chaque activité")
    .setHelpText(CONSIGNE_GRILLE)
    .setRows(activites)
    .setColumns(NIVEAUX);
}

function texte(form, titre) {
  form.addTextItem().setTitle(titre);
}

function choix(form, titre, options, autre) {
  form.addMultipleChoiceItem().setTitle(titre).setChoiceValues(options).showOtherOption(autre);
}

function cases(form, titre, options) {
  form.addCheckboxItem().setTitle(titre).setChoiceValues(options).showOtherOption(true);
}
