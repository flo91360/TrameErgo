#include "interface4_2.h"
#include "ui_interface4_2.h"
#include "patient.h"
#include "interface4_3.h"

Interface4_2::Interface4_2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_2)
{
    ui->setupUi(this);
}

Interface4_2::~Interface4_2()
{
    delete ui;
}

void Interface4_2::on_pushButtonSuivant_clicked()
{
    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();

    qDebug() << Patient::aideMaison;
    qDebug() << Patient::difficulteMaison;
    qDebug() << Patient::grandeDifficulteMaison;

    // Next interface
    Interface4_3 *interface4_3 = new Interface4_3();
    this->hide();
    interface4_3->show();
}

void Interface4_2::checkRadioButtonAide()
{
    if(ui->radioButtonMoucherAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMoucher->text() + "\n";
    }

    if(ui->radioButtonRaserAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelRaser->text() + "\n";
    }

    if(ui->radioButtonReveillerSeulAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelReveillerSeul->text() + "\n";
    }

    if(ui->radioButtonMettreBijouxAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreBijoux->text() + "\n";
    }

    if(ui->radioButtonMettreBoutonsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreBoutons->text() + "\n";
    }

    if(ui->radioButtonMettreChaussuresAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreChaussures->text() + "\n";
    }

    if(ui->radioButtonMettreEnleverVetementsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreEnleverVetements->text() + "\n";
    }

    if(ui->radioButtonServirVerreEauAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelServirVerreEau->text() + "\n";
    }

    if(ui->radioButtonMaquillerAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMaquiller->text() + "\n";
    }

    if(ui->radioButtonDeplacerSkateRollerAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelDeplacerSkateRoller->text() + "\n";
    }

    if(ui->radioButtonDeplacerTrotinetteAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelDeplacerTrotinette->text() + "\n";
    }

    if(ui->radioButtonDeplacerVeloAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelDeplacerVelo->text() + "\n";
    }

    if(ui->radioButtonUtiliserTransportsCommunAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelUtiliserTransportsCommun->text() + "\n";
    }

    if(ui->radioButtonAppelerParentsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelAppelerParents->text() + "\n";
    }

    if(ui->radioButtonAppelerSecoursAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelAppelerSecours->text() + "\n";
    }

    if(ui->radioButtonAttacherCeintureAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelAttacherCeinture->text() + "\n";
    }

    if(ui->radioButtonMettreProtectionsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreProtections->text() + "\n";
    }

    if(ui->radioButtonMettreCasqueAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreCasque->text() + "\n";
    }

    if(ui->radioButtonTraverserRueAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelTraverserRue->text() + "\n";
    }

    if(ui->radioButtonUtiliserCleAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelUtiliserCle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCadenaAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelUtiliserCadena->text() + "\n";
    }
}

void Interface4_2::checkRadioButtonDifficulte()
{
    if(ui->radioButtonMoucherDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMoucher->text() + "\n";
    }

    if(ui->radioButtonRaserDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelRaser->text() + "\n";
    }

    if(ui->radioButtonReveillerSeulDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelReveillerSeul->text() + "\n";
    }

    if(ui->radioButtonMettreBijouxDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreBijoux->text() + "\n";
    }

    if(ui->radioButtonMettreBoutonsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreBoutons->text() + "\n";
    }

    if(ui->radioButtonMettreChaussuresDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreChaussures->text() + "\n";
    }

    if(ui->radioButtonMettreEnleverVetementsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreEnleverVetements->text() + "\n";
    }

    if(ui->radioButtonServirVerreEauDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelServirVerreEau->text() + "\n";
    }

    if(ui->radioButtonMaquillerDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMaquiller->text() + "\n";
    }

    if(ui->radioButtonDeplacerSkateRollerDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelDeplacerSkateRoller->text() + "\n";
    }

    if(ui->radioButtonDeplacerTrotinetteDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelDeplacerTrotinette->text() + "\n";
    }

    if(ui->radioButtonDeplacerVeloDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelDeplacerVelo->text() + "\n";
    }

    if(ui->radioButtonUtiliserTransportsCommunDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelUtiliserTransportsCommun->text() + "\n";
    }

    if(ui->radioButtonAppelerParentsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelAppelerParents->text() + "\n";
    }

    if(ui->radioButtonAppelerSecoursDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelAppelerSecours->text() + "\n";
    }

    if(ui->radioButtonAttacherCeintureDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelAttacherCeinture->text() + "\n";
    }

    if(ui->radioButtonMettreProtectionsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreProtections->text() + "\n";
    }

    if(ui->radioButtonMettreCasqueDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreCasque->text() + "\n";
    }

    if(ui->radioButtonTraverserRueDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelTraverserRue->text() + "\n";
    }

    if(ui->radioButtonUtiliserCleDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelUtiliserCle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCadenaDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelUtiliserCadena->text() + "\n";
    }
}

void Interface4_2::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonMoucherGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMoucher->text() + "\n";
    }

    if(ui->radioButtonRaserGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelRaser->text() + "\n";
    }

    if(ui->radioButtonReveillerSeulGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelReveillerSeul->text() + "\n";
    }

    if(ui->radioButtonMettreBijouxGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreBijoux->text() + "\n";
    }

    if(ui->radioButtonMettreBoutonsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreBoutons->text() + "\n";
    }

    if(ui->radioButtonMettreChaussuresGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreChaussures->text() + "\n";
    }

    if(ui->radioButtonMettreEnleverVetementsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreEnleverVetements->text() + "\n";
    }

    if(ui->radioButtonServirVerreEauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelServirVerreEau->text() + "\n";
    }

    if(ui->radioButtonMaquillerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMaquiller->text() + "\n";
    }

    if(ui->radioButtonDeplacerSkateRollerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelDeplacerSkateRoller->text() + "\n";
    }

    if(ui->radioButtonDeplacerTrotinetteGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelDeplacerTrotinette->text() + "\n";
    }

    if(ui->radioButtonDeplacerVeloGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelDeplacerVelo->text() + "\n";
    }

    if(ui->radioButtonUtiliserTransportsCommunGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelUtiliserTransportsCommun->text() + "\n";
    }

    if(ui->radioButtonAppelerParentsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelAppelerParents->text() + "\n";
    }

    if(ui->radioButtonAppelerSecoursGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelAppelerSecours->text() + "\n";
    }

    if(ui->radioButtonAttacherCeintureGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelAttacherCeinture->text() + "\n";
    }

    if(ui->radioButtonMettreProtectionsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreProtections->text() + "\n";
    }

    if(ui->radioButtonMettreCasqueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreCasque->text() + "\n";
    }

    if(ui->radioButtonTraverserRueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelTraverserRue->text() + "\n";
    }

    if(ui->radioButtonUtiliserCleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelUtiliserCle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCadenaGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelUtiliserCadena->text() + "\n";
    }
}

