/********************************************************************************
** Form generated from reading UI file 'interface1.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE1_H
#define UI_INTERFACE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_Interface1
{
public:
    QGroupBox *groupBoxEntente;
    QRadioButton *radioButtonNeutreEntente;
    QRadioButton *radioButtonMauvaiseEntenre;
    QRadioButton *radioButtonBonneEntente;
    QLabel *labelEntente;
    QPushButton *pushButtonSuivant;
    QLabel *labelModeGarde;
    QLabel *labelNomEtablissement;
    QLineEdit *lineEditNomEtablissement;
    QLineEdit *lineEditNom;
    QLabel *labelFraterie;
    QRadioButton *radioButtonEnfantUnique;
    QLabel *labelPrenom;
    QLabel *labelLateralite;
    QLineEdit *lineEditPrenom;
    QLineEdit *lineEditMedecinTraitant;
    QComboBox *comboBoxClasse;
    QLabel *labelVille;
    QLabel *labelDateNaissance;
    QComboBox *comboBoxLateralite;
    QDateEdit *dateEditNaissance;
    QLineEdit *lineEditFraterie;
    QComboBox *comboBoxTypeEtablissement;
    QComboBox *comboBoxModeGarde;
    QLabel *labelClasse;
    QLabel *labelNom;
    QLineEdit *lineEditVille;
    QLabel *labelMedecin;

    void setupUi(QDialog *Interface1)
    {
        if (Interface1->objectName().isEmpty())
            Interface1->setObjectName("Interface1");
        Interface1->resize(670, 298);
        groupBoxEntente = new QGroupBox(Interface1);
        groupBoxEntente->setObjectName("groupBoxEntente");
        groupBoxEntente->setGeometry(QRect(70, 120, 231, 31));
        radioButtonNeutreEntente = new QRadioButton(groupBoxEntente);
        radioButtonNeutreEntente->setObjectName("radioButtonNeutreEntente");
        radioButtonNeutreEntente->setGeometry(QRect(160, 10, 69, 18));
        radioButtonMauvaiseEntenre = new QRadioButton(groupBoxEntente);
        radioButtonMauvaiseEntenre->setObjectName("radioButtonMauvaiseEntenre");
        radioButtonMauvaiseEntenre->setGeometry(QRect(80, 10, 81, 18));
        radioButtonBonneEntente = new QRadioButton(groupBoxEntente);
        radioButtonBonneEntente->setObjectName("radioButtonBonneEntente");
        radioButtonBonneEntente->setGeometry(QRect(10, 10, 71, 18));
        radioButtonBonneEntente->setChecked(true);
        labelEntente = new QLabel(Interface1);
        labelEntente->setObjectName("labelEntente");
        labelEntente->setGeometry(QRect(10, 130, 61, 16));
        pushButtonSuivant = new QPushButton(Interface1);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(460, 120, 141, 41));
        labelModeGarde = new QLabel(Interface1);
        labelModeGarde->setObjectName("labelModeGarde");
        labelModeGarde->setGeometry(QRect(10, 170, 111, 16));
        labelNomEtablissement = new QLabel(Interface1);
        labelNomEtablissement->setObjectName("labelNomEtablissement");
        labelNomEtablissement->setGeometry(QRect(190, 210, 121, 16));
        lineEditNomEtablissement = new QLineEdit(Interface1);
        lineEditNomEtablissement->setObjectName("lineEditNomEtablissement");
        lineEditNomEtablissement->setGeometry(QRect(410, 210, 113, 20));
        lineEditNom = new QLineEdit(Interface1);
        lineEditNom->setObjectName("lineEditNom");
        lineEditNom->setGeometry(QRect(260, 10, 113, 22));
        labelFraterie = new QLabel(Interface1);
        labelFraterie->setObjectName("labelFraterie");
        labelFraterie->setGeometry(QRect(10, 90, 61, 16));
        radioButtonEnfantUnique = new QRadioButton(Interface1);
        radioButtonEnfantUnique->setObjectName("radioButtonEnfantUnique");
        radioButtonEnfantUnique->setGeometry(QRect(220, 90, 111, 20));
        labelPrenom = new QLabel(Interface1);
        labelPrenom->setObjectName("labelPrenom");
        labelPrenom->setGeometry(QRect(20, 10, 49, 16));
        labelLateralite = new QLabel(Interface1);
        labelLateralite->setObjectName("labelLateralite");
        labelLateralite->setGeometry(QRect(270, 50, 61, 16));
        lineEditPrenom = new QLineEdit(Interface1);
        lineEditPrenom->setObjectName("lineEditPrenom");
        lineEditPrenom->setGeometry(QRect(80, 10, 113, 22));
        lineEditMedecinTraitant = new QLineEdit(Interface1);
        lineEditMedecinTraitant->setObjectName("lineEditMedecinTraitant");
        lineEditMedecinTraitant->setGeometry(QRect(120, 250, 113, 20));
        comboBoxClasse = new QComboBox(Interface1);
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->addItem(QString());
        comboBoxClasse->setObjectName("comboBoxClasse");
        comboBoxClasse->setGeometry(QRect(60, 210, 101, 22));
        labelVille = new QLabel(Interface1);
        labelVille->setObjectName("labelVille");
        labelVille->setGeometry(QRect(270, 250, 37, 12));
        labelDateNaissance = new QLabel(Interface1);
        labelDateNaissance->setObjectName("labelDateNaissance");
        labelDateNaissance->setGeometry(QRect(10, 50, 101, 16));
        comboBoxLateralite = new QComboBox(Interface1);
        comboBoxLateralite->addItem(QString());
        comboBoxLateralite->addItem(QString());
        comboBoxLateralite->addItem(QString());
        comboBoxLateralite->setObjectName("comboBoxLateralite");
        comboBoxLateralite->setGeometry(QRect(330, 50, 69, 22));
        dateEditNaissance = new QDateEdit(Interface1);
        dateEditNaissance->setObjectName("dateEditNaissance");
        dateEditNaissance->setGeometry(QRect(130, 50, 110, 22));
        dateEditNaissance->setDateTime(QDateTime(QDate(1995, 10, 19), QTime(13, 0, 0)));
        lineEditFraterie = new QLineEdit(Interface1);
        lineEditFraterie->setObjectName("lineEditFraterie");
        lineEditFraterie->setGeometry(QRect(70, 90, 111, 20));
        comboBoxTypeEtablissement = new QComboBox(Interface1);
        comboBoxTypeEtablissement->addItem(QString());
        comboBoxTypeEtablissement->addItem(QString());
        comboBoxTypeEtablissement->addItem(QString());
        comboBoxTypeEtablissement->setObjectName("comboBoxTypeEtablissement");
        comboBoxTypeEtablissement->setGeometry(QRect(320, 210, 69, 21));
        comboBoxModeGarde = new QComboBox(Interface1);
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->addItem(QString());
        comboBoxModeGarde->setObjectName("comboBoxModeGarde");
        comboBoxModeGarde->setGeometry(QRect(110, 170, 171, 22));
        labelClasse = new QLabel(Interface1);
        labelClasse->setObjectName("labelClasse");
        labelClasse->setGeometry(QRect(10, 210, 51, 16));
        labelNom = new QLabel(Interface1);
        labelNom->setObjectName("labelNom");
        labelNom->setGeometry(QRect(210, 10, 49, 16));
        lineEditVille = new QLineEdit(Interface1);
        lineEditVille->setObjectName("lineEditVille");
        lineEditVille->setGeometry(QRect(320, 250, 113, 20));
        labelMedecin = new QLabel(Interface1);
        labelMedecin->setObjectName("labelMedecin");
        labelMedecin->setGeometry(QRect(10, 250, 101, 16));

        retranslateUi(Interface1);

        QMetaObject::connectSlotsByName(Interface1);
    } // setupUi

    void retranslateUi(QDialog *Interface1)
    {
        Interface1->setWindowTitle(QCoreApplication::translate("Interface1", "Dialog", nullptr));
        groupBoxEntente->setTitle(QString());
        radioButtonNeutreEntente->setText(QCoreApplication::translate("Interface1", "Neutre", nullptr));
        radioButtonMauvaiseEntenre->setText(QCoreApplication::translate("Interface1", "Mauvaise", nullptr));
        radioButtonBonneEntente->setText(QCoreApplication::translate("Interface1", "Bonne", nullptr));
        labelEntente->setText(QCoreApplication::translate("Interface1", "Entente : ", nullptr));
        pushButtonSuivant->setText(QCoreApplication::translate("Interface1", "Suivant", nullptr));
        labelModeGarde->setText(QCoreApplication::translate("Interface1", "Mode de garde :", nullptr));
        labelNomEtablissement->setText(QCoreApplication::translate("Interface1", "Nom d'\303\251tablissement :", nullptr));
        lineEditNomEtablissement->setText(QCoreApplication::translate("Interface1", "Emile Bouton", nullptr));
        lineEditNom->setText(QCoreApplication::translate("Interface1", "GAUDON", nullptr));
        labelFraterie->setText(QCoreApplication::translate("Interface1", "Fraterie : ", nullptr));
        radioButtonEnfantUnique->setText(QCoreApplication::translate("Interface1", "Enfant unique", nullptr));
        labelPrenom->setText(QCoreApplication::translate("Interface1", "Pr\303\251nom :", nullptr));
        labelLateralite->setText(QCoreApplication::translate("Interface1", "Lat\303\251ralit\303\251 :", nullptr));
        lineEditPrenom->setText(QCoreApplication::translate("Interface1", "Florian", nullptr));
        lineEditMedecinTraitant->setText(QCoreApplication::translate("Interface1", "Rom\303\251as", nullptr));
        comboBoxClasse->setItemText(0, QCoreApplication::translate("Interface1", "petite section", nullptr));
        comboBoxClasse->setItemText(1, QCoreApplication::translate("Interface1", "moyenne section", nullptr));
        comboBoxClasse->setItemText(2, QCoreApplication::translate("Interface1", "grande section ", nullptr));
        comboBoxClasse->setItemText(3, QCoreApplication::translate("Interface1", "CP", nullptr));
        comboBoxClasse->setItemText(4, QCoreApplication::translate("Interface1", "CE1", nullptr));
        comboBoxClasse->setItemText(5, QCoreApplication::translate("Interface1", "CE2", nullptr));
        comboBoxClasse->setItemText(6, QCoreApplication::translate("Interface1", "CM1", nullptr));
        comboBoxClasse->setItemText(7, QCoreApplication::translate("Interface1", "CM2", nullptr));
        comboBoxClasse->setItemText(8, QCoreApplication::translate("Interface1", "6\303\250me", nullptr));
        comboBoxClasse->setItemText(9, QCoreApplication::translate("Interface1", "5\303\250me", nullptr));
        comboBoxClasse->setItemText(10, QCoreApplication::translate("Interface1", "4\303\250me", nullptr));
        comboBoxClasse->setItemText(11, QCoreApplication::translate("Interface1", "3\303\250me", nullptr));
        comboBoxClasse->setItemText(12, QCoreApplication::translate("Interface1", "2nd", nullptr));
        comboBoxClasse->setItemText(13, QCoreApplication::translate("Interface1", "1\303\250re", nullptr));
        comboBoxClasse->setItemText(14, QCoreApplication::translate("Interface1", "Terminal ", nullptr));
        comboBoxClasse->setItemText(15, QCoreApplication::translate("Interface1", "post BAC", nullptr));

        comboBoxClasse->setCurrentText(QCoreApplication::translate("Interface1", "petite section", nullptr));
        labelVille->setText(QCoreApplication::translate("Interface1", "Ville :", nullptr));
        labelDateNaissance->setText(QCoreApplication::translate("Interface1", "Date de naissance : ", nullptr));
        comboBoxLateralite->setItemText(0, QCoreApplication::translate("Interface1", "droiti\303\250re", nullptr));
        comboBoxLateralite->setItemText(1, QCoreApplication::translate("Interface1", "gauch\303\250re", nullptr));
        comboBoxLateralite->setItemText(2, QCoreApplication::translate("Interface1", "ambidextre", nullptr));

        lineEditFraterie->setText(QCoreApplication::translate("Interface1", "1fr\303\250re,1soeur", nullptr));
        comboBoxTypeEtablissement->setItemText(0, QCoreApplication::translate("Interface1", "l'\303\251cole", nullptr));
        comboBoxTypeEtablissement->setItemText(1, QCoreApplication::translate("Interface1", "le coll\303\250ge", nullptr));
        comboBoxTypeEtablissement->setItemText(2, QCoreApplication::translate("Interface1", "le lyc\303\251e", nullptr));

        comboBoxModeGarde->setItemText(0, QCoreApplication::translate("Interface1", "avec ses 2 parents", nullptr));
        comboBoxModeGarde->setItemText(1, QCoreApplication::translate("Interface1", "avec son p\303\250re", nullptr));
        comboBoxModeGarde->setItemText(2, QCoreApplication::translate("Interface1", "avec sa m\303\250re", nullptr));
        comboBoxModeGarde->setItemText(3, QCoreApplication::translate("Interface1", "en garde altern\303\251e", nullptr));
        comboBoxModeGarde->setItemText(4, QCoreApplication::translate("Interface1", "une semaine chez chaque parent", nullptr));
        comboBoxModeGarde->setItemText(5, QCoreApplication::translate("Interface1", "la semaine chez sa m\303\250re et un week-end sur deux chez son p\303\250re", nullptr));
        comboBoxModeGarde->setItemText(6, QCoreApplication::translate("Interface1", "la semaine chez son p\303\250re et un week-end sur deux chez sa m\303\250re", nullptr));
        comboBoxModeGarde->setItemText(7, QCoreApplication::translate("Interface1", "en foyer", nullptr));

        labelClasse->setText(QCoreApplication::translate("Interface1", "Classe :", nullptr));
        labelNom->setText(QCoreApplication::translate("Interface1", "Nom :", nullptr));
        lineEditVille->setText(QCoreApplication::translate("Interface1", "VSO", nullptr));
        labelMedecin->setText(QCoreApplication::translate("Interface1", "M\303\251decin traitant :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface1: public Ui_Interface1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE1_H
