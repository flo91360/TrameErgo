#include "interface4_6.h"
#include "ui_interface4_6.h"
#include "patient.h"
#include "word.h"
#include "interface4_7.h"

Interface4_6::Interface4_6(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_6)
{
    ui->setupUi(this);
}

Interface4_6::~Interface4_6()
{
    delete ui;
}

void Interface4_6::on_pushButtonSuivant_clicked()
{
    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();

    qDebug() << Patient::aideLoisirs;
    qDebug() << Patient::difficulteLoisirs;
    qDebug() << Patient::grandeDifficulteLoisirs;


    // Next interface
    Interface4_7 *interface4_7 = new Interface4_7();
    this->hide();
    interface4_7->show();
}

void Interface4_6::checkRadioButtonAide()
{
    if(ui->radioButtonLireHistoiresAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelLireHistoires->text() + "\n";
    }

    if(ui->radioButtonRepondreTelephoneAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelRepondreTelephone->text() + "\n";
    }

    if(ui->radioButtonFaireBalancoireAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireBalancoire->text() + "\n";
    }

    if(ui->radioButtonFaireRollerAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireRoller->text() + "\n";
    }

    if(ui->radioButtonFaireTrampolineAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireTrampoline->text() + "\n";
    }

    if(ui->radioButtonFaireVeloAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireVelo->text() + "\n";
    }

    if(ui->radioButtonGrimperArbresAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelGrimperArbres->text() + "\n";
    }

    if(ui->radioButtonJouerMarelleAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerMarelle->text() + "\n";
    }

    if(ui->radioButtonJouerBallonAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerBallon->text() + "\n";
    }

    if(ui->radioButtonJouerFrisbeeAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerFrisbee->text() + "\n";
    }

    if(ui->radioButtonJouerPaletPetanqueAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerPaletPetanque->text() + "\n";
    }

    if(ui->radioButtonJouerDansEauAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerDansEau->text() + "\n";
    }

    if(ui->radioButtonJouerDansSableAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerDansSable->text() + "\n";
    }

    if(ui->radioButtonJouerDansNeigeAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerDansNeige->text() + "\n";
    }

    if(ui->radioButtonSauterCordeAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelSauterCorde->text() + "\n";
    }

    if(ui->radioButtonRetrouverEntreAmisAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelRetrouverEntreAmis->text() + "\n";
    }
}

void Interface4_6::checkRadioButtonDifficulte()
{
    if(ui->radioButtonLireHistoiresDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelLireHistoires->text() + "\n";
    }

    if(ui->radioButtonRepondreTelephoneDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelRepondreTelephone->text() + "\n";
    }

    if(ui->radioButtonFaireBalancoireDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireBalancoire->text() + "\n";
    }

    if(ui->radioButtonFaireRollerDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireRoller->text() + "\n";
    }

    if(ui->radioButtonFaireTrampolineDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireTrampoline->text() + "\n";
    }

    if(ui->radioButtonFaireVeloDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireVelo->text() + "\n";
    }

    if(ui->radioButtonGrimperArbresDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelGrimperArbres->text() + "\n";
    }

    if(ui->radioButtonJouerMarelleDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerMarelle->text() + "\n";
    }

    if(ui->radioButtonJouerBallonDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerBallon->text() + "\n";
    }

    if(ui->radioButtonJouerFrisbeeDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerFrisbee->text() + "\n";
    }

    if(ui->radioButtonJouerPaletPetanqueDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerPaletPetanque->text() + "\n";
    }

    if(ui->radioButtonJouerDansEauDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerDansEau->text() + "\n";
    }

    if(ui->radioButtonJouerDansSableDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerDansSable->text() + "\n";
    }

    if(ui->radioButtonJouerDansNeigeDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerDansNeige->text() + "\n";
    }

    if(ui->radioButtonSauterCordeDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelSauterCorde->text() + "\n";
    }

    if(ui->radioButtonRetrouverEntreAmisDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelRetrouverEntreAmis->text() + "\n";
    }
}

void Interface4_6::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonLireHistoiresGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelLireHistoires->text() + "\n";
    }

    if(ui->radioButtonRepondreTelephoneGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelRepondreTelephone->text() + "\n";
    }

    if(ui->radioButtonFaireBalancoireGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireBalancoire->text() + "\n";
    }

    if(ui->radioButtonFaireRollerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireRoller->text() + "\n";
    }

    if(ui->radioButtonFaireTrampolineGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireTrampoline->text() + "\n";
    }

    if(ui->radioButtonFaireVeloGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireVelo->text() + "\n";
    }

    if(ui->radioButtonGrimperArbresGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelGrimperArbres->text() + "\n";
    }

    if(ui->radioButtonJouerMarelleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerMarelle->text() + "\n";
    }

    if(ui->radioButtonJouerBallonGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerBallon->text() + "\n";
    }

    if(ui->radioButtonJouerFrisbeeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerFrisbee->text() + "\n";
    }

    if(ui->radioButtonJouerPaletPetanqueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerPaletPetanque->text() + "\n";
    }

    if(ui->radioButtonJouerDansEauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerDansEau->text() + "\n";
    }

    if(ui->radioButtonJouerDansSableGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerDansSable->text() + "\n";
    }

    if(ui->radioButtonJouerDansNeigeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerDansNeige->text() + "\n";
    }

    if(ui->radioButtonSauterCordeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelSauterCorde->text() + "\n";
    }

    if(ui->radioButtonRetrouverEntreAmisGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelRetrouverEntreAmis->text() + "\n";
    }
}

