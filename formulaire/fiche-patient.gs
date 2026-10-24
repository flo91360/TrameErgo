/**
 * Fiche patient Word créée dans le Google Drive à chaque réponse au
 * questionnaire des parents : toutes les réponses, rangées sous les titres du
 * formulaire (sections et encadrés), dans le dossier ERGO/questionnaire pré-bilan.
 *
 * À ajouter au projet Apps Script de questionnaire-parents.gs : il en reprend
 * le formulaire (installer) et la fonction comparable. Mode d'emploi :
 * formulaire/README.md.
 */

// Dossier du Drive où ranger les fiches, depuis « Mon Drive » ; créé s'il manque.
const DOSSIER_FICHES = ['ERGO', 'questionnaire pré-bilan'];
const TYPE_WORD = 'application/vnd.openxmlformats-officedocument.wordprocessingml.document';

/** À exécuter une fois : crée la fiche à chaque nouvelle réponse au formulaire. */
function installerFichePatient() {
  const form = formulaireDeLaFiche();
  retirerFichePatient();
  ScriptApp.newTrigger('creerFichePatient').forForm(form).onFormSubmit().create();
  Logger.log('Une fiche sera créée dans « ' + DOSSIER_FICHES.join('/') + ' » à chaque réponse à : ' + form.getTitle());
}

/** Arrête la création automatique des fiches. */
function retirerFichePatient() {
  ScriptApp.getProjectTriggers().forEach(function (declencheur) {
    if (declencheur.getHandlerFunction() === 'creerFichePatient') ScriptApp.deleteTrigger(declencheur);
  });
}

/** Essai : fiche de la dernière réponse reçue. */
function essayerFichePatient() {
  const reponses = formulaireDeLaFiche().getResponses();
  if (!reponses.length) throw new Error("Le formulaire n'a encore aucune réponse.");
  Logger.log('Fiche créée : ' + ficheDeLaReponse(reponses[reponses.length - 1]).getUrl());
}

/** Déclencheur « à l'envoi du formulaire ». */
function creerFichePatient(e) {
  ficheDeLaReponse(e.response);
}

function formulaireDeLaFiche() {
  const id = PropertiesService.getScriptProperties().getProperty('FORMULAIRE');
  if (!id) throw new Error("Exécuter d'abord installer (questionnaire-parents.gs).");
  return FormApp.openById(id);
}

