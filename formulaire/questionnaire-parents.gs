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
  indexer();
  Logger.log('Déployer maintenant le script en application web, puis exécuter lienDeLiaison.');
}

// Index des réponses par enfant, dans les propriétés du script : une propriété
// par enfant (ENFANT_ suivi de son nom comparable), qui liste ses réponses
// [identifiant, date d'envoi]. La recherche lit l'index sans ouvrir le
// formulaire : Google Forms charge toutes les réponses en entier, ce qui est lent.
const PREFIXE_INDEX = 'ENFANT_';
// Formulaire dont les réponses sont dans l'index (un autre : l'index ne sert pas).
const FORMULAIRE_INDEXE = 'INDEX_FORMULAIRE';

/**
 * Range dans l'index toutes les réponses déjà reçues, et l'y tient à jour à
 * chaque nouvelle réponse (déclencheur « à l'envoi du formulaire »). Exécuté
 * par installer ; à relancer seulement si une réponse a été modifiée à la main.
 */
function indexer() {
  const proprietes = PropertiesService.getScriptProperties();
  const id = proprietes.getProperty('FORMULAIRE');
  if (!id) throw new Error("Exécuter d'abord installer.");
  const form = FormApp.openById(id);
  const champs = questionsDuNom(form);
  const index = {};
  form.getResponses().forEach(function (reponse) {
    const cle = comparable(nomDeLaReponse(reponse, champs));
    if (!cle) return;
    (index[PREFIXE_INDEX + cle] = index[PREFIXE_INDEX + cle] || []).push(entreeDIndex(reponse));
  });
  const lock = LockService.getScriptLock();
  lock.waitLock(30000);
  try {
    Object.keys(proprietes.getProperties()).forEach(function (nom) {
      if (nom.indexOf(PREFIXE_INDEX) === 0) proprietes.deleteProperty(nom);
    });
    const valeurs = {};
    Object.keys(index).forEach(function (nom) { valeurs[nom] = JSON.stringify(index[nom]); });
    valeurs[FORMULAIRE_INDEXE] = id;
    proprietes.setProperties(valeurs);
  } finally {
    lock.releaseLock();
  }
  ScriptApp.getProjectTriggers().forEach(function (declencheur) {
    if (declencheur.getHandlerFunction() === 'indexerReponse') ScriptApp.deleteTrigger(declencheur);
  });
  ScriptApp.newTrigger('indexerReponse').forForm(form).onFormSubmit().create();
  Logger.log('Index : ' + Object.keys(index).length + ' enfant(s). Les nouvelles réponses y seront ajoutées.');
}

/** Déclencheur « à l'envoi du formulaire » : ajoute la réponse à l'index. */
function indexerReponse(e) {
  const proprietes = PropertiesService.getScriptProperties();
  const cle = comparable(nomDeLaReponse(e.response, questionsDuNom(FormApp.openById(proprietes.getProperty('FORMULAIRE')))));
  if (!cle) return;
  modifierIndex(PREFIXE_INDEX + cle, function (liste) {
    return liste.filter(function (entree) { return entree[0] !== e.response.getId(); })
      .concat([entreeDIndex(e.response)]);
  });
}

function entreeDIndex(reponse) {
  return [reponse.getId(), reponse.getTimestamp().toISOString()];
}

/** Modifie la liste d'un enfant dans l'index, une modification à la fois. */
function modifierIndex(nom, modification) {
  const proprietes = PropertiesService.getScriptProperties();
  const lock = LockService.getScriptLock();
  lock.waitLock(30000);
  try {
    const liste = modification(JSON.parse(proprietes.getProperty(nom) || '[]'));
    if (liste.length) proprietes.setProperty(nom, JSON.stringify(liste));
    else proprietes.deleteProperty(nom);
  } finally {
    lock.releaseLock();
  }
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
 *   { envois: [{ id, envoi }] }, les questionnaires de cet enfant, lus dans
 *   l'index (voir indexer) ; sans index, dans le nom de chaque réponse.
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

  // Index à jour pour ce formulaire : la recherche ne l'ouvre même pas.
  const indexe = proprietes.getProperty(FORMULAIRE_INDEXE) === proprietes.getProperty('FORMULAIRE');
  const noms = recherche.map(function (cle) { return PREFIXE_INDEX + cle; })
    .filter(function (nom, i, tous) { return tous.indexOf(nom) === i; });
  if (parametres.etape === 'recherche' && indexe) {
    const envois = [];
    noms.forEach(function (nom) {
      JSON.parse(proprietes.getProperty(nom) || '[]').forEach(function (entree) {
        if (!envois.some(function (envoi) { return envoi.id === entree[0]; })) envois.push({ id: entree[0], envoi: entree[1] });
      });
    });
    return enJson({ envois: envois });
  }

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
      reponse = null; // Réponse supprimée du formulaire : retirée de l'index.
      if (indexe) {
        noms.forEach(function (nom) {
          modifierIndex(nom, function (liste) {
            return liste.filter(function (entree) { return entree[0] !== parametres.id; });
          });
        });
      }
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
