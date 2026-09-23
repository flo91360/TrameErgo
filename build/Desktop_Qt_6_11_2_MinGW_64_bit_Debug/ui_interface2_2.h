/********************************************************************************
** Form generated from reading UI file 'interface2_2.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE2_2_H
#define UI_INTERFACE2_2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface2_2
{
public:
    QGroupBox *groupBoxProfessionnels;
    QCheckBox *checkBoxPsychomotricien;
    QCheckBox *checkBoxOrthophoniste;
    QCheckBox *checkBoxOrthopiste;
    QCheckBox *checkBoxPsychologue;
    QCheckBox *checkBoxNeuropsychologue;
    QCheckBox *checkBoxKinesiterapeute;
    QCheckBox *checkBoxAucun;
    QWidget *formLayoutWidget;
    QFormLayout *formLayoutSuivi;
    QPushButton *pushButtonSuivant;

    void setupUi(QDialog *Interface2_2)
    {
        if (Interface2_2->objectName().isEmpty())
            Interface2_2->setObjectName("Interface2_2");
        Interface2_2->resize(500, 357);
        groupBoxProfessionnels = new QGroupBox(Interface2_2);
        groupBoxProfessionnels->setObjectName("groupBoxProfessionnels");
        groupBoxProfessionnels->setGeometry(QRect(20, 20, 431, 81));
        checkBoxPsychomotricien = new QCheckBox(groupBoxProfessionnels);
        checkBoxPsychomotricien->setObjectName("checkBoxPsychomotricien");
        checkBoxPsychomotricien->setGeometry(QRect(20, 20, 133, 20));
        checkBoxOrthophoniste = new QCheckBox(groupBoxProfessionnels);
        checkBoxOrthophoniste->setObjectName("checkBoxOrthophoniste");
        checkBoxOrthophoniste->setGeometry(QRect(20, 40, 98, 20));
        checkBoxOrthopiste = new QCheckBox(groupBoxProfessionnels);
        checkBoxOrthopiste->setObjectName("checkBoxOrthopiste");
        checkBoxOrthopiste->setGeometry(QRect(160, 40, 84, 20));
        checkBoxPsychologue = new QCheckBox(groupBoxProfessionnels);
        checkBoxPsychologue->setObjectName("checkBoxPsychologue");
        checkBoxPsychologue->setGeometry(QRect(160, 20, 91, 20));
        checkBoxNeuropsychologue = new QCheckBox(groupBoxProfessionnels);
        checkBoxNeuropsychologue->setObjectName("checkBoxNeuropsychologue");
        checkBoxNeuropsychologue->setGeometry(QRect(280, 20, 122, 20));
        checkBoxKinesiterapeute = new QCheckBox(groupBoxProfessionnels);
        checkBoxKinesiterapeute->setObjectName("checkBoxKinesiterapeute");
        checkBoxKinesiterapeute->setGeometry(QRect(280, 40, 110, 20));
        checkBoxAucun = new QCheckBox(groupBoxProfessionnels);
        checkBoxAucun->setObjectName("checkBoxAucun");
        checkBoxAucun->setGeometry(QRect(280, 60, 76, 20));
        formLayoutWidget = new QWidget(Interface2_2);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 120, 451, 196));
        formLayoutSuivi = new QFormLayout(formLayoutWidget);
        formLayoutSuivi->setObjectName("formLayoutSuivi");
        formLayoutSuivi->setContentsMargins(0, 0, 0, 0);
        pushButtonSuivant = new QPushButton(Interface2_2);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(400, 320, 75, 24));

        retranslateUi(Interface2_2);

        QMetaObject::connectSlotsByName(Interface2_2);
    } // setupUi

    void retranslateUi(QDialog *Interface2_2)
    {
        Interface2_2->setWindowTitle(QCoreApplication::translate("Interface2_2", "Dialog", nullptr));
        groupBoxProfessionnels->setTitle(QCoreApplication::translate("Interface2_2", "professionnels autour du patient :", nullptr));
        checkBoxPsychomotricien->setText(QCoreApplication::translate("Interface2_2", "psychomotricien(ne)", nullptr));
        checkBoxOrthophoniste->setText(QCoreApplication::translate("Interface2_2", "orthophoniste", nullptr));
        checkBoxOrthopiste->setText(QCoreApplication::translate("Interface2_2", "orthoptiste ", nullptr));
        checkBoxPsychologue->setText(QCoreApplication::translate("Interface2_2", "psychologue", nullptr));
        checkBoxNeuropsychologue->setText(QCoreApplication::translate("Interface2_2", "neuropsychologue", nullptr));
        checkBoxKinesiterapeute->setText(QCoreApplication::translate("Interface2_2", "kin\303\251sith\303\251rapeute", nullptr));
        checkBoxAucun->setText(QCoreApplication::translate("Interface2_2", "aucun", nullptr));
        pushButtonSuivant->setText(QCoreApplication::translate("Interface2_2", "Suivant ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface2_2: public Ui_Interface2_2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE2_2_H
