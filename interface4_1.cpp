#include "interface4_1.h"
#include "ui_interface4_1.h"
#include "word.h"
#include "patient.h"
#include "interface4_2.h"

Interface4_1::Interface4_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_1)
{
    ui->setupUi(this);
}

Interface4_1::~Interface4_1()
{
    delete ui;
}


void Interface4_1::on_pushButtonSuivant_clicked()
{
    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();

    // Next interface
    Interface4_2 *interface4_2 = new Interface4_2();
    this->hide();
    interface4_2->show();
}

void Interface4_1::checkRadioButtonAide()
{
    if(ui->radioButtonBalayerAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelBalayer->text() + "\n";
    }

    if(ui->radioButtonCompterArgentAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelCompterArgent->text() + "\n";
    }

    if(ui->radioButtonCuisinerAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelCuisiner->text() + "\n";
    }

    if(ui->radioButtonEnleverPoussiereAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelEnleverPoussiere->text() + "\n";
    }

    if(ui->radioButtonEtendreLingeAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelEtendreLinge->text() + "\n";
    }

    if(ui->radioButtonFaireLessiveAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFaireLessive->text() + "\n";
    }

    if(ui->radioButtonFaireVaiselleAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFaireVaiselle->text() + "\n";
    }

    if(ui->radioButtonFaireLitAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFaireLit->text() + "\n";
    }

    if(ui->radioButtonMettreDebarasserTableAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMettreDebarasserTable->text() + "\n";
    }

    if(ui->radioButtonPasserAspirateurAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelPasserAspirateur->text() + "\n";
    }

    if(ui->radioButtonPlierLingeAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelPlierLinge->text() + "\n";
    }

    if(ui->radioButtonRangerChambreAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelRangerChambre->text() + "\n";
    }

    if(ui->radioButtonRepasserAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelRepasser->text() + "\n";
    }

    if(ui->radioButtonOccuperAnimauxAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelOccuperAnimaux->text() + "\n";
    }

    if(ui->radioButtonSortirPoubelleAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelSortirPoubelle->text() + "\n";
    }

    if(ui->radioButtonUtiliserFourMicroOndeAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelUtiliserFourMicroOnde->text() + "\n";
    }

    if(ui->radioButtonAllerWcAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelAllerWc->text() + "\n";
    }

    if(ui->radioButtonCouperViandeAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelCouperViande->text() + "\n";
    }

    if(ui->radioButtonDormirAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelDormir->text() + "\n";
    }

    if(ui->radioButtonEplucherFruitAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelEplucherFruit->text() + "\n";
    }

    if(ui->radioButtonFaireLacetsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFaireLacets->text() + "\n";
    }

    if(ui->radioButtonFermerManteauAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFermerManteau->text() + "\n";
    }

    if(ui->radioButtonGererHygieneFeminineAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelGererHygieneFeminine->text() + "\n";
    }

    if(ui->radioButtonEpilerAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelEpiler->text() + "\n";
    }

    if(ui->radioButtonMangerBoireAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelMangerBoire->text() + "\n";
    }

    if(ui->radioButtonCoifferAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelCoiffer->text() + "\n";
    }

    if(ui->radioButtonDoucherAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelDoucher->text() + "\n";
    }

    if(ui->radioButtonFaireTartineAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelFaireTartine->text() + "\n";
    }

    if(ui->radioButtonLaverVisageAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelLaverVisage->text() + "\n";
    }

    if(ui->radioButtonLaverMainsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelLaverMains->text() + "\n";
    }

    if(ui->radioButtonBrosserDentsAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelBrosserDents->text() + "\n";
    }

    if(ui->radioButtonViderLaveVaisselleAide->isChecked())
    {
        Patient::aideMaison += "- " + ui->labelViderLaveVaisselle->text() + "\n";
    }
}


