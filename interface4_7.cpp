#include "interface4_7.h"
#include "ui_interface4_7.h"
#include "patient.h"
#include "interface4_8.h"

#define NB_OBJECTIFS 5

Interface4_7::Interface4_7(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Interface4_7)
{
    ui->setupUi(this);

    QStringList listeAVQ;
    QStringList listeAVS;
    QStringList listeAVL;

    QStringList listeTampon1 = Patient::aideMaison.split('\n');
    QStringList listeTampon2 = Patient::difficulteMaison.split('\n');
    QStringList listeTampon3 = Patient::grandeDifficulteMaison.split('\n');

    QStringList listeTampon4 = Patient::aideEcole.split('\n');
    QStringList listeTampon5 = Patient::difficulteEcole.split('\n');
    QStringList listeTampon6 = Patient::grandeDifficulteEcole.split('\n');

    QStringList listeTampon7 = Patient::aideLoisirs.split('\n');
    QStringList listeTampon8 = Patient::difficulteLoisirs.split('\n');
    QStringList listeTampon9 = Patient::grandeDifficulteLoisirs.split('\n');

    listeTampon1.removeLast();
    listeTampon2.removeLast();
    listeTampon3.removeLast();

    listeTampon4.removeLast();
    listeTampon5.removeLast();
    listeTampon6.removeLast();

    listeTampon7.removeLast();
    listeTampon8.removeLast();
    listeTampon9.removeLast();

    // // Afficher tous les éléments de la liste dans la console
    // foreach (const QString &element, listeTampon) {
    //     qDebug() << element;
    // }

    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon1) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVQ << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon2) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVQ << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon3) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVQ << element;
    }


    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon4) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVS << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon5) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVS << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon6) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVS << element;
    }


    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon7) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVL << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon8) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVL << element;
    }
    // Parcourir la liste et nettoyer chaque élément
    foreach (QString element, listeTampon9) {
        // Retirer le préfixe "- " et les espaces de la fin
        element = element.remove(0, 2).trimmed();
        listeAVL << element;
    }
    // // Afficher tous les éléments de la liste dans la console
    // foreach (const QString &element, listeAideMaison) {
    //     qDebug() << element;
    // }


    ui->comboBoxChoix1AVQ->addItems(listeAVQ);
    ui->comboBoxChoix2AVQ->addItems(listeAVQ);
    ui->comboBoxChoix3AVQ->addItems(listeAVQ);
    ui->comboBoxChoix4AVQ->addItems(listeAVQ);
    ui->comboBoxChoix5AVQ->addItems(listeAVQ);

    ui->comboBoxChoix1AVQ->addItem("Aucun");
    ui->comboBoxChoix2AVQ->addItem("Aucun");
    ui->comboBoxChoix3AVQ->addItem("Aucun");
    ui->comboBoxChoix4AVQ->addItem("Aucun");
    ui->comboBoxChoix5AVQ->addItem("Aucun");


    ui->comboBoxChoix1AVS->addItems(listeAVS);
    ui->comboBoxChoix2AVS->addItems(listeAVS);
    ui->comboBoxChoix3AVS->addItems(listeAVS);
    ui->comboBoxChoix4AVS->addItems(listeAVS);
    ui->comboBoxChoix5AVS->addItems(listeAVS);

    ui->comboBoxChoix1AVS->addItem("Aucun");
    ui->comboBoxChoix2AVS->addItem("Aucun");
    ui->comboBoxChoix3AVS->addItem("Aucun");
    ui->comboBoxChoix4AVS->addItem("Aucun");
    ui->comboBoxChoix5AVS->addItem("Aucun");



    ui->comboBoxChoix1AVL->addItems(listeAVL);
    ui->comboBoxChoix2AVL->addItems(listeAVL);
    ui->comboBoxChoix3AVL->addItems(listeAVL);
    ui->comboBoxChoix4AVL->addItems(listeAVL);
    ui->comboBoxChoix5AVL->addItems(listeAVL);


    ui->comboBoxChoix1AVL->addItem("Aucun");
    ui->comboBoxChoix2AVL->addItem("Aucun");
    ui->comboBoxChoix3AVL->addItem("Aucun");
    ui->comboBoxChoix4AVL->addItem("Aucun");
    ui->comboBoxChoix5AVL->addItem("Aucun");



}

Interface4_7::~Interface4_7()
{
    delete ui;
}

void Interface4_7::on_pushButtonSuivant_clicked()
{

    if(ui->comboBoxChoix1AVQ->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix1AVQ->currentText());
        Patient::objectfisAVQPatient.append(ui->comboBoxChoix1AVQ->currentText());
    }
    if(ui->comboBoxChoix2AVQ->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix2AVQ->currentText());
        Patient::objectfisAVQPatient.append(ui->comboBoxChoix2AVQ->currentText());
    }
    if(ui->comboBoxChoix3AVQ->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix3AVQ->currentText());
        Patient::objectfisAVQPatient.append(ui->comboBoxChoix3AVQ->currentText());
    }
    if(ui->comboBoxChoix4AVQ->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix4AVQ->currentText());
        Patient::objectfisAVQPatient.append(ui->comboBoxChoix4AVQ->currentText());
    }
    if(ui->comboBoxChoix5AVQ->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix5AVQ->currentText());
        Patient::objectfisAVQPatient.append(ui->comboBoxChoix5AVQ->currentText());
    }

    if(ui->comboBoxChoix1AVS->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix1AVS->currentText());
        Patient::objectfisAVSPatient.append(ui->comboBoxChoix1AVS->currentText());
    }
    if(ui->comboBoxChoix2AVS->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix2AVS->currentText());
        Patient::objectfisAVSPatient.append(ui->comboBoxChoix2AVS->currentText());
    }
    if(ui->comboBoxChoix3AVS->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix3AVS->currentText());
        Patient::objectfisAVSPatient.append(ui->comboBoxChoix3AVS->currentText());
    }
    if(ui->comboBoxChoix4AVS->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix4AVS->currentText());
        Patient::objectfisAVSPatient.append(ui->comboBoxChoix4AVS->currentText());
    }
    if(ui->comboBoxChoix5AVS->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix5AVS->currentText());
        Patient::objectfisAVSPatient.append(ui->comboBoxChoix5AVS->currentText());
    }

    if(ui->comboBoxChoix1AVL->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix1AVL->currentText());
        Patient::objectfisAVLPatient.append(ui->comboBoxChoix1AVL->currentText());
    }
    if(ui->comboBoxChoix2AVL->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix2AVL->currentText());
        Patient::objectfisAVLPatient.append(ui->comboBoxChoix2AVL->currentText());
    }
    if(ui->comboBoxChoix3AVL->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix3AVL->currentText());
        Patient::objectfisAVLPatient.append(ui->comboBoxChoix3AVL->currentText());
    }
    if(ui->comboBoxChoix4AVL->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix4AVL->currentText());
        Patient::objectfisAVLPatient.append(ui->comboBoxChoix4AVL->currentText());
    }
    if(ui->comboBoxChoix5AVL->currentText() != "Aucun"){
        Patient::objectfisFinauxPossibles.append(ui->comboBoxChoix5AVL->currentText());
        Patient::objectfisAVLPatient.append(ui->comboBoxChoix5AVL->currentText());
    }

    foreach (const QString &element, Patient::objectfisFinauxPossibles) {
        qDebug() << element;
    }

    // Next interface
    Interface4_8 *interface4_8 = new Interface4_8();
    this->hide();
    interface4_8->show();
}

