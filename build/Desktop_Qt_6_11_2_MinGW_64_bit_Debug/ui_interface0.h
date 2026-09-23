/********************************************************************************
** Form generated from reading UI file 'interface0.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE0_H
#define UI_INTERFACE0_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Interface0
{
public:
    QGroupBox *groupBoxNomFichier;
    QRadioButton *radioButtonEnfant;
    QRadioButton *radioButtonAdolescent;
    QRadioButton *radioButtonAdulte;
    QComboBox *comboBoxSexe;
    QPushButton *pushButtonSuivant;
    QLabel *labelSexe;

    void setupUi(QDialog *Interface0)
    {
        if (Interface0->objectName().isEmpty())
            Interface0->setObjectName("Interface0");
        Interface0->resize(607, 322);
        groupBoxNomFichier = new QGroupBox(Interface0);
        groupBoxNomFichier->setObjectName("groupBoxNomFichier");
        groupBoxNomFichier->setGeometry(QRect(90, 130, 351, 81));
        radioButtonEnfant = new QRadioButton(groupBoxNomFichier);
        radioButtonEnfant->setObjectName("radioButtonEnfant");
        radioButtonEnfant->setGeometry(QRect(10, 20, 201, 18));
        radioButtonEnfant->setChecked(true);
        radioButtonAdolescent = new QRadioButton(groupBoxNomFichier);
        radioButtonAdolescent->setObjectName("radioButtonAdolescent");
        radioButtonAdolescent->setGeometry(QRect(10, 40, 221, 18));
        radioButtonAdulte = new QRadioButton(groupBoxNomFichier);
        radioButtonAdulte->setObjectName("radioButtonAdulte");
        radioButtonAdulte->setGeometry(QRect(10, 60, 171, 18));
        comboBoxSexe = new QComboBox(Interface0);
        comboBoxSexe->addItem(QString());
        comboBoxSexe->addItem(QString());
        comboBoxSexe->setObjectName("comboBoxSexe");
        comboBoxSexe->setGeometry(QRect(160, 80, 91, 22));
        pushButtonSuivant = new QPushButton(Interface0);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(440, 240, 75, 24));
        labelSexe = new QLabel(Interface0);
        labelSexe->setObjectName("labelSexe");
        labelSexe->setGeometry(QRect(100, 80, 49, 16));

        retranslateUi(Interface0);

        QMetaObject::connectSlotsByName(Interface0);
    } // setupUi

    void retranslateUi(QDialog *Interface0)
    {
        Interface0->setWindowTitle(QCoreApplication::translate("Interface0", "Dialog", nullptr));
        groupBoxNomFichier->setTitle(QCoreApplication::translate("Interface0", "Nom de ficher : ", nullptr));
        radioButtonEnfant->setText(QCoreApplication::translate("Interface0", "Bilan_ergoth\303\251rapie_enfant ", nullptr));
        radioButtonAdolescent->setText(QCoreApplication::translate("Interface0", "Bilan_ergoth\303\251rapie_adolescent", nullptr));
        radioButtonAdulte->setText(QCoreApplication::translate("Interface0", "Bilan_ergoth\303\251rapie_adulte", nullptr));
        comboBoxSexe->setItemText(0, QCoreApplication::translate("Interface0", "Femme", nullptr));
        comboBoxSexe->setItemText(1, QCoreApplication::translate("Interface0", "Homme", nullptr));

        pushButtonSuivant->setText(QCoreApplication::translate("Interface0", "Suivant", nullptr));
        labelSexe->setText(QCoreApplication::translate("Interface0", "Sexe :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface0: public Ui_Interface0 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE0_H
