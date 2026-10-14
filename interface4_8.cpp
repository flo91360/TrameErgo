#include "interface4_8.h"
#include "ui_interface4_8.h"
#include "patient.h"
#include "word.h"
#include "interface5.h"

// « Aucun » en premier : sans choix, aucun objectif n'est retenu (avant, la
// première activité était choisie par défaut dans les 5 listes).
static void remplir(const QList<QComboBox*> &choix, const QStringList &activites)
{
    for (QComboBox *combo : choix) {
        combo->addItem("Aucun");
        combo->addItems(activites);
    }
}

// Activités choisies, sans « Aucun » ni doublon.
static QStringList choisis(const QList<QComboBox*> &choix)
{
    QStringList objectifs;
    for (const QComboBox *combo : choix) {
        const QString activite = combo->currentText();
        if (activite != "Aucun" && !objectifs.contains(activite))
            objectifs << activite;
    }
    return objectifs;
}

// Liste numérotée « 1 - objectif », une ligne par objectif.
static QString numerotes(const QStringList &objectifs)
{
    QString liste;
    for (int i = 0; i < objectifs.size(); ++i) {
        liste += QString::number(i + 1) + " - " + objectifs[i] + "\n";
    }
    return liste;
}

Interface4_8::Interface4_8(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_8)
{
    ui->setupUi(this);

    remplir(choixPatient(), Patient::objectfisFinauxPossibles);
    remplir(choixParents(), Patient::objectfisFinauxPossibles);
}

Interface4_8::~Interface4_8()
{
    delete ui;
}

QList<QComboBox*> Interface4_8::choixPatient() const
{
    return {ui->comboBoxChoix1ObjectfisFinauxPatient, ui->comboBoxChoix2ObjectfisFinauxPatient,
            ui->comboBoxChoix3ObjectfisFinauxPatient, ui->comboBoxChoix4ObjectfisFinauxPatient,
            ui->comboBoxChoix5ObjectfisFinauxPatient};
}

QList<QComboBox*> Interface4_8::choixParents() const
{
    return {ui->comboBoxChoix1ObjectfisFinauxParents, ui->comboBoxChoix2ObjectfisFinauxParents,
            ui->comboBoxChoix3ObjectfisFinauxParents, ui->comboBoxChoix4ObjectfisFinauxParents,
            ui->comboBoxChoix5ObjectfisFinauxParents};
}


void Interface4_8::on_pushButtonValiderObjectifsFinaux_clicked()
{
    ui->labelAccordParents->setEnabled(true);
    ui->comboBoxAccordParents->setEnabled(true);
    ui->labelObjectifsParents->setEnabled(true);
    ui->labelChoix1ObjectfisFinauxParents->setEnabled(true);
    ui->labelChoix2ObjectfisFinauxParents->setEnabled(true);
    ui->labelChoix3ObjectfisFinauxParents->setEnabled(true);
    ui->labelChoix4ObjectfisFinauxParents->setEnabled(true);
    ui->labelChoix5ObjectfisFinauxParents->setEnabled(true);
    ui->comboBoxChoix1ObjectfisFinauxParents->setEnabled(true);
    ui->comboBoxChoix2ObjectfisFinauxParents->setEnabled(true);
    ui->comboBoxChoix3ObjectfisFinauxParents->setEnabled(true);
    ui->comboBoxChoix4ObjectfisFinauxParents->setEnabled(true);
    ui->comboBoxChoix5ObjectfisFinauxParents->setEnabled(true);
    ui->textEditRemarquesParents->setEnabled(true);
    ui->pushButtonSuivant->setEnabled(true);
}


void Interface4_8::on_pushButtonSuivant_clicked()
{
    // Lus ici : valider deux fois créait des doublons, et un choix modifié
    // après « Valider » était perdu.
    Patient::objectfisFinauxPatients = choisis(choixPatient());

    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        // Section OT Hope et objectifs, insérée là où interface3 l'attend.
        Word::insereModele("i_interface4", Word::modele("interface4"));

        Word::replaceText("i_aide_maison",Patient::aideMaison);
        Word::replaceText("i_aide_ecole",Patient::aideEcole);
        Word::replaceText("i_aide_loisirs",Patient::aideLoisirs);
        Word::replaceText("i_difficulte_maison",Patient::difficulteMaison);
        Word::replaceText("i_difficulte_ecole",Patient::difficulteEcole);
        Word::replaceText("i_difficulte_loisirs",Patient::difficulteLoisirs);
        Word::replaceText("i_grande_difficulte_maison",Patient::grandeDifficulteMaison);
        Word::replaceText("i_grande_difficulte_ecole",Patient::grandeDifficulteEcole);
        Word::replaceText("i_grande_difficulte_loisirs",Patient::grandeDifficulteLoisirs);

        Word::replaceText("i_objectifs_activites_vie_quotidienne",numerotes(Patient::objectfisAVQPatient));
        Word::replaceText("i_objectifs_activites_scolaires",numerotes(Patient::objectfisAVSPatient));
        Word::replaceText("i_objectifs_activites_loisirs",numerotes(Patient::objectfisAVLPatient));

        Word::replaceText("i_prenom",Patient::prenomPatient);

        QString phraseAccordParents;

        if(ui->comboBoxAccordParents->currentText() == "Oui" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " sont en accord avec les objectifs qui lui paraissent importants";
        }
        else if(ui->comboBoxAccordParents->currentText() == "Non" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " ne sont pas en accord avec les objectifs qui lui paraissent importants";
        }
        else if(ui->comboBoxAccordParents->currentText() == "Pas tout à fait" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " ne sont pas totalement en accord avec les objectifs qui lui paraissent importants";
        }

        Word::replaceText("i_en_accord",phraseAccordParents);

        Word::replaceText("i_objectifs_finaux",numerotes(Patient::objectfisFinauxPatients));

        // Objectifs et remarques des parents : saisis mais jamais écrits jusqu'ici.
        QString objectifsParents = numerotes(choisis(choixParents()));
        const QString remarques = ui->textEditRemarquesParents->toPlainText().trimmed();
        if (!remarques.isEmpty())
            objectifsParents += "Remarques des parents : " + remarques;
        Word::replaceText("i_objectifs_parents",objectifsParents);

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");

        // Next interface
        Interface5 *interface5 = new Interface5();
        this->hide();
        interface5->show();
    }
}
