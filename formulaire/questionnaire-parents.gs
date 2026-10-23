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
  const cle = PropertiesService.getScriptProperties().getProperty('CLE');
  if (!cle) throw new Error("Exécuter d'abord installer.");
  // Lancé depuis l'éditeur, getUrl renvoie souvent l'adresse de test (…/dev),
  // pas celle de l'application web déployée (…/exec).
  const adresse = ScriptApp.getService().getUrl() || '';
  if (/\/exec$/.test(adresse)) {
    Logger.log('Lien de liaison à coller dans TrameErgo : ' + adresse + '#cle=' + cle);
  } else {
    Logger.log("Lien de liaison : copier l'URL de l'application web (Déployer > Gérer les déploiements, "
      + "elle finit par /exec), puis y ajouter, sans espace : #cle=" + cle);
  }
}

/** Nouvelle clé : les appareils qui avaient l'ancienne n'ont plus accès aux réponses. */
function changerCle() {
  PropertiesService.getScriptProperties().setProperty('CLE', Utilities.getUuid());
  lienDeLiaison();
}

const QUESTION_NOM = "Nom et Prénom de l'enfant";
// Ou, si le nom est découpé : questions « Nom » et « Prénom » sous le titre « Enfant ».
const PARTIE_ENFANT = 'Enfant';

/**
 * Réponse à TrameErgo : …/exec?cle=…&prenom=…&nom=…
 * Renvoie { reponses: [{ envoi, questions: [{ titre, partie?, reponse, lignes? }] }] },
 * les questionnaires de cet enfant seulement, ou { erreur }. partie : titre de
 * l'encadré ou de la section où se trouve la question (« Parent 1 »…).
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
  const parties = partiesDesQuestions(form);
  const reponses = form.getResponses().map(function (reponse) {
    return {
      envoi: reponse.getTimestamp().toISOString(),
      questions: reponse.getItemResponses().map(function (r) {
        const item = r.getItem();
        const question = { titre: item.getTitle(), reponse: r.getResponse() };
        if (parties[item.getId()]) question.partie = parties[item.getId()];
        if (item.getType() === FormApp.ItemType.GRID) question.lignes = item.asGridItem().getRows();
        return question;
      }),
    };
  }).filter(function (reponse) {
    return recherche.indexOf(comparable(nomDeLEnfant(reponse.questions))) !== -1;
  });
  return enJson({ reponses: reponses });
}

/** Pour chaque question, le titre du dernier encadré ou début de section placé au-dessus. */
function partiesDesQuestions(form) {
  const parties = {};
  let partie = '';
  form.getItems().forEach(function (item) {
    const type = item.getType();
    if (type === FormApp.ItemType.SECTION_HEADER || type === FormApp.ItemType.PAGE_BREAK) partie = item.getTitle();
    else if (partie) parties[item.getId()] = partie;
  });
  return parties;
}

function nomDeLEnfant(questions) {
  const texte = function (titre, partie) {
    const question = questions.filter(function (q) {
      // Comparaison sans majuscules, accents ni ponctuation : « Nom et Prénom de l’enfant : » convient.
      return comparable(q.titre) === comparable(titre) && (!partie || comparable(q.partie || '') === comparable(partie));
    })[0];
    return question ? String(question.reponse) : '';
  };
  return texte(QUESTION_NOM) || texte('Prénom', PARTIE_ENFANT) + texte('Nom', PARTIE_ENFANT);
}

/** « Léa  DUPONT-Martin » et « lea dupont martin » se valent. */
function comparable(texte) {
  return texte.normalize('NFD').replace(/[\u0300-\u036f]/g, '').toLowerCase().replace(/[^a-z]/g, '');
}

function enJson(valeur) {
  return ContentService.createTextOutput(JSON.stringify(valeur)).setMimeType(ContentService.MimeType.JSON);
}
