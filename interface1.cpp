#include "interface1.h"
#include "ui_interface1.h"
#include "interface2_1.h"
#include "word.h"
#include "patient.h"

Interface1::Interface1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface1)
{
    ui->setupUi(this);

    // QFile logFile("C:/Users/flori/OneDrive/Documents/TrameERGO_test/log.txt");
    // logFile.open(QIODevice::Append | QIODevice::Text);
    // QTextStream out(&logFile);
    // out << "Trying to access folder: ALED\n";


    this->sexe = Patient::sexePatient;
    this->typeBilan = Patient::typeBilan;

    qDebug() << sexe;
    qDebug() << typeBilan;

    Word::wordApp = new QAxObject("Word.Application");
    if (!Word::wordApp->isNull()) {
        Word::documents = Word::wordApp->querySubObject("Documents");
    }
}

Interface1::~Interface1()
{
    delete ui;
}


void Interface1::on_pushButtonSuivant_clicked()
{
    QString moisPassation;
    QString anneePassation;
    QString age;
    QDate dateDuJour;
    QString fileName;

    // QFile logFile("C:/Users/flori/OneDrive/Documents/TrameERGO_test/log.txt");
    // logFile.open(QIODevice::Append | QIODevice::Text);
    // QTextStream out(&logFile);
    // out << "Trying to access folder: plop\n";



    // Configurer la localisation pour le français
    QLocale frenchLocale(QLocale::French);
    fileName = "Bilan_ergotherapie";
    dateDuJour = QDateTime::currentDateTime().date();
    moisPassation = frenchLocale.toString(dateDuJour, "MMMM");
    anneePassation  = dateDuJour.toString("yyyy");


    Word::pathToArbo = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    qDebug() << "Word::pathToArbo";
    qDebug() << Word::pathToArbo;
    // out << Word::pathToArbo +"\n";


    Word::filePathToSave = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TrameErgo/" + fileName + "_" + ui->lineEditNom->text() + "_" + ui->lineEditPrenom->text()  + "_" +  moisPassation + "_" + anneePassation  + ".docx";
    qDebug() <<  Word::filePathToSave;
    qDebug() << QDir::currentPath();
    // out << Word::filePathToSave  +"\n";
    Word::copieCree(Word::pathToArbo + "/arborescence/Femme/Enfant/Interface1/interface1.docx", Word::filePathToSave);

    qDebug() << "filePathToSave";

    Patient::prenomPatient = ui->lineEditPrenom->text();

    Word::document = Word::documents->querySubObject("Open(const QString&)",  Word::filePathToSave);
    if (!Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        Word::replaceText("i_prenom",Patient::prenomPatient);
        Word::replaceText("i_date_de_naissance",ui->dateEditNaissance->date().toString("dd-MM-yyyy"));
        Patient::agePatient = Patient::calculerAge(ui->dateEditNaissance->date());
        Word::replaceText("i_age",Patient::agePatient);
        Word::replaceText("i_classe",ui->comboBoxClasse->currentText());
        Word::replaceText("i_type_etablissement",ui->comboBoxTypeEtablissement->currentText());
        Word::replaceText("i_nom_etablissement",ui->lineEditNomEtablissement->text());
        Word::replaceText("i_lateralite",ui->comboBoxLateralite->currentText());
        Word::replaceText("i_mode_de_garde",ui->comboBoxModeGarde->currentText());


        if(ui->radioButtonEnfantUnique->isChecked())
        {
            Word::replaceText("i_fraterie","est enfant unique");
            Word::replaceText("i_entente","");
            qDebug() << "C'est coché";
        }
        else
        {
            Word::replaceText("i_fraterie","a " + ui->lineEditFraterie->text());
            Word::replaceText("i_entente","(" + entente + ")");
            qDebug() << "C'est aps coché";
        }


        Word::replaceText("i_medecin_traitant",ui->lineEditMedecinTraitant->text());
        Word::replaceText("i_ville",ui->lineEditVille->text());
        Word::replaceTextFromZoneText("i_prenom",ui->lineEditPrenom->text());
        Word::replaceTextFromZoneText("i_nom",ui->lineEditNom->text());
        Word::replaceTextFromZoneText("i_date_de_passation",dateDuJour.toString("dd-MM-yyyy"));
        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface2_1 *interface2_1 = new Interface2_1();
    this->hide();
    interface2_1->show();
}


void Interface1::on_radioButtonBonneEntente_clicked()
{
    entente = "bonne entente entre eux";
}


void Interface1::on_radioButtonMauvaiseEntenre_clicked()
{
    entente = "mauvaise entente entre eux";
}


void Interface1::on_radioButtonNeutreEntente_clicked()
{
    entente = "pas de relation particulière entre eux";
}



