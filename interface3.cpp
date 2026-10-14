#include "interface3.h"
#include "ui_interface3.h"
#include "questionnaire.h"
#include "word.h"
#include "interface4.h"

Interface3::Interface3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface3)
{
    ui->setupUi(this);

    ui->listeComportement->remplir(Questionnaire::liste("scolarite/comportement"), 2);
    ui->listeDifficultes->remplir(Questionnaire::liste("scolarite/difficultes"), 3);
    ui->listeMatieresPreferees->remplir(Questionnaire::liste("scolarite/matieres"), 4);
    ui->listeMatieresDetestees->remplir(Questionnaire::liste("scolarite/matieres"), 4);
}

Interface3::~Interface3()
{
    delete ui;
}

void Interface3::on_pushButtonSuivant_clicked()
{
    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        Word::replaceText("{comportement_en_classe}",Word::enListe(ui->listeComportement->cochees()));
        Word::replaceText("{difficultes_en_classe}",Word::enListe(ui->listeDifficultes->cochees()));
        Word::replaceText("{matieres_preferees}",
                          ui->listeMatieresPreferees->cochees(ui->lineEditMatierePrefere->text()).join(", "));
        Word::replaceText("{matieres_moins_appreciees}",
                          ui->listeMatieresDetestees->cochees(ui->lineEditMatiereDeteste->text()).join(", "));

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface : OT Hope, premier domaine
    Interface4 *interface4 = new Interface4(0);
    this->hide();
    interface4->show();
}
