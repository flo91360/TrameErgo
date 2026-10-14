#include "interface0.h"
#include "ui_interface0.h"

#include "interface1.h"

#include "patient.h"


Interface0::Interface0(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface0)
{
    ui->setupUi(this);
}

Interface0::~Interface0()
{
    delete ui;
}

void Interface0::on_pushButtonSuivant_clicked()
{
    // Lus ici plutôt qu'au clic : le choix coché par défaut n'émet aucun clic.
    // Ils désignent les dossiers des modèles Word (voir Word::modele).
    Patient::sexePatient = ui->comboBoxSexe->currentText();
    Patient::typeBilan = ui->radioButtonAdolescent->isChecked() ? "Ado" : "Enfant";
    Interface1 *interface1 = new Interface1();
    this->hide();
    interface1->show();
}
