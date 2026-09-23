#include "interface2_1.h"
#include "ui_interface2_1.h"
#include "word.h"
#include "interface2_2.h"

Interface2_1::Interface2_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface2_1)
{
    ui->setupUi(this);
}

Interface2_1::~Interface2_1()
{
    delete ui;
}

void Interface2_1::on_pushButtonSuivant_clicked()
{
    Word::copieColle(Word::pathToArbo + "/arborescence/Femme/Enfant/Interface2/interface2.docx", Word::filePathToSave);

    qDebug() << "filePathToSave";

    Word::document = Word::documents->querySubObject("Open(const QString&)",  Word::filePathToSave);
    if (!Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");



        Word::replaceText("i_personne_demandeuse",ui->comboBoxPersonneDemandeuse->currentText());

        if(ui->lineEditAutreMotif->text() == "")
        {
            if (motifs.size() >= 2) {
                // Utilisez la méthode erase() pour enlever les deux derniers caractères
                motifs.remove(motifs.size() - 2, 2);
            } else {
                // Gérez le cas où la chaîne a moins de deux caractères
                 qDebug() << "La chaîne est trop courte pour enlever les deux derniers caractères.";
            }
        }
        else
        {
            motifs += ui->lineEditAutreMotif->text();
        }

        qDebug() << motifs;

        Word::replaceText("i_motifs",motifs);

        if(ui->lineEditAutreTrouble->text() != "")
        {
            troubles += "- " + ui->lineEditAutreTrouble->text();
        }

        qDebug() << troubles;

        Word::replaceText("i_anamnese/troubles",troubles);

        Word::replaceText("i_dossier_mdph",ui->comboBoxDossierMDPH->currentText());

        // Word::replaceText("i_ville",ui->lineEditVille->text());
        // Word::replaceTextFromZoneText("i_prenom",ui->lineEditPrenom->text());
        // Word::replaceTextFromZoneText("i_nom",ui->lineEditNom->text());
        // Word::replaceTextFromZoneText("i_date_de_passation",ui->dateEditPassation->date().toString("dd-MM-yyyy"));
        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    // Next interface
    Interface2_2 *interface2_2 = new Interface2_2();
    this->hide();
    interface2_2->show();
}


void Interface2_1::on_checkBoxMotif1_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        motifs += ui->checkBoxMotif1->text() + ", ";
        qDebug() << motifs;
    }
    else if (arg1 == Qt::Unchecked)
    {
        motifs.replace(ui->checkBoxMotif1->text() + ", ","");
        qDebug() << motifs;
    }
}


void Interface2_1::on_checkBoxMotif2_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        motifs += ui->checkBoxMotif2->text() + ", ";
        qDebug() << motifs;
    }
    else if (arg1 == Qt::Unchecked)
    {
        motifs.replace(ui->checkBoxMotif2->text() + ", ","");
        qDebug() << motifs;
    }
}


void Interface2_1::on_checkBoxMotif3_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        motifs += ui->checkBoxMotif3->text() + ", ";
        qDebug() << motifs;
    }
    else if (arg1 == Qt::Unchecked)
    {
        motifs.replace(ui->checkBoxMotif3->text() + ", ","");
        qDebug() << motifs;
    }
}






void Interface2_1::on_checkBoxTDASansHyperactivite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxTDASansHyperactivite->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxTDASansHyperactivite->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDifficultesEcriture_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDifficultesEcriture->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDifficultesEcriture->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxdDifficultesLecture_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxdDifficultesLecture->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxdDifficultesLecture->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDifficultesCoordination_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDifficultesCoordination->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDifficultesCoordination->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDifficultesConcentration_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDifficultesConcentration->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDifficultesConcentration->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDysgraphie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDysgraphie->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDysgraphie->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDyslexie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDyslexie->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDyslexie->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDystographie_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDystographie->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDystographie->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDifficultesSociales_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDifficultesSociales->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDifficultesSociales->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxHyperlaxite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxHyperlaxite->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxHyperlaxite->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxDeveloppementCoordination_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxDeveloppementCoordination->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxDeveloppementCoordination->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxTSA_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxTSA->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxTSA->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxAutistiqueAsperger_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxAutistiqueAsperger->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxAutistiqueAsperger->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxTDAAvecHyperactivite_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxTDAAvecHyperactivite->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxTDAAvecHyperactivite->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxPsychologique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxPsychologique->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxPsychologique->text() + "\n","");
        qDebug() << troubles;
    }
}


void Interface2_1::on_checkBoxPsychiatrique_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        troubles += "- " + ui->checkBoxPsychiatrique->text() + "\n";
        qDebug() << troubles;
    }
    else if (arg1 == Qt::Unchecked)
    {
        troubles.replace("- " + ui->checkBoxPsychiatrique->text() + "\n","");
        qDebug() << troubles;
    }
}

