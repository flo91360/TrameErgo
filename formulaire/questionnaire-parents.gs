/**
 * Lecture des réponses du questionnaire pré-bilan des parents (Google Forms)
 * par TrameErgo. Le formulaire est créé et envoyé aux parents à part ; ce
 * script, publié en application web, renvoie seulement les réponses d'un
 * enfant, à partir de son nom et de son prénom, et seulement si la clé secrète
 * est la bonne.
 *
 * Mode d'emploi : formulaire/README.md.
 */

// Adresse de modification du formulaire (…/forms/d/<ID>/edit). Le compte qui
// publie ce script doit en être propriétaire ou éditeur.
const ADRESSE_FORMULAIRE = '';

/** À exécuter une fois : vérifie l'accès au formulaire et crée la clé secrète. */
function installer() {
  const form = FormApp.openByUrl(ADRESSE_FORMULAIRE);
  const proprietes = PropertiesService.getScriptProperties();
  proprietes.setProperty('FORMULAIRE', form.getId());
  if (!proprietes.getProperty('CLE')) proprietes.setProperty('CLE', Utilities.getUuid());
  Logger.log('Formulaire : ' + form.getTitle() + ' (' + form.getResponses().length + ' réponses)');
  Logger.log('Déployer maintenant le script en application web, puis exécuter lienDeLiaison.');
}

/**
 * Après le déploiement en application web : le lien à coller une fois dans
 * TrameErgo, sur chaque appareil (adresse de l'application web et clé).
 */
function lienDeLiaison() {
  const adresse = ScriptApp.getService().getUrl();
  if (!adresse || !/\/exec$/.test(adresse)) {
    throw new Error("Script pas encore déployé en application web : Déployer > Nouveau déploiement.");
  }
  Logger.log('Lien de liaison à coller dans TrameErgo : ' + adresse + '#cle='
    + PropertiesService.getScriptProperties().getProperty('CLE'));
}

/** Nouvelle clé : les appareils qui avaient l'ancienne n'ont plus accès aux réponses. */
function changerCle() {
  PropertiesService.getScriptProperties().setProperty('CLE', Utilities.getUuid());
  lienDeLiaison();
}

const QUESTION_NOM = "Nom et Prénom de l'enfant";

/**
 * Réponse à TrameErgo : …/exec?cle=…&prenom=…&nom=…
 * Renvoie { reponses: [{ envoi, questions: [{ titre, reponse, lignes? }] }] },
 * les questionnaires de cet enfant seulement, ou { erreur }.
 */
function doGet(e) {
  const parametres = e.parameter || {};
  const proprietes = PropertiesService.getScriptProperties();
  if (!proprietes.getProperty('CLE') || parametres.cle !== proprietes.getProperty('CLE')) {
    return enJson({ erreur: 'cle' });
  }
  const recherche = [
    comparable((parametres.prenom || '') + (parametres.nom || '')),
    comparable((parametres.nom || '') + (parametres.prenom || '')),
  ];
  if (!recherche[0]) return enJson({ erreur: 'nom' });

  const form = FormApp.openById(proprietes.getProperty('FORMULAIRE'));
  const reponses = form.getResponses().filter(function (reponse) {
    const nom = reponse.getItemResponses().filter(function (r) {
      return r.getItem().getTitle() === QUESTION_NOM;
    })[0];
    return nom && recherche.indexOf(comparable(String(nom.getResponse()))) !== -1;
  }).map(function (reponse) {
    return {
      envoi: reponse.getTimestamp().toISOString(),
      questions: reponse.getItemResponses().map(function (r) {
        const item = r.getItem();
        const question = { titre: item.getTitle(), reponse: r.getResponse() };
        if (item.getType() === FormApp.ItemType.GRID) question.lignes = item.asGridItem().getRows();
        return question;
      }),
    };
  });
  return enJson({ reponses: reponses });
}

/** « Léa  DUPONT-Martin » et « lea dupont martin » se valent. */
function comparable(texte) {
  return texte.normalize('NFD').replace(/[\u0300-\u036f]/g, '').toLowerCase().replace(/[^a-z]/g, '');
}

function enJson(valeur) {
  return ContentService.createTextOutput(JSON.stringify(valeur)).setMimeType(ContentService.MimeType.JSON);
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
