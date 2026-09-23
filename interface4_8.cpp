#include "interface4_8.h"
#include "ui_interface4_8.h"
#include "patient.h"
#include "word.h"
#include "interface5.h"

Interface4_8::Interface4_8(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_8)
{
    ui->setupUi(this);

    ui->comboBoxChoix1ObjectfisFinauxPatient->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix2ObjectfisFinauxPatient->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix3ObjectfisFinauxPatient->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix4ObjectfisFinauxPatient->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix5ObjectfisFinauxPatient->addItems(Patient::objectfisFinauxPossibles);

    ui->comboBoxChoix1ObjectfisFinauxPatient->addItem("Aucun");
    ui->comboBoxChoix2ObjectfisFinauxPatient->addItem("Aucun");
    ui->comboBoxChoix3ObjectfisFinauxPatient->addItem("Aucun");
    ui->comboBoxChoix4ObjectfisFinauxPatient->addItem("Aucun");
    ui->comboBoxChoix5ObjectfisFinauxPatient->addItem("Aucun");


    ui->comboBoxChoix1ObjectfisFinauxParents->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix2ObjectfisFinauxParents->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix3ObjectfisFinauxParents->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix4ObjectfisFinauxParents->addItems(Patient::objectfisFinauxPossibles);
    ui->comboBoxChoix5ObjectfisFinauxParents->addItems(Patient::objectfisFinauxPossibles);

    ui->comboBoxChoix1ObjectfisFinauxParents->addItem("Aucun");
    ui->comboBoxChoix2ObjectfisFinauxParents->addItem("Aucun");
    ui->comboBoxChoix3ObjectfisFinauxParents->addItem("Aucun");
    ui->comboBoxChoix4ObjectfisFinauxParents->addItem("Aucun");
    ui->comboBoxChoix5ObjectfisFinauxParents->addItem("Aucun");
}

Interface4_8::~Interface4_8()
{
    delete ui;
}



void Interface4_8::on_pushButtonValiderObjectifsFinaux_clicked()
{
    if(ui->comboBoxChoix1ObjectfisFinauxPatient->currentText() != "Aucun"){
        Patient::objectfisFinauxPatients.append(ui->comboBoxChoix1ObjectfisFinauxPatient->currentText());
    }
    if(ui->comboBoxChoix2ObjectfisFinauxPatient->currentText() != "Aucun"){
        Patient::objectfisFinauxPatients.append(ui->comboBoxChoix2ObjectfisFinauxPatient->currentText());
    }
    if(ui->comboBoxChoix3ObjectfisFinauxPatient->currentText() != "Aucun"){
        Patient::objectfisFinauxPatients.append(ui->comboBoxChoix3ObjectfisFinauxPatient->currentText());
    }
    if(ui->comboBoxChoix4ObjectfisFinauxPatient->currentText() != "Aucun"){
        Patient::objectfisFinauxPatients.append(ui->comboBoxChoix4ObjectfisFinauxPatient->currentText());
    }
    if(ui->comboBoxChoix5ObjectfisFinauxPatient->currentText() != "Aucun"){
        Patient::objectfisFinauxPatients.append(ui->comboBoxChoix5ObjectfisFinauxPatient->currentText());
    }

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

    qDebug() << "go to interface 5";


}


void Interface4_8::on_pushButtonSuivant_clicked()
{
    // Word::copieColle(Word::pathToArbo + "/arborescence/Femme/Enfant/Interface4/interface4.docx", Word::filePathToSave);

    // qDebug() << "filePathToSave";

    Word::document = Word::documents->querySubObject("Open(const QString&)",  Word::filePathToSave);
    if (!Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");


        Word::replaceText("i_aide_maison",Patient::aideMaison);
        Word::replaceText("i_aide_ecole",Patient::aideEcole);
        Word::replaceText("i_aide_loisirs",Patient::aideLoisirs);
        Word::replaceText("i_difficulte_maison",Patient::difficulteMaison);
        Word::replaceText("i_difficulte_ecole",Patient::difficulteEcole);
        Word::replaceText("i_difficulte_loisirs",Patient::difficulteLoisirs);
        Word::replaceText("i_grande_difficulte_maison",Patient::grandeDifficulteMaison);
        Word::replaceText("i_grande_difficulte_ecole",Patient::grandeDifficulteEcole);
        Word::replaceText("i_grande_difficulte_loisirs",Patient::grandeDifficulteLoisirs);

        qDebug() << "ALED";
        qDebug() << Patient::objectfisAVQPatient;
        qDebug() << Patient::objectfisAVSPatient;
        qDebug() << Patient::objectfisAVLPatient;

        QString listAVQ;
        for (int i = 0; i < Patient::objectfisAVQPatient.size(); ++i) {
            listAVQ += QString::number(i + 1) + " - " + Patient::objectfisAVQPatient[i] + "\n";
        }

        QString listAVS;
        for (int i = 0; i < Patient::objectfisAVSPatient.size(); ++i) {
            listAVS += QString::number(i + 1) + " - " + Patient::objectfisAVSPatient[i] + "\n";
        }

        QString listAVL;
        for (int i = 0; i < Patient::objectfisAVLPatient.size(); ++i) {
            listAVL += QString::number(i + 1) + " - " + Patient::objectfisAVLPatient[i] + "\n";
        }

        qDebug() << "ALED1";
        Word::replaceText("i_objectifs_activites_vie_quotidienne",listAVQ);
        qDebug() << "ALED2";
        Word::replaceText("i_obejctifs_activites_scolaires",listAVS);
        Word::replaceText("i_objectifs_activites_loisirs",listAVL);

        Word::replaceText("i_prenom",Patient::prenomPatient);

        QString phraseAccordParents;

        qDebug() << ui->comboBoxAccordParents->currentText() ;

        if(ui->comboBoxAccordParents->currentText() == "Oui" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " sont en accords avec les objectifs qui lui paraissent importants";
        }
        else if(ui->comboBoxAccordParents->currentText() == "Non" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " ne sont pas en accords avec les objectifs qui lui paraissent importants";
        }
        else if(ui->comboBoxAccordParents->currentText() == "Pas tout à fait" ){
            phraseAccordParents = "Les parents de " + Patient::prenomPatient + " ne sont pas totalement en accords avec les objectifs qui lui paraissent importants";
        }

        qDebug() << phraseAccordParents;

        Word::replaceText("i_en_accord",phraseAccordParents);


        QString listObjectfisFinaux;
        for (int i = 0; i < Patient::objectfisFinauxPatients.size(); ++i) {
            listObjectfisFinaux += QString::number(i + 1) + " - " + Patient::objectfisFinauxPatients[i] + "\n";
        }

        Word::replaceText("i_objectifs_finaux",listObjectfisFinaux);



        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");

        // Next interface
        Interface5 *interface5 = new Interface5();
        this->hide();
        interface5->show();
    }
}

