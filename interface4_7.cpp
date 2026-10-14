#include "interface4_7.h"
#include "ui_interface4_7.h"
#include "patient.h"
#include "interface4_8.h"

// Activités d'une liste « - activité\n- activité\n », sans les tirets.
static QStringList activites(const QString &liste)
{
    QStringList resultat;
    for (QString element : liste.split('\n', Qt::SkipEmptyParts))
        resultat << element.remove(0, 2).trimmed();
    return resultat;
}

// « Aucun » en premier : sans choix, aucun objectif n'est retenu (avant, la
// première activité était choisie par défaut dans les 5 listes).
static void remplir(const QList<QComboBox*> &choix, const QStringList &activites)
{
    for (QComboBox *combo : choix) {
        combo->addItem("Aucun");
        combo->addItems(activites);
    }
}

// Ajoute à objectifs les activités choisies, sans « Aucun » ni doublon.
static void ajouterChoix(const QList<QComboBox*> &choix, QStringList &objectifs)
{
    for (const QComboBox *combo : choix) {
        const QString activite = combo->currentText();
        if (activite != "Aucun" && !objectifs.contains(activite))
            objectifs << activite;
    }
}

Interface4_7::Interface4_7(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_7)
{
    ui->setupUi(this);

    remplir(choixAVQ(), activites(Patient::aideMaison) + activites(Patient::difficulteMaison)
                            + activites(Patient::grandeDifficulteMaison));
    remplir(choixAVS(), activites(Patient::aideEcole) + activites(Patient::difficulteEcole)
                            + activites(Patient::grandeDifficulteEcole));
    remplir(choixAVL(), activites(Patient::aideLoisirs) + activites(Patient::difficulteLoisirs)
                            + activites(Patient::grandeDifficulteLoisirs));
}

Interface4_7::~Interface4_7()
{
    delete ui;
}

QList<QComboBox*> Interface4_7::choixAVQ() const
{
    return {ui->comboBoxChoix1AVQ, ui->comboBoxChoix2AVQ, ui->comboBoxChoix3AVQ,
            ui->comboBoxChoix4AVQ, ui->comboBoxChoix5AVQ};
}

QList<QComboBox*> Interface4_7::choixAVS() const
{
    return {ui->comboBoxChoix1AVS, ui->comboBoxChoix2AVS, ui->comboBoxChoix3AVS,
            ui->comboBoxChoix4AVS, ui->comboBoxChoix5AVS};
}

QList<QComboBox*> Interface4_7::choixAVL() const
{
    return {ui->comboBoxChoix1AVL, ui->comboBoxChoix2AVL, ui->comboBoxChoix3AVL,
            ui->comboBoxChoix4AVL, ui->comboBoxChoix5AVL};
}

void Interface4_7::on_pushButtonSuivant_clicked()
{
    Patient::objectfisAVQPatient.clear();
    Patient::objectfisAVSPatient.clear();
    Patient::objectfisAVLPatient.clear();
    Patient::objectfisFinauxPossibles.clear();

    ajouterChoix(choixAVQ(), Patient::objectfisAVQPatient);
    ajouterChoix(choixAVS(), Patient::objectfisAVSPatient);
    ajouterChoix(choixAVL(), Patient::objectfisAVLPatient);

    // Objectifs finaux proposés à l'écran suivant : toutes catégories confondues.
    ajouterChoix(choixAVQ() + choixAVS() + choixAVL(), Patient::objectfisFinauxPossibles);

    // Next interface
    Interface4_8 *interface4_8 = new Interface4_8();
    this->hide();
    interface4_8->show();
}
