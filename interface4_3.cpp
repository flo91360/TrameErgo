#include "interface4_3.h"
#include "ui_interface4_3.h"
#include "patient.h"
#include "interface4_4.h"

Interface4_3::Interface4_3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_3)
{
    ui->setupUi(this);
}

Interface4_3::~Interface4_3()
{
    delete ui;
}




void Interface4_3::on_pushButtonSuivant_clicked()
{
    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();

    // Next interface
    Interface4_4 *interface4_4 = new Interface4_4();
    this->hide();
    interface4_4->show();
}

void Interface4_3::checkRadioButtonAide()
{
    if(ui->radioButtonDebarasserPlateauAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelDebarasserPlateau->text() + "\n";
    }

    if(ui->radioButtonEcrireTableauAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireTableau->text() + "\n";
    }

    if(ui->radioButtonEtreDelegueAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEtreDelegue->text() + "\n";
    }

    if(ui->radioButtonFaireSportAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelFaireSport->text() + "\n";
    }

    if(ui->radioButtonJouerRecreationAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelJouerRecreation->text() + "\n";
    }

    if(ui->radioButtonLireHeureAiguillesAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelLireHeureAiguilles->text() + "\n";
    }

    if(ui->radioButtonChangerSportAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelChangerSport->text() + "\n";
    }

    if(ui->radioButtonRepererEcoleAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelRepererEcole->text() + "\n";
    }

    if(ui->radioButtonInstallerConfortablementClasseAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelInstallerConfortablementClasse->text() + "\n";
    }

    if(ui->radioButtonRangerClasseurAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelRangerClasseur->text() + "\n";
    }

    if(ui->radioButtonRetrouverAffairesCasierAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelRetrouverAffairesCasier->text() + "\n";
    }

    if(ui->radioButtonTenirPlateauCantineAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTenirPlateauCantine->text() + "\n";
    }

    if(ui->radioButtonDessinerFeuilleAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelDessinerFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireBonEndroitFeuilleAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireBonEndroitFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireSuivantLigneAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireSuivantLigne->text() + "\n";
    }

    if(ui->radioButtonEcrireLisiblementAutresAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireLisiblementAutres->text() + "\n";
    }

    if(ui->radioButtonEcrireLeconSansFatigueAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireLeconSansFatigue->text() + "\n";
    }

    if(ui->radioButtonFormerLettresCorrectementAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelFormerLettresCorrectement->text() + "\n";
    }

    if(ui->radioButtonMeRelireAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelMeRelire->text() + "\n";
    }

    if(ui->radioButtonCollerFeuilleCahierAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelCollerFeuilleCahier->text() + "\n";
    }

    if(ui->radioButtonDecouperAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelDecouper->text() + "\n";
    }
}

void Interface4_3::checkRadioButtonDifficulte()
{
    if(ui->radioButtonDebarasserPlateauDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelDebarasserPlateau->text() + "\n";
    }

    if(ui->radioButtonEcrireTableauDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireTableau->text() + "\n";
    }

    if(ui->radioButtonEtreDelegueDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEtreDelegue->text() + "\n";
    }

    if(ui->radioButtonFaireSportDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelFaireSport->text() + "\n";
    }

    if(ui->radioButtonJouerRecreationDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelJouerRecreation->text() + "\n";
    }

    if(ui->radioButtonLireHeureAiguillesDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelLireHeureAiguilles->text() + "\n";
    }

    if(ui->radioButtonChangerSportDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelChangerSport->text() + "\n";
    }

    if(ui->radioButtonRepererEcoleDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelRepererEcole->text() + "\n";
    }

    if(ui->radioButtonInstallerConfortablementClasseDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelInstallerConfortablementClasse->text() + "\n";
    }

    if(ui->radioButtonRangerClasseurDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelRangerClasseur->text() + "\n";
    }

    if(ui->radioButtonRetrouverAffairesCasierDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelRetrouverAffairesCasier->text() + "\n";
    }

    if(ui->radioButtonTenirPlateauCantineDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTenirPlateauCantine->text() + "\n";
    }

    if(ui->radioButtonDessinerFeuilleDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelDessinerFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireBonEndroitFeuilleDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireBonEndroitFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireSuivantLigneDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireSuivantLigne->text() + "\n";
    }

    if(ui->radioButtonEcrireLisiblementAutresDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireLisiblementAutres->text() + "\n";
    }

    if(ui->radioButtonEcrireLeconSansFatigueDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireLeconSansFatigue->text() + "\n";
    }

    if(ui->radioButtonFormerLettresCorrectementDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelFormerLettresCorrectement->text() + "\n";
    }

    if(ui->radioButtonMeRelireDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelMeRelire->text() + "\n";
    }

    if(ui->radioButtonCollerFeuilleCahierDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelCollerFeuilleCahier->text() + "\n";
    }

    if(ui->radioButtonDecouperDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelDecouper->text() + "\n";
    }
}

void Interface4_3::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonDebarasserPlateauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelDebarasserPlateau->text() + "\n";
    }

    if(ui->radioButtonEcrireTableauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireTableau->text() + "\n";
    }

    if(ui->radioButtonEtreDelegueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEtreDelegue->text() + "\n";
    }

    if(ui->radioButtonFaireSportGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelFaireSport->text() + "\n";
    }

    if(ui->radioButtonJouerRecreationGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelJouerRecreation->text() + "\n";
    }

    if(ui->radioButtonLireHeureAiguillesGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelLireHeureAiguilles->text() + "\n";
    }

    if(ui->radioButtonChangerSportGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelChangerSport->text() + "\n";
    }

    if(ui->radioButtonRepererEcoleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelRepererEcole->text() + "\n";
    }

    if(ui->radioButtonInstallerConfortablementClasseGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelInstallerConfortablementClasse->text() + "\n";
    }

    if(ui->radioButtonRangerClasseurGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelRangerClasseur->text() + "\n";
    }

    if(ui->radioButtonRetrouverAffairesCasierGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelRetrouverAffairesCasier->text() + "\n";
    }

    if(ui->radioButtonTenirPlateauCantineGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTenirPlateauCantine->text() + "\n";
    }

    if(ui->radioButtonDessinerFeuilleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelDessinerFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireBonEndroitFeuilleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireBonEndroitFeuille->text() + "\n";
    }

    if(ui->radioButtonEcrireSuivantLigneGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireSuivantLigne->text() + "\n";
    }

    if(ui->radioButtonEcrireLisiblementAutresGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireLisiblementAutres->text() + "\n";
    }

    if(ui->radioButtonEcrireLeconSansFatigueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireLeconSansFatigue->text() + "\n";
    }

    if(ui->radioButtonFormerLettresCorrectementGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelFormerLettresCorrectement->text() + "\n";
    }

    if(ui->radioButtonMeRelireGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelMeRelire->text() + "\n";
    }

    if(ui->radioButtonCollerFeuilleCahierGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelCollerFeuilleCahier->text() + "\n";
    }

    if(ui->radioButtonDecouperGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelDecouper->text() + "\n";
    }
}

