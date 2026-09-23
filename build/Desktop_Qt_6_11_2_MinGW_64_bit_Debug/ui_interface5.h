/********************************************************************************
** Form generated from reading UI file 'interface5.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE5_H
#define UI_INTERFACE5_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Interface5
{
public:
    QGroupBox *groupBoxActivitesTempsLibre;
    QLineEdit *lineEditActivitesTempsLibre1;
    QLineEdit *lineEditActivitesTempsLibre2;
    QGroupBox *groupBoxDifficultesPendantLoisirs;
    QLineEdit *lineEditDifficultesPendantLoisirs;
    QGroupBox *groupBoxAmenagementsScolaires;
    QCheckBox *checkBoxAESH;
    QCheckBox *checkBoxOrdinateur;
    QCheckBox *checkBoxMiseEnPlacePAP;
    QCheckBox *checkBoxMiseEnPlacePPS;
    QCheckBox *checkBoxMiseEnPlacePPRE;
    QCheckBox *checkBoxTierTemps;
    QCheckBox *checkBoxPolycopiesDonnes;
    QCheckBox *checkBoxMoinsExercices;
    QCheckBox *checkBoxDicterTrous;
    QGroupBox *groupBoxActivitesExtraScolaires;
    QLineEdit *lineEditActivitesExtraScolaires1;
    QLineEdit *lineEditActivitesExtraScolaires2;
    QPushButton *pushButtonSuivant;

    void setupUi(QDialog *Interface5)
    {
        if (Interface5->objectName().isEmpty())
            Interface5->setObjectName("Interface5");
        Interface5->resize(591, 417);
        groupBoxActivitesTempsLibre = new QGroupBox(Interface5);
        groupBoxActivitesTempsLibre->setObjectName("groupBoxActivitesTempsLibre");
        groupBoxActivitesTempsLibre->setGeometry(QRect(0, 200, 571, 91));
        lineEditActivitesTempsLibre1 = new QLineEdit(groupBoxActivitesTempsLibre);
        lineEditActivitesTempsLibre1->setObjectName("lineEditActivitesTempsLibre1");
        lineEditActivitesTempsLibre1->setGeometry(QRect(10, 20, 531, 22));
        lineEditActivitesTempsLibre2 = new QLineEdit(groupBoxActivitesTempsLibre);
        lineEditActivitesTempsLibre2->setObjectName("lineEditActivitesTempsLibre2");
        lineEditActivitesTempsLibre2->setGeometry(QRect(10, 50, 531, 22));
        groupBoxDifficultesPendantLoisirs = new QGroupBox(Interface5);
        groupBoxDifficultesPendantLoisirs->setObjectName("groupBoxDifficultesPendantLoisirs");
        groupBoxDifficultesPendantLoisirs->setGeometry(QRect(0, 290, 551, 80));
        lineEditDifficultesPendantLoisirs = new QLineEdit(groupBoxDifficultesPendantLoisirs);
        lineEditDifficultesPendantLoisirs->setObjectName("lineEditDifficultesPendantLoisirs");
        lineEditDifficultesPendantLoisirs->setGeometry(QRect(10, 20, 113, 22));
        groupBoxAmenagementsScolaires = new QGroupBox(Interface5);
        groupBoxAmenagementsScolaires->setObjectName("groupBoxAmenagementsScolaires");
        groupBoxAmenagementsScolaires->setGeometry(QRect(0, 0, 571, 91));
        checkBoxAESH = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxAESH->setObjectName("checkBoxAESH");
        checkBoxAESH->setGeometry(QRect(10, 20, 151, 20));
        checkBoxOrdinateur = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxOrdinateur->setObjectName("checkBoxOrdinateur");
        checkBoxOrdinateur->setGeometry(QRect(10, 40, 151, 20));
        checkBoxMiseEnPlacePAP = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxMiseEnPlacePAP->setObjectName("checkBoxMiseEnPlacePAP");
        checkBoxMiseEnPlacePAP->setGeometry(QRect(10, 60, 321, 20));
        checkBoxMiseEnPlacePPS = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxMiseEnPlacePPS->setObjectName("checkBoxMiseEnPlacePPS");
        checkBoxMiseEnPlacePPS->setGeometry(QRect(170, 20, 151, 20));
        checkBoxMiseEnPlacePPRE = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxMiseEnPlacePPRE->setObjectName("checkBoxMiseEnPlacePPRE");
        checkBoxMiseEnPlacePPRE->setGeometry(QRect(170, 40, 271, 20));
        checkBoxTierTemps = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxTierTemps->setObjectName("checkBoxTierTemps");
        checkBoxTierTemps->setGeometry(QRect(370, 20, 141, 20));
        checkBoxPolycopiesDonnes = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxPolycopiesDonnes->setObjectName("checkBoxPolycopiesDonnes");
        checkBoxPolycopiesDonnes->setGeometry(QRect(170, 60, 231, 20));
        checkBoxMoinsExercices = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxMoinsExercices->setObjectName("checkBoxMoinsExercices");
        checkBoxMoinsExercices->setGeometry(QRect(370, 40, 111, 20));
        checkBoxDicterTrous = new QCheckBox(groupBoxAmenagementsScolaires);
        checkBoxDicterTrous->setObjectName("checkBoxDicterTrous");
        checkBoxDicterTrous->setGeometry(QRect(370, 60, 91, 20));
        groupBoxActivitesExtraScolaires = new QGroupBox(Interface5);
        groupBoxActivitesExtraScolaires->setObjectName("groupBoxActivitesExtraScolaires");
        groupBoxActivitesExtraScolaires->setGeometry(QRect(0, 100, 571, 91));
        lineEditActivitesExtraScolaires1 = new QLineEdit(groupBoxActivitesExtraScolaires);
        lineEditActivitesExtraScolaires1->setObjectName("lineEditActivitesExtraScolaires1");
        lineEditActivitesExtraScolaires1->setGeometry(QRect(10, 30, 531, 21));
        lineEditActivitesExtraScolaires2 = new QLineEdit(groupBoxActivitesExtraScolaires);
        lineEditActivitesExtraScolaires2->setObjectName("lineEditActivitesExtraScolaires2");
        lineEditActivitesExtraScolaires2->setGeometry(QRect(10, 60, 531, 22));
        pushButtonSuivant = new QPushButton(Interface5);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(500, 380, 75, 24));

        retranslateUi(Interface5);

        QMetaObject::connectSlotsByName(Interface5);
    } // setupUi

    void retranslateUi(QDialog *Interface5)
    {
        Interface5->setWindowTitle(QCoreApplication::translate("Interface5", "Dialog", nullptr));
        groupBoxActivitesTempsLibre->setTitle(QCoreApplication::translate("Interface5", "Activit\303\251 temps libre ", nullptr));
        groupBoxDifficultesPendantLoisirs->setTitle(QCoreApplication::translate("Interface5", "Difficult\303\251 pendant les loisirs : ", nullptr));
        groupBoxAmenagementsScolaires->setTitle(QCoreApplication::translate("Interface5", "Am\303\251nagements scolaire ", nullptr));
        checkBoxAESH->setText(QCoreApplication::translate("Interface5", "AESH", nullptr));
        checkBoxOrdinateur->setText(QCoreApplication::translate("Interface5", "Ordinateur ", nullptr));
        checkBoxMiseEnPlacePAP->setText(QCoreApplication::translate("Interface5", "Mise en place d'un PAP", nullptr));
        checkBoxMiseEnPlacePPS->setText(QCoreApplication::translate("Interface5", "Mise en place d'un PPS", nullptr));
        checkBoxMiseEnPlacePPRE->setText(QCoreApplication::translate("Interface5", "Mise en place d'un PPRE", nullptr));
        checkBoxTierTemps->setText(QCoreApplication::translate("Interface5", "Tiers temps ", nullptr));
        checkBoxPolycopiesDonnes->setText(QCoreApplication::translate("Interface5", "Polycopi\303\251s donn\303\251s ", nullptr));
        checkBoxMoinsExercices->setText(QCoreApplication::translate("Interface5", "Moins d'exercice ", nullptr));
        checkBoxDicterTrous->setText(QCoreApplication::translate("Interface5", "Dict\303\251e \303\240 trou ", nullptr));
        groupBoxActivitesExtraScolaires->setTitle(QCoreApplication::translate("Interface5", "Activit\303\251 extra-scolaire ", nullptr));
        pushButtonSuivant->setText(QCoreApplication::translate("Interface5", "Suivant ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface5: public Ui_Interface5 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE5_H
