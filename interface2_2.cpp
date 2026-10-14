#include "interface2_2.h"
#include "ui_interface2_2.h"
#include "questionnaire.h"
#include "word.h"
#include "interface3.h"

Interface2_2::Interface2_2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface2_2)
{
    ui->setupUi(this);

    ui->listeProfessionnels->remplir(Questionnaire::liste("suivis/professionnels"), 3);
    connect(ui->listeProfessionnels, &ListeCases::caseModifiee, this, &Interface2_2::suiviModifie);
}

Interface2_2::~Interface2_2()
{
    delete ui;
}

void Interface2_2::suiviModifie(const QString &professionnel, bool suivi)
{
    if (suivi) {
        auto *frequence = new QComboBox();
        frequence->addItems(Questionnaire::liste("suivis/frequences"));
        ui->formLayoutSuivi->addRow(professionnel + " :", frequence);
        frequences.insert(professionnel, frequence);
    } else if (QComboBox *frequence = frequences.take(professionnel)) {
        ui->formLayoutSuivi->removeRow(frequence);
    }
}

void Interface2_2::on_checkBoxAucun_toggled(bool checked)
{
    // « Aucun » exclut les autres professionnels.
    ui->listeProfessionnels->setEnabled(!checked);
    ui->groupBoxSuivi->setEnabled(!checked);
}

void Interface2_2::on_pushButtonSuivant_clicked()
{
    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        QStringList professionnels;
        if (ui->checkBoxAucun->isChecked()) {
            professionnels << "aucun";
        } else {
            for (const QString &professionnel : ui->listeProfessionnels->cochees())
                professionnels << professionnel + " : " + frequences.value(professionnel)->currentText();
        }
        Word::replaceText("{professionnels}",Word::enListe(professionnels));

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface3 *interface3 = new Interface3();
    this->hide();
    interface3->show();
}
