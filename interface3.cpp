#include "interface3.h"
#include "ui_interface3.h"
#include "word.h"
#include "interface4_1.h"

Interface3::Interface3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface3)
{
    ui->setupUi(this);
}

Interface3::~Interface3()
{
    delete ui;
}


void Interface3::on_pushButtonSuivant_clicked()
{
    Word::copieColle(Word::modele("interface3"), Word::filePathToSave);

    qDebug() << "filePathToSave";

    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");


        Word::replaceText("i_comportement_en_classe",comportementClasse);
        Word::replaceText("i_difficulte_en_classe",difficultesClasse);

        if(ui->lineEditMatierePrefere->text() == "")
        {
            if (matieresPreferees.size() >= 2) {
                // Utilisez la méthode erase() pour enlever les deux derniers caractères
                matieresPreferees.remove(matieresPreferees.size() - 2, 2);
            } else {
                // Gérez le cas où la chaîne a moins de deux caractères
                qDebug() << "La chaîne est trop courte pour enlever les deux derniers caractères.";
            }
        }
        else
        {
            matieresPreferees += ui->lineEditMatierePrefere->text();
        }

        qDebug() << matieresPreferees;

        Word::replaceText("i_matieres_preferees",matieresPreferees);

        if(ui->lineEditMatiereDeteste->text() == "")
        {
            if (matieresDetestees.size() >= 2) {
                // Utilisez la méthode erase() pour enlever les deux derniers caractères
                matieresDetestees.remove(matieresDetestees.size() - 2, 2);
            } else {
                // Gérez le cas où la chaîne a moins de deux caractères
                qDebug() << "La chaîne est trop courte pour enlever les deux derniers caractères.";
            }
        }
        else
        {
            matieresDetestees += ui->lineEditMatiereDeteste->text();
        }

        qDebug() << matieresDetestees;

        Word::replaceText("i_matieres_les_moins_appreciees",matieresDetestees);

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface4_1 *interface4_1 = new Interface4_1();
    this->hide();
    interface4_1->show();
}


/************************* Comportement en classe ***********************/

void Interface3::on_checkBoxCCDifficultesConcentrer_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxCCDifficultesConcentrer->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxCCDifficultesConcentrer->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxBavardage_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxBavardage->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxBavardage->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxParticipeBien_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxParticipeBien->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxParticipeBien->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxParticipePas_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxParticipePas->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxParticipePas->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxConcentreBien_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxConcentreBien->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxConcentreBien->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxTravailNonAutonome_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxTravailNonAutonome->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxTravailNonAutonome->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxConcentrationFluctuente_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxConcentrationFluctuente->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxConcentrationFluctuente->text() + "\n","");
        qDebug() << comportementClasse;
    }
}


void Interface3::on_checkBoxParticipeSelonMatiere_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        comportementClasse += "- " + ui->checkBoxParticipeSelonMatiere->text() + "\n";
        qDebug() << comportementClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        comportementClasse.replace("- " + ui->checkBoxParticipeSelonMatiere->text() + "\n","");
        qDebug() << comportementClasse;
    }
}




/********************** Difficultés en classe **********************/







void Interface3::on_checkBoxEcritureQualite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxEcritureQualite->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxEcritureQualite->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxDCConcentration_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxDCConcentration->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxDCConcentration->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxOrganiser_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxOrganiser->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxOrganiser->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxFaireDevoirs_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxFaireDevoirs->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxFaireDevoirs->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxEcritureQuantite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxEcritureQuantite->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxEcritureQuantite->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxMathematiquesCalcul_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxMathematiquesCalcul->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxMathematiquesCalcul->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxMathematiquesGeometrie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxMathematiquesGeometrie->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxMathematiquesGeometrie->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxEcritureQualiteQuantite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxEcritureQualiteQuantite->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxEcritureQualiteQuantite->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}


void Interface3::on_checkBoxMathematiquesCalculGeometrie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        difficultesClasse += "- " + ui->checkBoxMathematiquesCalculGeometrie->text() + "\n";
        qDebug() << difficultesClasse;
    }
    else if (arg1 == Qt::Unchecked)
    {
        difficultesClasse.replace("- " + ui->checkBoxMathematiquesCalculGeometrie->text() + "\n","");
        qDebug() << difficultesClasse;
    }
}




/********************* Matieres preferees *******************/



void Interface3::on_checkBoxPrefereEPS_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereEPS->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereEPS->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereHistoireGeographie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereHistoireGeographie->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereHistoireGeographie->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereMathematiques_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereMathematiques->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereMathematiques->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPreferePhysiqueChimie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPreferePhysiqueChimie->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPreferePhysiqueChimie->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereSVT_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereSVT->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereSVT->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereFrancais_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereFrancais->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereFrancais->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereAnglais_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereAnglais->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereAnglais->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereEspagnol_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereEspagnol->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereEspagnol->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereLangues_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereLangues->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereLangues->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereTechnologie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereTechnologie->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereTechnologie->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereMusique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereMusique->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereMusique->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}


void Interface3::on_checkBoxPrefereArtsPlastique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresPreferees += " " + ui->checkBoxPrefereArtsPlastique->text() + ", ";
        qDebug() << matieresPreferees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresPreferees.replace(" " + ui->checkBoxPrefereArtsPlastique->text() + ", ","");
        qDebug() << matieresPreferees;
    }
}




/**************** Matieres detestees ********************/






void Interface3::on_checkBoxDetesteEPS_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteEPS->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteEPS->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteHistoireGeo_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteHistoireGeo->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteHistoireGeo->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteMathematiques_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteMathematiques->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteMathematiques->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetestePhysiqueChimie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetestePhysiqueChimie->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetestePhysiqueChimie->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteSVT_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteSVT->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteSVT->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteFrancais_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteFrancais->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteFrancais->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteAnglais_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteAnglais->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteAnglais->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteEspagnol_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteEspagnol->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteEspagnol->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteLangues_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteLangues->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteLangues->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteTechnologie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteTechnologie->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteTechnologie->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteMusique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteMusique->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteMusique->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}


void Interface3::on_checkBoxDetesteArtsPlastique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        matieresDetestees += " " + ui->checkBoxDetesteArtsPlastique->text() + ", ";
        qDebug() << matieresDetestees;
    }
    else if (arg1 == Qt::Unchecked)
    {
        matieresDetestees.replace(" " + ui->checkBoxDetesteArtsPlastique->text() + ", ","");
        qDebug() << matieresDetestees;
    }
}



