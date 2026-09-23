/********************************************************************************
** Form generated from reading UI file 'interface2_1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE2_1_H
#define UI_INTERFACE2_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Interface2_1
{
public:
    QLabel *labelPersonneDemandeuse;
    QGroupBox *groupBoxMotifs;
    QCheckBox *checkBoxMotif1;
    QCheckBox *checkBoxMotif2;
    QCheckBox *checkBoxMotif3;
    QLabel *labelAutreMotif;
    QLineEdit *lineEditAutreMotif;
    QComboBox *comboBoxDossierMDPH;
    QPushButton *pushButtonSuivant;
    QGroupBox *groupBox;
    QCheckBox *checkBoxDifficultesEcriture;
    QCheckBox *checkBoxdDifficultesLecture;
    QCheckBox *checkBoxDifficultesCoordination;
    QCheckBox *checkBoxDifficultesConcentration;
    QCheckBox *checkBoxDysgraphie;
    QCheckBox *checkBoxDyslexie;
    QCheckBox *checkBoxHyperlaxite;
    QCheckBox *checkBoxDeveloppementCoordination;
    QCheckBox *checkBoxTDAAvecHyperactivite;
    QCheckBox *checkBoxDystographie;
    QCheckBox *checkBoxTDASansHyperactivite;
    QCheckBox *checkBoxDifficultesSociales;
    QCheckBox *checkBoxTSA;
    QCheckBox *checkBoxAutistiqueAsperger;
    QLineEdit *lineEditAutreTrouble;
    QLabel *labelAutreTrouble;
    QCheckBox *checkBoxPsychologique;
    QCheckBox *checkBoxPsychiatrique;
    QComboBox *comboBoxPersonneDemandeuse;
    QLabel *labelDossierMDPH;

    void setupUi(QDialog *Interface2_1)
    {
        if (Interface2_1->objectName().isEmpty())
            Interface2_1->setObjectName("Interface2_1");
        Interface2_1->resize(738, 374);
        labelPersonneDemandeuse = new QLabel(Interface2_1);
        labelPersonneDemandeuse->setObjectName("labelPersonneDemandeuse");
        labelPersonneDemandeuse->setGeometry(QRect(20, 20, 131, 21));
        groupBoxMotifs = new QGroupBox(Interface2_1);
        groupBoxMotifs->setObjectName("groupBoxMotifs");
        groupBoxMotifs->setGeometry(QRect(20, 50, 591, 131));
        checkBoxMotif1 = new QCheckBox(groupBoxMotifs);
        checkBoxMotif1->setObjectName("checkBoxMotif1");
        checkBoxMotif1->setGeometry(QRect(10, 20, 581, 18));
        checkBoxMotif2 = new QCheckBox(groupBoxMotifs);
        checkBoxMotif2->setObjectName("checkBoxMotif2");
        checkBoxMotif2->setGeometry(QRect(10, 40, 401, 18));
        checkBoxMotif3 = new QCheckBox(groupBoxMotifs);
        checkBoxMotif3->setObjectName("checkBoxMotif3");
        checkBoxMotif3->setGeometry(QRect(10, 60, 331, 18));
        labelAutreMotif = new QLabel(groupBoxMotifs);
        labelAutreMotif->setObjectName("labelAutreMotif");
        labelAutreMotif->setGeometry(QRect(20, 90, 49, 16));
        lineEditAutreMotif = new QLineEdit(groupBoxMotifs);
        lineEditAutreMotif->setObjectName("lineEditAutreMotif");
        lineEditAutreMotif->setGeometry(QRect(70, 90, 491, 22));
        comboBoxDossierMDPH = new QComboBox(Interface2_1);
        comboBoxDossierMDPH->addItem(QString());
        comboBoxDossierMDPH->addItem(QString());
        comboBoxDossierMDPH->addItem(QString());
        comboBoxDossierMDPH->addItem(QString());
        comboBoxDossierMDPH->setObjectName("comboBoxDossierMDPH");
        comboBoxDossierMDPH->setGeometry(QRect(130, 340, 141, 22));
        pushButtonSuivant = new QPushButton(Interface2_1);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(630, 340, 75, 24));
        groupBox = new QGroupBox(Interface2_1);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 180, 681, 151));
        checkBoxDifficultesEcriture = new QCheckBox(groupBox);
        checkBoxDifficultesEcriture->setObjectName("checkBoxDifficultesEcriture");
        checkBoxDifficultesEcriture->setGeometry(QRect(0, 20, 131, 20));
        checkBoxdDifficultesLecture = new QCheckBox(groupBox);
        checkBoxdDifficultesLecture->setObjectName("checkBoxdDifficultesLecture");
        checkBoxdDifficultesLecture->setGeometry(QRect(0, 40, 131, 20));
        checkBoxDifficultesCoordination = new QCheckBox(groupBox);
        checkBoxDifficultesCoordination->setObjectName("checkBoxDifficultesCoordination");
        checkBoxDifficultesCoordination->setGeometry(QRect(0, 60, 161, 20));
        checkBoxDifficultesConcentration = new QCheckBox(groupBox);
        checkBoxDifficultesConcentration->setObjectName("checkBoxDifficultesConcentration");
        checkBoxDifficultesConcentration->setGeometry(QRect(0, 80, 171, 20));
        checkBoxDysgraphie = new QCheckBox(groupBox);
        checkBoxDysgraphie->setObjectName("checkBoxDysgraphie");
        checkBoxDysgraphie->setGeometry(QRect(170, 70, 81, 21));
        checkBoxDyslexie = new QCheckBox(groupBox);
        checkBoxDyslexie->setObjectName("checkBoxDyslexie");
        checkBoxDyslexie->setGeometry(QRect(170, 30, 76, 20));
        checkBoxHyperlaxite = new QCheckBox(groupBox);
        checkBoxHyperlaxite->setObjectName("checkBoxHyperlaxite");
        checkBoxHyperlaxite->setGeometry(QRect(170, 10, 91, 20));
        checkBoxDeveloppementCoordination = new QCheckBox(groupBox);
        checkBoxDeveloppementCoordination->setObjectName("checkBoxDeveloppementCoordination");
        checkBoxDeveloppementCoordination->setGeometry(QRect(340, 90, 271, 20));
        checkBoxTDAAvecHyperactivite = new QCheckBox(groupBox);
        checkBoxTDAAvecHyperactivite->setObjectName("checkBoxTDAAvecHyperactivite");
        checkBoxTDAAvecHyperactivite->setGeometry(QRect(340, 30, 141, 20));
        checkBoxDystographie = new QCheckBox(groupBox);
        checkBoxDystographie->setObjectName("checkBoxDystographie");
        checkBoxDystographie->setGeometry(QRect(170, 50, 121, 20));
        checkBoxTDASansHyperactivite = new QCheckBox(groupBox);
        checkBoxTDASansHyperactivite->setObjectName("checkBoxTDASansHyperactivite");
        checkBoxTDASansHyperactivite->setGeometry(QRect(340, 10, 151, 20));
        checkBoxDifficultesSociales = new QCheckBox(groupBox);
        checkBoxDifficultesSociales->setObjectName("checkBoxDifficultesSociales");
        checkBoxDifficultesSociales->setGeometry(QRect(170, 90, 111, 20));
        checkBoxTSA = new QCheckBox(groupBox);
        checkBoxTSA->setObjectName("checkBoxTSA");
        checkBoxTSA->setGeometry(QRect(340, 50, 76, 20));
        checkBoxAutistiqueAsperger = new QCheckBox(groupBox);
        checkBoxAutistiqueAsperger->setObjectName("checkBoxAutistiqueAsperger");
        checkBoxAutistiqueAsperger->setGeometry(QRect(340, 70, 211, 20));
        lineEditAutreTrouble = new QLineEdit(groupBox);
        lineEditAutreTrouble->setObjectName("lineEditAutreTrouble");
        lineEditAutreTrouble->setGeometry(QRect(90, 120, 491, 22));
        labelAutreTrouble = new QLabel(groupBox);
        labelAutreTrouble->setObjectName("labelAutreTrouble");
        labelAutreTrouble->setGeometry(QRect(40, 120, 49, 16));
        checkBoxPsychologique = new QCheckBox(groupBox);
        checkBoxPsychologique->setObjectName("checkBoxPsychologique");
        checkBoxPsychologique->setGeometry(QRect(530, 10, 141, 20));
        checkBoxPsychiatrique = new QCheckBox(groupBox);
        checkBoxPsychiatrique->setObjectName("checkBoxPsychiatrique");
        checkBoxPsychiatrique->setGeometry(QRect(530, 30, 141, 20));
        comboBoxPersonneDemandeuse = new QComboBox(Interface2_1);
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->addItem(QString());
        comboBoxPersonneDemandeuse->setObjectName("comboBoxPersonneDemandeuse");
        comboBoxPersonneDemandeuse->setGeometry(QRect(160, 20, 131, 22));
        labelDossierMDPH = new QLabel(Interface2_1);
        labelDossierMDPH->setObjectName("labelDossierMDPH");
        labelDossierMDPH->setGeometry(QRect(40, 340, 91, 16));

        retranslateUi(Interface2_1);

        QMetaObject::connectSlotsByName(Interface2_1);
    } // setupUi

    void retranslateUi(QDialog *Interface2_1)
    {
        Interface2_1->setWindowTitle(QCoreApplication::translate("Interface2_1", "Dialog", nullptr));
        labelPersonneDemandeuse->setText(QCoreApplication::translate("Interface2_1", "Personne demandeuse :", nullptr));
        groupBoxMotifs->setTitle(QCoreApplication::translate("Interface2_1", "Motifs ", nullptr));
        checkBoxMotif1->setText(QCoreApplication::translate("Interface2_1", "Voir la pertinence de la mise en place de l'outil informatique pour compenser les difficult\303\251s d'\303\251criture", nullptr));
        checkBoxMotif2->setText(QCoreApplication::translate("Interface2_1", "Explorer d'o\303\271 viennent les difficult\303\251s qui g\303\251n\303\250rent un trouble graphique", nullptr));
        checkBoxMotif3->setText(QCoreApplication::translate("Interface2_1", "Faire le point sur les besoins en am\303\251nagements scolaires", nullptr));
        labelAutreMotif->setText(QCoreApplication::translate("Interface2_1", "Autre :", nullptr));
        comboBoxDossierMDPH->setItemText(0, QCoreApplication::translate("Interface2_1", "Actif", nullptr));
        comboBoxDossierMDPH->setItemText(1, QCoreApplication::translate("Interface2_1", "En renouvellement", nullptr));
        comboBoxDossierMDPH->setItemText(2, QCoreApplication::translate("Interface2_1", "En cr\303\251ation ", nullptr));
        comboBoxDossierMDPH->setItemText(3, QCoreApplication::translate("Interface2_1", "Aucun", nullptr));

        pushButtonSuivant->setText(QCoreApplication::translate("Interface2_1", "Suivant ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Interface2_1", "Anamn\303\250se/ Troubles : ", nullptr));
        checkBoxDifficultesEcriture->setText(QCoreApplication::translate("Interface2_1", "Difficult\303\251 d'\303\251criture ", nullptr));
        checkBoxdDifficultesLecture->setText(QCoreApplication::translate("Interface2_1", "Difficult\303\251 de lecture ", nullptr));
        checkBoxDifficultesCoordination->setText(QCoreApplication::translate("Interface2_1", "Difficult\303\251 de coordination", nullptr));
        checkBoxDifficultesConcentration->setText(QCoreApplication::translate("Interface2_1", "Difficult\303\251 de concentration", nullptr));
        checkBoxDysgraphie->setText(QCoreApplication::translate("Interface2_1", "Dysgraphie", nullptr));
        checkBoxDyslexie->setText(QCoreApplication::translate("Interface2_1", "Dyslexie", nullptr));
        checkBoxHyperlaxite->setText(QCoreApplication::translate("Interface2_1", "Hyperlaxit\303\251", nullptr));
        checkBoxDeveloppementCoordination->setText(QCoreApplication::translate("Interface2_1", "Trouble du d\303\251veloppement des coordinations ", nullptr));
        checkBoxTDAAvecHyperactivite->setText(QCoreApplication::translate("Interface2_1", "TDA avec hyperactivit\303\251", nullptr));
        checkBoxDystographie->setText(QCoreApplication::translate("Interface2_1", "Dysorthographie", nullptr));
        checkBoxTDASansHyperactivite->setText(QCoreApplication::translate("Interface2_1", "TDA sans hyperactivit\303\251", nullptr));
        checkBoxDifficultesSociales->setText(QCoreApplication::translate("Interface2_1", "Difficult\303\251 sociale ", nullptr));
        checkBoxTSA->setText(QCoreApplication::translate("Interface2_1", "TSA", nullptr));
        checkBoxAutistiqueAsperger->setText(QCoreApplication::translate("Interface2_1", "Trouble autistique de type asperger", nullptr));
        labelAutreTrouble->setText(QCoreApplication::translate("Interface2_1", "Autre :", nullptr));
        checkBoxPsychologique->setText(QCoreApplication::translate("Interface2_1", "Trouble psychologique", nullptr));
        checkBoxPsychiatrique->setText(QCoreApplication::translate("Interface2_1", "Trouble psychiatrique ", nullptr));
        comboBoxPersonneDemandeuse->setItemText(0, QCoreApplication::translate("Interface2_1", "le m\303\251decin traitant", nullptr));
        comboBoxPersonneDemandeuse->setItemText(1, QCoreApplication::translate("Interface2_1", "la neurop\303\251diatre", nullptr));
        comboBoxPersonneDemandeuse->setItemText(2, QCoreApplication::translate("Interface2_1", "l'enseignant", nullptr));
        comboBoxPersonneDemandeuse->setItemText(3, QCoreApplication::translate("Interface2_1", "la psychomotricienne", nullptr));
        comboBoxPersonneDemandeuse->setItemText(4, QCoreApplication::translate("Interface2_1", "la neuropsychologue", nullptr));
        comboBoxPersonneDemandeuse->setItemText(5, QCoreApplication::translate("Interface2_1", "le(s) parent(s)", nullptr));
        comboBoxPersonneDemandeuse->setItemText(6, QCoreApplication::translate("Interface2_1", "le p\303\250re ", nullptr));
        comboBoxPersonneDemandeuse->setItemText(7, QCoreApplication::translate("Interface2_1", "la m\303\250re", nullptr));

        labelDossierMDPH->setText(QCoreApplication::translate("Interface2_1", "Dossier MDPH : ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface2_1: public Ui_Interface2_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE2_1_H
