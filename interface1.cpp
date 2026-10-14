#include "interface1.h"
#include "ui_interface1.h"
#include "interface2_1.h"
#include "word.h"
#include "patient.h"
#include "questionnaire.h"

Interface1::Interface1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface1)
{
    ui->setupUi(this);

    ui->comboBoxClasse->addItems(Questionnaire::liste("identite/classes"));
    ui->comboBoxTypeEtablissement->addItems(Questionnaire::liste("identite/typesEtablissement"));
    // Le bilan accorde la latéralité : « {prenom} est {lateralite} ».
    ui->comboBoxLateralite->addItems(Questionnaire::liste("identite/lateralite/" + Patient::sexePatient));
    ui->comboBoxModeGarde->addItems(Questionnaire::liste("identite/modesDeGarde"));
    ui->comboBoxEntente->addItems(Questionnaire::liste("identite/entente"));

    Word::wordApp = new QAxObject("Word.Application");
    if (Word::wordApp && !Word::wordApp->isNull()) {
        Word::documents = Word::wordApp->querySubObject("Documents");
    }
}

Interface1::~Interface1()
{
    delete ui;
}


void Interface1::on_pushButtonSuivant_clicked()
{
    // Configurer la localisation pour le français
    QLocale frenchLocale(QLocale::French);
    QDate dateDuJour = QDate::currentDate();
    QString moisPassation = frenchLocale.toString(dateDuJour, "MMMM");
    QString anneePassation = dateDuJour.toString("yyyy");

    Word::filePathToSave = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/TrameErgo/Bilan_ergotherapie_" + ui->lineEditNom->text() + "_" + ui->lineEditPrenom->text()  + "_" +  moisPassation + "_" + anneePassation  + ".docx";
    if (!Word::creerBilan(Word::filePathToSave))
        return;

    Patient::prenomPatient = ui->lineEditPrenom->text();

    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        // Mots accordés au sexe du patient, dans tout le bilan.
        Word::replaceText("{il_elle}",Patient::accord("il", "elle"));
        Word::replaceText("{Il_Elle}",Patient::accord("Il", "Elle"));
        Word::replaceText("{ne_e}",Patient::accord("né", "née"));
        Word::replaceText("{seul_e}",Patient::accord("seul", "seule"));

        Word::replaceText("{prenom}",Patient::prenomPatient);
        Word::replaceText("{date_de_naissance}",ui->dateEditNaissance->date().toString("dd-MM-yyyy"));
        Patient::agePatient = Patient::calculerAge(ui->dateEditNaissance->date());
        Word::replaceText("{age}",Patient::agePatient);
        Word::replaceText("{classe}",ui->comboBoxClasse->currentText());
        Word::replaceText("{type_etablissement}",ui->comboBoxTypeEtablissement->currentText());
        Word::replaceText("{nom_etablissement}",ui->lineEditNomEtablissement->text());
        Word::replaceText("{lateralite}",ui->comboBoxLateralite->currentText());
        Word::replaceText("{mode_de_garde}",ui->comboBoxModeGarde->currentText());

        if(ui->checkBoxEnfantUnique->isChecked())
        {
            Word::replaceText("{fratrie}","est enfant unique");
            Word::replaceText("{entente}","");
        }
        else
        {
            const QString entente = Questionnaire::phrase("identite/entente", ui->comboBoxEntente->currentText());
            Word::replaceText("{fratrie}","a " + ui->lineEditFraterie->text());
            Word::replaceText("{entente}","(" + entente + ")");
        }

        Word::replaceText("{medecin_traitant}",ui->lineEditMedecinTraitant->text());
        Word::replaceText("{ville}",ui->lineEditVille->text());

        // Page de garde (zones de texte)
        const QString typeBilan = Patient::typeBilan == "Ado" ? Patient::accord("Adolescent", "Adolescente")
                                                              : "Enfant";
        Word::replaceTextFromZoneText("{type_bilan}",typeBilan);
        Word::replaceTextFromZoneText("{prenom}",ui->lineEditPrenom->text());
        Word::replaceTextFromZoneText("{nom}",ui->lineEditNom->text());
        Word::replaceTextFromZoneText("{date_de_passation}",dateDuJour.toString("dd-MM-yyyy"));
        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface2_1 *interface2_1 = new Interface2_1();
    this->hide();
    interface2_1->show();
}
