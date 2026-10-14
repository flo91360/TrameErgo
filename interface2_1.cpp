#include "interface2_1.h"
#include "ui_interface2_1.h"
#include "questionnaire.h"
#include "word.h"
#include "interface2_2.h"

Interface2_1::Interface2_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface2_1)
{
    ui->setupUi(this);

    ui->comboBoxPersonneDemandeuse->addItems(Questionnaire::liste("demande/personnesDemandeuses"));
    ui->listeMotifs->remplir(Questionnaire::liste("demande/motifs"));
    ui->listeTroubles->remplir(Questionnaire::liste("demande/troubles"), 3);
    ui->comboBoxDossierMDPH->addItems(Questionnaire::liste("demande/dossierMdph"));
}

Interface2_1::~Interface2_1()
{
    delete ui;
}

void Interface2_1::on_pushButtonSuivant_clicked()
{
    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        Word::replaceText("{personne_demandeuse}",ui->comboBoxPersonneDemandeuse->currentText());
        Word::replaceText("{motifs}",ui->listeMotifs->cochees(ui->lineEditAutreMotif->text()).join(", "));
        Word::replaceText("{troubles}",Word::enListe(ui->listeTroubles->cochees(ui->lineEditAutreTrouble->text())));
        Word::replaceText("{dossier_mdph}",ui->comboBoxDossierMDPH->currentText());

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface2_2 *interface2_2 = new Interface2_2();
    this->hide();
    interface2_2->show();
}
