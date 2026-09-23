#include "interface4_5.h"
#include "ui_interface4_5.h"
#include "patient.h"
#include "interface4_6.h"

Interface4_5::Interface4_5(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_5)
{
    ui->setupUi(this);
}

Interface4_5::~Interface4_5()
{
    delete ui;
}

void Interface4_5::on_pushButtonSuivant_clicked()
{
    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();

    // Next interface
    Interface4_6 *interface4_6 = new Interface4_6();
    this->hide();
    interface4_6->show();
}

void Interface4_5::checkRadioButtonAide()
{
    if(ui->radioButtonCourirAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelCourir->text() + "\n";
    }

    if(ui->radioButtonFaireGymDanseAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireGymDanse->text() + "\n";
    }

    if(ui->radioButtonFaireBadmintonTennisAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireBadmintonTennis->text() + "\n";
    }

    if(ui->radioButtonFaireBasketAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireBasket->text() + "\n";
    }

    if(ui->radioButtonFaireFootAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireFoot->text() + "\n";
    }

    if(ui->radioButtonFaireHandballAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireHandball->text() + "\n";
    }

    if(ui->radioButtonFaireJudoKarateAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireJudoKarate->text() + "\n";
    }

    if(ui->radioButtonFairePatinGlaceAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFairePatinGlace->text() + "\n";
    }

    if(ui->radioButtonFaireRugbyAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireRugby->text() + "\n";
    }

    if(ui->radioButtonFaireSkiAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireSki->text() + "\n";
    }

    if(ui->radioButtonFaireVolleyAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireVolley->text() + "\n";
    }

    if(ui->radioButtonNagerAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelNager->text() + "\n";
    }

    if(ui->radioButtonBricolerAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelBricoler->text() + "\n";
    }

    if(ui->radioButtonEcouterMusiqueAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelEcouterMusique->text() + "\n";
    }

    if(ui->radioButtonEcrireHistoiresAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelEcrireHistoires->text() + "\n";
    }

    if(ui->radioButtonFaireArtsPlastiquesAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireArtsPlastiques->text() + "\n";
    }

    if(ui->radioButtonFaireCollectionsAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireCollections->text() + "\n";
    }

    if(ui->radioButtonFaireJeuxConstructionAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelFaireJeuxConstruction->text() + "\n";
    }

    if(ui->radioButtonJouerFlechettesAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerFlechettes->text() + "\n";
    }

    if(ui->radioButtonJouerJeuxVideosAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerJeuxVideos->text() + "\n";
    }

    if(ui->radioButtonJouerAvecAmisAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerAvecAmis->text() + "\n";
    }

    if(ui->radioButtonJouerInstrumentMusiqueAide->isChecked())
    {
        Patient::aideLoisirs += "- " + ui->labelJouerInstrumentMusique->text() + "\n";
    }
}

void Interface4_5::checkRadioButtonDifficulte()
{
    if(ui->radioButtonCourirDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelCourir->text() + "\n";
    }

    if(ui->radioButtonFaireGymDanseDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireGymDanse->text() + "\n";
    }

    if(ui->radioButtonFaireBadmintonTennisDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireBadmintonTennis->text() + "\n";
    }

    if(ui->radioButtonFaireBasketDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireBasket->text() + "\n";
    }

    if(ui->radioButtonFaireFootDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireFoot->text() + "\n";
    }

    if(ui->radioButtonFaireHandballDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireHandball->text() + "\n";
    }

    if(ui->radioButtonFaireJudoKarateDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireJudoKarate->text() + "\n";
    }

    if(ui->radioButtonFairePatinGlaceDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFairePatinGlace->text() + "\n";
    }

    if(ui->radioButtonFaireRugbyDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireRugby->text() + "\n";
    }

    if(ui->radioButtonFaireSkiDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireSki->text() + "\n";
    }

    if(ui->radioButtonFaireVolleyDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireVolley->text() + "\n";
    }

    if(ui->radioButtonNagerDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelNager->text() + "\n";
    }

    if(ui->radioButtonBricolerDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelBricoler->text() + "\n";
    }

    if(ui->radioButtonEcouterMusiqueDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelEcouterMusique->text() + "\n";
    }

    if(ui->radioButtonEcrireHistoiresDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelEcrireHistoires->text() + "\n";
    }

    if(ui->radioButtonFaireArtsPlastiquesDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireArtsPlastiques->text() + "\n";
    }

    if(ui->radioButtonFaireCollectionsDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireCollections->text() + "\n";
    }

    if(ui->radioButtonFaireJeuxConstructionDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelFaireJeuxConstruction->text() + "\n";
    }

    if(ui->radioButtonJouerFlechettesDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerFlechettes->text() + "\n";
    }

    if(ui->radioButtonJouerJeuxVideosDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerJeuxVideos->text() + "\n";
    }

    if(ui->radioButtonJouerAvecAmisDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerAvecAmis->text() + "\n";
    }

    if(ui->radioButtonJouerInstrumentMusiqueDifficulte->isChecked())
    {
        Patient::difficulteLoisirs += "- " + ui->labelJouerInstrumentMusique->text() + "\n";
    }
}

void Interface4_5::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonCourirGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelCourir->text() + "\n";
    }

    if(ui->radioButtonFaireGymDanseGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireGymDanse->text() + "\n";
    }

    if(ui->radioButtonFaireBadmintonTennisGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireBadmintonTennis->text() + "\n";
    }

    if(ui->radioButtonFaireBasketGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireBasket->text() + "\n";
    }

    if(ui->radioButtonFaireFootGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireFoot->text() + "\n";
    }

    if(ui->radioButtonFaireHandballGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireHandball->text() + "\n";
    }

    if(ui->radioButtonFaireJudoKarateGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireJudoKarate->text() + "\n";
    }

    if(ui->radioButtonFairePatinGlaceGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFairePatinGlace->text() + "\n";
    }

    if(ui->radioButtonFaireRugbyGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireRugby->text() + "\n";
    }

    if(ui->radioButtonFaireSkiGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireSki->text() + "\n";
    }

    if(ui->radioButtonFaireVolleyGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireVolley->text() + "\n";
    }

    if(ui->radioButtonNagerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelNager->text() + "\n";
    }

    if(ui->radioButtonBricolerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelBricoler->text() + "\n";
    }

    if(ui->radioButtonEcouterMusiqueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelEcouterMusique->text() + "\n";
    }

    if(ui->radioButtonEcrireHistoiresGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelEcrireHistoires->text() + "\n";
    }

    if(ui->radioButtonFaireArtsPlastiquesGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireArtsPlastiques->text() + "\n";
    }

    if(ui->radioButtonFaireCollectionsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireCollections->text() + "\n";
    }

    if(ui->radioButtonFaireJeuxConstructionGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelFaireJeuxConstruction->text() + "\n";
    }

    if(ui->radioButtonJouerFlechettesGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerFlechettes->text() + "\n";
    }

    if(ui->radioButtonJouerJeuxVideosGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerJeuxVideos->text() + "\n";
    }

    if(ui->radioButtonJouerAvecAmisGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerAvecAmis->text() + "\n";
    }

    if(ui->radioButtonJouerInstrumentMusiqueGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteLoisirs += "- " + ui->labelJouerInstrumentMusique->text() + "\n";
    }
}

