#include "interface0.h"
#include "ui_interface0.h"

#include "interface1_old.h"

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
    Patient::sexePatient = ui->comboBoxSexe->currentText();
    Interface1 *interface1 = new Interface1();
    this->hide();
    interface1->show();
}


void Interface0::on_radioButtonEnfant_clicked()
{
    Patient::typeBilan = "enfant";
}


void Interface0::on_radioButtonAdolescent_clicked()
{
    Patient::typeBilan = "adolescent";
}


void Interface0::on_radioButtonAdulte_clicked()
{
    Patient::typeBilan = "adulte";
}

