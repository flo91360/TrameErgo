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
 * Réponse à TrameErgo, en deux temps :
 * - recherche : …/exec?cle=…&prenom=…&nom=…&etape=recherche renvoie
 *   { envois: [{ id, envoi }] }, les questionnaires de cet enfant. Seul le nom
 *   de l'enfant est lu dans chaque réponse : la recherche reste rapide.
 * - importation : …/exec?cle=…&prenom=…&nom=…&id=… renvoie
 *   { reponses: [{ envoi, questions: [{ titre, partie?, reponse, lignes? }] }] },
 *   ce questionnaire seulement, s'il est bien au nom de cet enfant.
 * Sans etape ni id (TrameErgo avant la version 1.6.18) : toutes les réponses de
 * cet enfant, au format de l'importation. En cas de problème : { erreur }.
 * partie : titre de l'encadré ou de la section où se trouve la question (« Parent 1 »…).
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
  const champsNom = questionsDuNom(form);
  const deLEnfant = function (reponse) {
    return recherche.indexOf(comparable(nomDeLaReponse(reponse, champsNom))) !== -1;
  };

  if (parametres.id) {
    let reponse = null;
    try {
      reponse = form.getResponse(parametres.id);
    } catch (erreur) {
      reponse = null; // Réponse supprimée du formulaire.
    }
    if (!reponse || !deLEnfant(reponse)) return enJson({ reponses: [] });
    return enJson({ reponses: [lireReponse(reponse, descriptionDesQuestions(form))] });
  }

  const trouvees = form.getResponses().filter(deLEnfant);
  if (parametres.etape === 'recherche') {
    return enJson({ envois: trouvees.map(function (reponse) {
      return { id: reponse.getId(), envoi: reponse.getTimestamp().toISOString() };
    }) });
  }
  const questions = descriptionDesQuestions(form);
  return enJson({ reponses: trouvees.map(function (reponse) { return lireReponse(reponse, questions); }) });
}

/** Toutes les réponses d'un questionnaire, au format attendu par TrameErgo. */
function lireReponse(reponse, questions) {
  return {
    envoi: reponse.getTimestamp().toISOString(),
    questions: reponse.getItemResponses().map(function (r) {
      const description = questions[r.getItem().getId()] || { titre: r.getItem().getTitle() };
      const question = { titre: description.titre, reponse: r.getResponse() };
      if (description.partie) question.partie = description.partie;
      if (description.lignes) question.lignes = description.lignes;
      return question;
    }),
  };
}

/**
 * Les questions qui portent le nom de l'enfant : « Nom et Prénom de l'enfant »
 * (complet), ou « Prénom » et « Nom » sous le titre « Enfant ».
 */
function questionsDuNom(form) {
  const champs = { complet: null, prenom: null, nom: null };
  let partie = '';
  form.getItems().forEach(function (item) {
    const type = item.getType();
    if (type === FormApp.ItemType.SECTION_HEADER || type === FormApp.ItemType.PAGE_BREAK) {
      partie = item.getTitle();
      return;
    }
    // Comparaison sans majuscules, accents ni ponctuation : « Nom et Prénom de l’enfant : » convient.
    const titre = comparable(item.getTitle());
    if (titre === comparable(QUESTION_NOM) && !champs.complet) champs.complet = item;
    if (comparable(partie) === comparable(PARTIE_ENFANT)) {
      if (titre === 'prenom' && !champs.prenom) champs.prenom = item;
      if (titre === 'nom' && !champs.nom) champs.nom = item;
    }
  });
  return champs;
}

/** Nom de l'enfant dans une réponse, en ne lisant que les questions du nom. */
function nomDeLaReponse(reponse, champs) {
  const texte = function (item) {
    const r = item ? reponse.getResponseForItem(item) : null;
    return r ? String(r.getResponse()) : '';
  };
  return texte(champs.complet) || texte(champs.prenom) + texte(champs.nom);
}

/**
 * Pour chaque question (par identifiant) : son titre, le titre du dernier
 * encadré ou début de section placé au-dessus (partie), et les lignes d'une grille.
 */
function descriptionDesQuestions(form) {
  const questions = {};
  let partie = '';
  form.getItems().forEach(function (item) {
    const type = item.getType();
    if (type === FormApp.ItemType.SECTION_HEADER || type === FormApp.ItemType.PAGE_BREAK) {
      partie = item.getTitle();
      return;
    }
    const question = { titre: item.getTitle() };
    if (partie) question.partie = partie;
    if (type === FormApp.ItemType.GRID) question.lignes = item.asGridItem().getRows();
    questions[item.getId()] = question;
  });
  return questions;
}

/** « Léa  DUPONT-Martin » et « lea dupont martin » se valent. */
function comparable(texte) {
  return texte.normalize('NFD').replace(/[\u0300-\u036f]/g, '').toLowerCase().replace(/[^a-z]/g, '');
}

function enJson(valeur) {
  return ContentService.createTextOutput(JSON.stringify(valeur)).setMimeType(ContentService.MimeType.JSON);
}
