#include "interface5.h"
#include "ui_interface5.h"
#include "questionnaire.h"
#include "word.h"

#include <QFileInfo>
#include <QMessageBox>

// Activités saisies dans les deux champs, séparées par des virgules.
static QStringList activites(const QString &premier, const QString &second)
{
    QStringList liste;
    for (const QString &activite : (premier + "," + second).split(','))
        if (!activite.trimmed().isEmpty())
            liste << activite.trimmed();
    return liste;
}

Interface5::Interface5(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface5)
{
    ui->setupUi(this);

    ui->listeAmenagements->remplir(Questionnaire::liste("amenagements"), 3);
}

Interface5::~Interface5()
{
    delete ui;
}

void Interface5::on_pushButtonSuivant_clicked()
{
    Word::document = Word::ouvrir(Word::filePathToSave);
    if (Word::document && !Word::document->isNull()) {
        Word::selection = Word::wordApp->querySubObject("Selection");

        Word::replaceText("{amenagements_scolaires}",Word::enListe(ui->listeAmenagements->cochees()));
        Word::replaceText("{activites_extra_scolaires}",
                          Word::enListe(activites(ui->lineEditActivitesExtraScolaires1->text(),
                                                  ui->lineEditActivitesExtraScolaires2->text())));
        Word::replaceText("{activites_temps_libre}",
                          Word::enListe(activites(ui->lineEditActivitesTempsLibre1->text(),
                                                  ui->lineEditActivitesTempsLibre2->text())));

        const QString difficultes = ui->lineEditDifficultesPendantLoisirs->text().trimmed();
        Word::replaceText("{difficultes_loisirs}",
                          difficultes.isEmpty() ? "" : "- difficultés pendant les loisirs : " + difficultes);

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
