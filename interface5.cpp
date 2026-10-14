#include "interface5.h"
#include "ui_interface5.h"
#include "word.h"

#include <QFileInfo>
#include <QMessageBox>

// Une activité par ligne (« - activité ») : les deux champs, séparés par des virgules.
static QString enListe(const QString &premier, const QString &second)
{
    QStringList activites;
    for (const QString &activite : (premier + "," + second).split(','))
        if (!activite.trimmed().isEmpty())
            activites << "- " + activite.trimmed();
    return activites.join("\n");
}

Interface5::Interface5(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface5)
{
    ui->setupUi(this);
}

Interface5::~Interface5()
{
    delete ui;
}

void Interface5::on_pushButtonSuivant_clicked()
{
    Word::copieColle(Word::modele("interface5"), Word::filePathToSave);

    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");


        Word::replaceText("i_amenagements_scolaires",amenagementsScolaires);

        Word::replaceText("i_activite_extra_scolaire",
                          enListe(ui->lineEditActivitesExtraScolaires1->text(), ui->lineEditActivitesExtraScolaires2->text()));
        Word::replaceText("i_activite_temps_libre",
                          enListe(ui->lineEditActivitesTempsLibre1->text(), ui->lineEditActivitesTempsLibre2->text()));

        if(ui->lineEditDifficultesPendantLoisirs->text()== "")
        {
            Word::replaceText("i_difficultes_pendant_loisirs","");
        }
        else
        {
            Word::replaceText("i_difficultes_pendant_loisirs","- difficultés pendant les loisirs : " + ui->lineEditDifficultesPendantLoisirs->text());
        }

        // Save the document
        Word::document->dynamicCall("Save()");
        Word::document->dynamicCall("Close()");
    }

    Word::fermer();
    // Les erreurs éventuelles ont déjà été signalées par Word::.
    if (QFileInfo::exists(Word::filePathToSave))
        QMessageBox::information(this, "TrameErgo", "Bilan enregistré :\n"
                                 + QDir::toNativeSeparators(Word::filePathToSave));
    QCoreApplication::quit();
}


void Interface5::on_checkBoxAESH_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxAESH->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxAESH->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxOrdinateur_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxOrdinateur->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxOrdinateur->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxMiseEnPlacePAP_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxMiseEnPlacePAP->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxMiseEnPlacePAP->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxMiseEnPlacePPS_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxMiseEnPlacePPS->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxMiseEnPlacePPS->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxMiseEnPlacePPRE_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxMiseEnPlacePPRE->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxMiseEnPlacePPRE->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxPolycopiesDonnes_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxPolycopiesDonnes->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxPolycopiesDonnes->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxTierTemps_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxTierTemps->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxTierTemps->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxMoinsExercices_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxMoinsExercices->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxMoinsExercices->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}


void Interface5::on_checkBoxDicterTrous_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        amenagementsScolaires += "- " + ui->checkBoxDicterTrous->text() + "\n";
        qDebug() << amenagementsScolaires;
    }
    else if (arg1 == Qt::Unchecked)
    {
        amenagementsScolaires.replace("- " + ui->checkBoxDicterTrous->text() + "\n","");
        qDebug() << amenagementsScolaires;
    }
}

