#include "interface4_4.h"
#include "ui_interface4_4.h"
#include "patient.h"
#include "interface4_5.h"

Interface4_4::Interface4_4(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_4)
{
    ui->setupUi(this);
}

Interface4_4::~Interface4_4()
{
    delete ui;
}

void Interface4_4::on_pushButtonSuivant_clicked()
{

    checkRadioButtonAide();
    checkRadioButtonDifficulte();
    checkRadioButtonGrandeDifficulte();


    qDebug() << Patient::aideEcole;
    qDebug() << Patient::difficulteEcole;
    qDebug() << Patient::grandeDifficulteEcole;

    // Next interface
    Interface4_5 *interface4_5 = new Interface4_5();
    this->hide();
    interface4_5->show();
}

void Interface4_4::checkRadioButtonAide()
{
    if(ui->radioButtonGommerAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelGommer->text() + "\n";
    }

    if(ui->radioButtonSoulignerAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelSouligner->text() + "\n";
    }

    if(ui->radioButtonTaillerCrayonAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTaillerCrayon->text() + "\n";
    }

    if(ui->radioButtonTracerTraitRegleAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTracerTraitRegle->text() + "\n";
    }

    if(ui->radioButtonUtiliserPinceauAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserPinceau->text() + "\n";
    }

    if(ui->radioButtonCompterAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelCompter->text() + "\n";
    }

    if(ui->radioButtonPoserQuestionAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelPoserQuestion->text() + "\n";
    }

    if(ui->radioButtonTracerCarreAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTracerCarre->text() + "\n";
    }

    if(ui->radioButtonTracerRondAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTracerRond->text() + "\n";
    }

    if(ui->radioButtonTracerTriangleAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelTracerTriangle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCompasAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserCompas->text() + "\n";
    }

    if(ui->radioButtonUtiliserEquerreAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserEquerre->text() + "\n";
    }

    if(ui->radioButtonUtiliserRapporteurAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserRapporteur->text() + "\n";
    }

    if(ui->radioButtonUtiliserCalculatriceAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserCalculatrice->text() + "\n";
    }

    if(ui->radioButtonEcrireDevoirsAgendaAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelEcrireDevoirsAgenda->text() + "\n";
    }

    if(ui->radioButtonFaireExercicesAutonomnieAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelFaireExercicesAutonomnie->text() + "\n";
    }

    if(ui->radioButtonOrganiserDevoirsAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelOrganiserDevoirs->text() + "\n";
    }

    if(ui->radioButtonPreparerCartableAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labePreparerCartable->text() + "\n";
    }

    if(ui->radioButtonRelireCoursAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelRelireCours->text() + "\n";
    }

    if(ui->radioButtonSavoirQuoiApprendreAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelSavoirQuoiApprendre->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurMaisonAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserOrdinateurMaison->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurClasseEvaluationAide->isChecked())
    {
        Patient::aideEcole += "- " + ui->labelUtiliserOrdinateurClasseEvaluation->text() + "\n";
    }
}

void Interface4_4::checkRadioButtonDifficulte()
{
    if(ui->radioButtonGommerDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelGommer->text() + "\n";
    }

    if(ui->radioButtonSoulignerDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelSouligner->text() + "\n";
    }

    if(ui->radioButtonTaillerCrayonDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTaillerCrayon->text() + "\n";
    }

    if(ui->radioButtonTracerTraitRegleDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTracerTraitRegle->text() + "\n";
    }

    if(ui->radioButtonUtiliserPinceauDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserPinceau->text() + "\n";
    }

    if(ui->radioButtonCompterDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelCompter->text() + "\n";
    }

    if(ui->radioButtonPoserQuestionDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelPoserQuestion->text() + "\n";
    }

    if(ui->radioButtonTracerCarreDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTracerCarre->text() + "\n";
    }

    if(ui->radioButtonTracerRondDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTracerRond->text() + "\n";
    }

    if(ui->radioButtonTracerTriangleDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelTracerTriangle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCompasDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserCompas->text() + "\n";
    }

    if(ui->radioButtonUtiliserEquerreDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserEquerre->text() + "\n";
    }

    if(ui->radioButtonUtiliserRapporteurDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserRapporteur->text() + "\n";
    }

    if(ui->radioButtonUtiliserCalculatriceDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserCalculatrice->text() + "\n";
    }

    if(ui->radioButtonEcrireDevoirsAgendaDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelEcrireDevoirsAgenda->text() + "\n";
    }

    if(ui->radioButtonFaireExercicesAutonomnieDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelFaireExercicesAutonomnie->text() + "\n";
    }

    if(ui->radioButtonOrganiserDevoirsDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelOrganiserDevoirs->text() + "\n";
    }

    if(ui->radioButtonPreparerCartableDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labePreparerCartable->text() + "\n";
    }

    if(ui->radioButtonRelireCoursDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelRelireCours->text() + "\n";
    }

    if(ui->radioButtonSavoirQuoiApprendreDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelSavoirQuoiApprendre->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurMaisonDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserOrdinateurMaison->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurClasseEvaluationDifficulte->isChecked())
    {
        Patient::difficulteEcole += "- " + ui->labelUtiliserOrdinateurClasseEvaluation->text() + "\n";
    }
}

void Interface4_4::checkRadioButtonGrandeDifficulte()
{
    if(ui->radioButtonGommerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelGommer->text() + "\n";
    }

    if(ui->radioButtonSoulignerGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelSouligner->text() + "\n";
    }

    if(ui->radioButtonTaillerCrayonGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTaillerCrayon->text() + "\n";
    }

    if(ui->radioButtonTracerTraitRegleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTracerTraitRegle->text() + "\n";
    }

    if(ui->radioButtonUtiliserPinceauGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserPinceau->text() + "\n";
    }

    if(ui->radioButtonCompterGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelCompter->text() + "\n";
    }

    if(ui->radioButtonPoserQuestionGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelPoserQuestion->text() + "\n";
    }

    if(ui->radioButtonTracerCarreGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTracerCarre->text() + "\n";
    }

    if(ui->radioButtonTracerRondGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTracerRond->text() + "\n";
    }

    if(ui->radioButtonTracerTriangleGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelTracerTriangle->text() + "\n";
    }

    if(ui->radioButtonUtiliserCompasGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserCompas->text() + "\n";
    }

    if(ui->radioButtonUtiliserEquerreGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserEquerre->text() + "\n";
    }

    if(ui->radioButtonUtiliserRapporteurGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserRapporteur->text() + "\n";
    }

    if(ui->radioButtonUtiliserCalculatriceGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserCalculatrice->text() + "\n";
    }

    if(ui->radioButtonEcrireDevoirsAgendaGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelEcrireDevoirsAgenda->text() + "\n";
    }

    if(ui->radioButtonFaireExercicesAutonomnieGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelFaireExercicesAutonomnie->text() + "\n";
    }

    if(ui->radioButtonOrganiserDevoirsGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelOrganiserDevoirs->text() + "\n";
    }

    if(ui->radioButtonPreparerCartableGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labePreparerCartable->text() + "\n";
    }

    if(ui->radioButtonRelireCoursGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelRelireCours->text() + "\n";
    }

    if(ui->radioButtonSavoirQuoiApprendreGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelSavoirQuoiApprendre->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurMaisonGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserOrdinateurMaison->text() + "\n";
    }

    if(ui->radioButtonUtiliserOrdinateurClasseEvaluationGrandeDifficulte->isChecked())
    {
        Patient::grandeDifficulteEcole += "- " + ui->labelUtiliserOrdinateurClasseEvaluation->text() + "\n";
    }
}

