#include "interface2_2.h"
#include "ui_interface2_2.h"
#include "word.h"
#include "interface3.h"

Interface2_2::Interface2_2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface2_2)
{
    ui->setupUi(this);
}

Interface2_2::~Interface2_2()
{
    delete ui;
}



void Interface2_2::on_pushButtonSuivant_clicked()
{
    Word::document = Word::documents->querySubObject("Open(const QString&)",  Word::filePathToSave);
    if (!Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        if(ui->checkBoxAucun->checkState() == Qt::Checked)
        {
            professionnels += "- " + ui->checkBoxAucun->text();
        }
        else
        {
            // Parcourez toutes les rangées du FormLayout
            for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {

                if (QLabel *label = qobject_cast<QLabel*>(ui->formLayoutSuivi->itemAt(2*i)->widget())) {
                    professionnels += "- " + label->text();
                }
                qDebug() << professionnels;

                if (QComboBox *comboBox = qobject_cast<QComboBox*>(ui->formLayoutSuivi->itemAt(2*i+1)->widget())) {
                    professionnels += " " + comboBox->currentText() + "\n";

                }
                qDebug() << professionnels;
            }
        }


        Word::replaceText("i_professionnels_suivants_le_patient",professionnels);

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }


    // Next interface
    Interface3 *interface3 = new Interface3();
    this->hide();
    interface3->show();
}


void Interface2_2::on_checkBoxPsychomotricien_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelPsychomotricien = new QLabel("psychomotricien(ne) :");
        comboBoxPsychomotricien = new QComboBox();

        comboBoxPsychomotricien->addItem("à raison d'une fois par semaine");
        comboBoxPsychomotricien->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxPsychomotricien->addItem("à raison d'une fois par mois");
        comboBoxPsychomotricien->addItem("à raison d'une fois par trimestre");
        comboBoxPsychomotricien->addItem("à raison d'une fois tous les 6 mois");
        comboBoxPsychomotricien->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelPsychomotricien, comboBoxPsychomotricien);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelPsychomotricien &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxPsychomotricien) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}


void Interface2_2::on_checkBoxOrthophoniste_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelOrthophoniste = new QLabel("orthophoniste :");
        comboBoxOrthophoniste = new QComboBox();

        comboBoxOrthophoniste->addItem("à raison d'une fois par semaine");
        comboBoxOrthophoniste->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxOrthophoniste->addItem("à raison d'une fois par mois");
        comboBoxOrthophoniste->addItem("à raison d'une fois par trimestre");
        comboBoxOrthophoniste->addItem("à raison d'une fois tous les 6 mois");
        comboBoxOrthophoniste->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelOrthophoniste, comboBoxOrthophoniste);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelOrthophoniste &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxOrthophoniste) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}


void Interface2_2::on_checkBoxPsychologue_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelPsychologue = new QLabel("psychologue :");
        comboBoxPsychologue = new QComboBox();

        comboBoxPsychologue->addItem("à raison d'une fois par semaine");
        comboBoxPsychologue->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxPsychologue->addItem("à raison d'une fois par mois");
        comboBoxPsychologue->addItem("à raison d'une fois par trimestre");
        comboBoxPsychologue->addItem("à raison d'une fois tous les 6 mois");
        comboBoxPsychologue->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelPsychologue, comboBoxPsychologue);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelPsychologue &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxPsychologue) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}


void Interface2_2::on_checkBoxOrthopiste_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelOrthopiste = new QLabel("orthoptiste :");
        comboBoxOrthopiste = new QComboBox();

        comboBoxOrthopiste->addItem("à raison d'une fois par semaine");
        comboBoxOrthopiste->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxOrthopiste->addItem("à raison d'une fois par mois");
        comboBoxOrthopiste->addItem("à raison d'une fois par trimestre");
        comboBoxOrthopiste->addItem("à raison d'une fois tous les 6 mois");
        comboBoxOrthopiste->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelOrthopiste, comboBoxOrthopiste);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelOrthopiste &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxOrthopiste) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}


void Interface2_2::on_checkBoxNeuropsychologue_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelNeuropsychologue = new QLabel("neuropsychologue :");
        comboBoxNeuropsychologue = new QComboBox();

        comboBoxNeuropsychologue->addItem("à raison d'une fois par semaine");
        comboBoxNeuropsychologue->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxNeuropsychologue->addItem("à raison d'une fois par mois");
        comboBoxNeuropsychologue->addItem("à raison d'une fois par trimestre");
        comboBoxNeuropsychologue->addItem("à raison d'une fois tous les 6 mois");
        comboBoxNeuropsychologue->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelNeuropsychologue, comboBoxNeuropsychologue);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelNeuropsychologue &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxNeuropsychologue) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}





void Interface2_2::on_checkBoxKinesiterapeute_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        // Créez un QLabel et une QComboBox
        labelKinesiterapeute = new QLabel("kinésithérapeute :");
        comboBoxKinesiterapeute = new QComboBox();

        comboBoxKinesiterapeute->addItem("à raison d'une fois par semaine");
        comboBoxKinesiterapeute->addItem("à raison d'une fois toutes les deux semaines");
        comboBoxKinesiterapeute->addItem("à raison d'une fois par mois");
        comboBoxKinesiterapeute->addItem("à raison d'une fois par trimestre");
        comboBoxKinesiterapeute->addItem("à raison d'une fois tous les 6 mois");
        comboBoxKinesiterapeute->addItem("à raison d'une fois par an");

        // Ajoutez le QLabel et la QComboBox au QFormLayout
        ui->formLayoutSuivi->addRow(labelKinesiterapeute, comboBoxKinesiterapeute);
    }
    else if (arg1 == Qt::Unchecked)
    {
        // Parcourez toutes les rangées du FormLayout
        for (int i = 0; i < ui->formLayoutSuivi->rowCount(); i++) {
            // Vérifiez si la rangée contient le label et le comboBox à supprimer
            if (ui->formLayoutSuivi->itemAt(2*i)->widget() == labelKinesiterapeute &&
                ui->formLayoutSuivi->itemAt(2*i + 1)->widget() == comboBoxKinesiterapeute) {
                // Supprimez la rangée contenant le label et le comboBox
                ui->formLayoutSuivi->removeRow(i);
                break; // Arrêtez la boucle une fois que la rangée est supprimée
            }
        }
    }
}