/** Crée le Word de cette réponse dans le dossier des fiches et le renvoie. */
function ficheDeLaReponse(reponse) {
  const form = formulaireDeLaFiche();
  const parQuestion = {};
  reponse.getItemResponses().forEach(function (r) { parQuestion[r.getItem().getId()] = r.getResponse(); });

  const enfant = enfantDeLaFiche(form, parQuestion);
  const envoi = reponse.getTimestamp();
  const fuseau = Session.getScriptTimeZone();
  const nom = ['Fiche_patient', enfant.nom.toUpperCase(), enfant.prenom,
    Utilities.formatDate(envoi, fuseau, 'yyyy-MM-dd')]
    .map(function (morceau) { return morceau.trim().replace(/[\\/:*?"<>|]/g, '').replace(/\s+/g, '_'); })
    .filter(String).join('_');

  // Document Google provisoire, converti en Word puis mis à la corbeille.
  const doc = DocumentApp.create(nom);
  const corps = doc.getBody();
  corps.appendParagraph('Fiche patient').setHeading(DocumentApp.ParagraphHeading.TITLE);
  corps.appendParagraph([enfant.prenom, enfant.nom.toUpperCase()].filter(String).join(' ') || 'Enfant sans nom')
    .setHeading(DocumentApp.ParagraphHeading.SUBTITLE);
  corps.appendParagraph('Questionnaire « ' + form.getTitle() + ' » envoyé le '
    + Utilities.formatDate(envoi, fuseau, "dd/MM/yyyy 'à' HH:mm") + '.');

  // Un titre n'est écrit que s'il a au moins une réponse en dessous.
  let section = null;
  let encadre = null;
  const ecrireTitres = function () {
    if (section) corps.appendParagraph(section).setHeading(DocumentApp.ParagraphHeading.HEADING1);
    if (encadre) corps.appendParagraph(encadre).setHeading(DocumentApp.ParagraphHeading.HEADING2);
    section = null;
    encadre = null;
  };

  form.getItems().forEach(function (item) {
    const type = item.getType();
    if (type === FormApp.ItemType.PAGE_BREAK) { section = item.getTitle(); encadre = null; return; }
    if (type === FormApp.ItemType.SECTION_HEADER) { encadre = item.getTitle(); return; }
    if (!(item.getId() in parQuestion)) return;
    const valeur = parQuestion[item.getId()];

    if (type === FormApp.ItemType.GRID || type === FormApp.ItemType.CHECKBOX_GRID) {
      const lignes = type === FormApp.ItemType.GRID ? item.asGridItem().getRows() : item.asCheckboxGridItem().getRows();
      const cellules = lignes.map(function (ligne, i) {
        const colonne = valeur[i];
        return [ligne, Array.isArray(colonne) ? colonne.join(', ') : colonne || ''];
      }).filter(function (cellule) { return cellule[1]; });
      if (!cellules.length) return;
      ecrireTitres();
      corps.appendParagraph(item.getTitle()).setBold(true);
      corps.appendTable(cellules);
      return;
    }

    const texte = texteDeLaReponse(valeur);
    if (!texte) return;
    ecrireTitres();
    const titre = item.getTitle().replace(/\s*:\s*$/, '');
    const paragraphe = corps.appendParagraph(titre + ' : ' + texte);
    paragraphe.editAsText().setBold(false).setBold(0, titre.length + 1, true);
  });
  doc.saveAndClose();

  const word = UrlFetchApp.fetch('https://www.googleapis.com/drive/v3/files/' + doc.getId()
    + '/export?mimeType=' + encodeURIComponent(TYPE_WORD), {
    headers: { Authorization: 'Bearer ' + ScriptApp.getOAuthToken() },
  }).getBlob().setName(nom + '.docx');
  const fichier = dossierDesFiches().createFile(word);
  DriveApp.getFileById(doc.getId()).setTrashed(true);
  return fichier;
}

/** Texte d'une réponse : cases cochées séparées par des virgules, date AAAA-MM-JJ en JJ/MM/AAAA. */
function texteDeLaReponse(valeur) {
  const texte = (Array.isArray(valeur) ? valeur.filter(String).join(', ') : String(valeur || '')).trim();
  const date = texte.match(/^(\d{4})-(\d{2})-(\d{2})$/);
  return date ? date[3] + '/' + date[2] + '/' + date[1] : texte;
}

/** Nom et prénom : questions « Nom » et « Prénom » sous « Enfant », ou « Nom et Prénom de l'enfant ». */
function enfantDeLaFiche(form, parQuestion) {
  const enfant = { nom: '', prenom: '' };
  let partie = '';
  form.getItems().forEach(function (item) {
    const type = item.getType();
    if (type === FormApp.ItemType.SECTION_HEADER || type === FormApp.ItemType.PAGE_BREAK) {
      partie = item.getTitle();
      return;
    }
    const valeur = texteDeLaReponse(parQuestion[item.getId()]);
    if (!valeur) return;
    const titre = comparable(item.getTitle());
    if (comparable(partie) === comparable(PARTIE_ENFANT) && titre === 'nom') enfant.nom = valeur;
    if (comparable(partie) === comparable(PARTIE_ENFANT) && titre === 'prenom') enfant.prenom = valeur;
    if (titre === comparable(QUESTION_NOM) && !enfant.nom) enfant.nom = valeur;
  });
  return enfant;
}

/** Dossier ERGO/questionnaire pré-bilan de « Mon Drive » ; chaque dossier manquant est créé. */
function dossierDesFiches() {
  return DOSSIER_FICHES.reduce(function (parent, nom) {
    const existants = parent.getFoldersByName(nom);
    while (existants.hasNext()) {
      const dossier = existants.next();
      if (!dossier.isTrashed()) return dossier;
    }
    return parent.createFolder(nom);
  }, DriveApp.getRootFolder());
}