void Interface4_1::checkRadioButtonDifficulte()
{
    if(ui->radioButtonBalayerDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelBalayer->text() + "\n";
    }

    if(ui->radioButtonCompterArgentDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelCompterArgent->text() + "\n";
    }

    if(ui->radioButtonCuisinerDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelCuisiner->text() + "\n";
    }

    if(ui->radioButtonEnleverPoussiereDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelEnleverPoussiere->text() + "\n";
    }

    if(ui->radioButtonEtendreLingeDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelEtendreLinge->text() + "\n";
    }

    if(ui->radioButtonFaireLessiveDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFaireLessive->text() + "\n";
    }

    if(ui->radioButtonFaireVaiselleDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFaireVaiselle->text() + "\n";
    }

    if(ui->radioButtonFaireLitDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFaireLit->text() + "\n";
    }

    if(ui->radioButtonMettreDebarasserTableDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMettreDebarasserTable->text() + "\n";
    }

    if(ui->radioButtonPasserAspirateurDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelPasserAspirateur->text() + "\n";
    }

    if(ui->radioButtonPlierLingeDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelPlierLinge->text() + "\n";
    }

    if(ui->radioButtonRangerChambreDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelRangerChambre->text() + "\n";
    }

    if(ui->radioButtonRepasserDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelRepasser->text() + "\n";
    }

    if(ui->radioButtonOccuperAnimauxDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelOccuperAnimaux->text() + "\n";
    }

    if(ui->radioButtonSortirPoubelleDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelSortirPoubelle->text() + "\n";
    }

    if(ui->radioButtonUtiliserFourMicroOndeDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelUtiliserFourMicroOnde->text() + "\n";
    }

    if(ui->radioButtonAllerWcDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelAllerWc->text() + "\n";
    }

    if(ui->radioButtonCouperViandeDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelCouperViande->text() + "\n";
    }

    if(ui->radioButtonDormirDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelDormir->text() + "\n";
    }

    if(ui->radioButtonEplucherFruitDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelEplucherFruit->text() + "\n";
    }

    if(ui->radioButtonFaireLacetsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFaireLacets->text() + "\n";
    }

    if(ui->radioButtonFermerManteauDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFermerManteau->text() + "\n";
    }

    if(ui->radioButtonGererHygieneFeminineDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelGererHygieneFeminine->text() + "\n";
    }

    if(ui->radioButtonEpilerDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelEpiler->text() + "\n";
    }

    if(ui->radioButtonMangerBoireDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelMangerBoire->text() + "\n";
    }

    if(ui->radioButtonCoifferDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelCoiffer->text() + "\n";
    }

    if(ui->radioButtonDoucherDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelDoucher->text() + "\n";
    }

    if(ui->radioButtonFaireTartineDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelFaireTartine->text() + "\n";
    }

    if(ui->radioButtonLaverVisageDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelLaverVisage->text() + "\n";
    }

    if(ui->radioButtonLaverMainsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelLaverMains->text() + "\n";
    }

    if(ui->radioButtonBrosserDentsDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelBrosserDents->text() + "\n";
    }

    if(ui->radioButtonViderLaveVaisselleDifficulte->isChecked())
    {
        Patient::difficulteMaison += "- " + ui->labelViderLaveVaisselle->text() + "\n";
    }
}


void Interface4_1::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonBalayerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelBalayer->text() + "\n";
    }

    if(ui->radioButtonCompterArgentGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelCompterArgent->text() + "\n";
    }

    if(ui->radioButtonCuisinerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelCuisiner->text() + "\n";
    }

    if(ui->radioButtonEnleverPoussiereGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelEnleverPoussiere->text() + "\n";
    }

    if(ui->radioButtonEtendreLingeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelEtendreLinge->text() + "\n";
    }

    if(ui->radioButtonFaireLessiveGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFaireLessive->text() + "\n";
    }

    if(ui->radioButtonFaireVaiselleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFaireVaiselle->text() + "\n";
    }

    if(ui->radioButtonFaireLitGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFaireLit->text() + "\n";
    }

    if(ui->radioButtonMettreDebarasserTableGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMettreDebarasserTable->text() + "\n";
    }

    if(ui->radioButtonPasserAspirateurGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelPasserAspirateur->text() + "\n";
    }

    if(ui->radioButtonPlierLingeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelPlierLinge->text() + "\n";
    }

    if(ui->radioButtonRangerChambreGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelRangerChambre->text() + "\n";
    }

    if(ui->radioButtonRepasserGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelRepasser->text() + "\n";
    }

    if(ui->radioButtonOccuperAnimauxGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelOccuperAnimaux->text() + "\n";
    }

    if(ui->radioButtonSortirPoubelleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelSortirPoubelle->text() + "\n";
    }

    if(ui->radioButtonUtiliserFourMicroOndeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelUtiliserFourMicroOnde->text() + "\n";
    }

    if(ui->radioButtonAllerWcGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelAllerWc->text() + "\n";
    }

    if(ui->radioButtonCouperViandeGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelCouperViande->text() + "\n";
    }

    if(ui->radioButtonDormirGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelDormir->text() + "\n";
    }

    if(ui->radioButtonEplucherFruitGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelEplucherFruit->text() + "\n";
    }

    if(ui->radioButtonFaireLacetsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFaireLacets->text() + "\n";
    }

    if(ui->radioButtonFermerManteauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFermerManteau->text() + "\n";
    }

    if(ui->radioButtonGererHygieneFeminineGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelGererHygieneFeminine->text() + "\n";
    }

    if(ui->radioButtonEpilerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelEpiler->text() + "\n";
    }

    if(ui->radioButtonMangerBoireGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelMangerBoire->text() + "\n";
    }

    if(ui->radioButtonCoifferGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelCoiffer->text() + "\n";
    }

    if(ui->radioButtonDoucherGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelDoucher->text() + "\n";
    }

    if(ui->radioButtonFaireTartineGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelFaireTartine->text() + "\n";
    }

    if(ui->radioButtonLaverVisageGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelLaverVisage->text() + "\n";
    }

    if(ui->radioButtonLaverMainsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelLaverMains->text() + "\n";
    }

    if(ui->radioButtonBrosserDentsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelBrosserDents->text() + "\n";
    }

    if(ui->radioButtonViderLaveVaisselleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteMaison += "- " + ui->labelViderLaveVaisselle->text() + "\n";
    }
}

