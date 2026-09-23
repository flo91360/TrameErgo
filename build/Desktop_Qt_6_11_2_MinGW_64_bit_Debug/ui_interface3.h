/********************************************************************************
** Form generated from reading UI file 'interface3.ui'
**
** Created by: Qt User Interface Compiler version 6.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE3_H
#define UI_INTERFACE3_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Interface3
{
public:
    QGroupBox *groupBoxDifficultesClasse;
    QCheckBox *checkBoxEcritureQualite;
    QCheckBox *checkBoxEcritureQuantite;
    QCheckBox *checkBoxEcritureQualiteQuantite;
    QCheckBox *checkBoxDCConcentration;
    QCheckBox *checkBoxMathematiquesCalcul;
    QCheckBox *checkBoxMathematiquesCalculGeometrie;
    QCheckBox *checkBoxMathematiquesGeometrie;
    QCheckBox *checkBoxOrganiser;
    QCheckBox *checkBoxFaireDevoirs;
    QGroupBox *groupBoxMatieresPreferees;
    QCheckBox *checkBoxPrefereEPS;
    QCheckBox *checkBoxPrefereSVT;
    QCheckBox *checkBoxPrefereTechnologie;
    QCheckBox *checkBoxPrefereHistoireGeographie;
    QCheckBox *checkBoxPrefereFrancais;
    QCheckBox *checkBoxPrefereMusique;
    QCheckBox *checkBoxPrefereArtsPlastique;
    QCheckBox *checkBoxPrefereAnglais;
    QCheckBox *checkBoxPrefereEspagnol;
    QCheckBox *checkBoxPrefereLangues;
    QCheckBox *checkBoxPrefereMathematiques;
    QCheckBox *checkBoxPreferePhysiqueChimie;
    QLabel *labelAutreMatierePrefere;
    QLineEdit *lineEditMatierePrefere;
    QGroupBox *groupBoxComportementClasse;
    QCheckBox *checkBoxCCDifficultesConcentrer;
    QCheckBox *checkBoxConcentreBien;
    QCheckBox *checkBoxConcentrationFluctuente;
    QCheckBox *checkBoxBavardage;
    QCheckBox *checkBoxTravailNonAutonome;
    QCheckBox *checkBoxParticipeBien;
    QCheckBox *checkBoxParticipePas;
    QCheckBox *checkBoxParticipeSelonMatiere;
    QGroupBox *groupBoxMatieresDetestees;
    QCheckBox *checkBoxDetesteEPS;
    QCheckBox *checkBoxDetesteSVT;
    QCheckBox *checkBoxDetesteTechnologie;
    QCheckBox *checkBoxDetesteHistoireGeo;
    QCheckBox *checkBoxDetesteFrancais;
    QCheckBox *checkBoxDetesteMusique;
    QCheckBox *checkBoxDetesteArtsPlastique;
    QCheckBox *checkBoxDetesteAnglais;
    QCheckBox *checkBoxDetesteEspagnol;
    QCheckBox *checkBoxDetesteLangues;
    QCheckBox *checkBoxDetesteMathematiques;
    QCheckBox *checkBoxDetestePhysiqueChimie;
    QLabel *labelAutresMatiereDeteste;
    QLineEdit *lineEditMatiereDeteste;
    QPushButton *pushButtonSuivant;

    void setupUi(QDialog *Interface3)
    {
        if (Interface3->objectName().isEmpty())
            Interface3->setObjectName("Interface3");
        Interface3->resize(612, 453);
        groupBoxDifficultesClasse = new QGroupBox(Interface3);
        groupBoxDifficultesClasse->setObjectName("groupBoxDifficultesClasse");
        groupBoxDifficultesClasse->setGeometry(QRect(20, 120, 571, 91));
        checkBoxEcritureQualite = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxEcritureQualite->setObjectName("checkBoxEcritureQualite");
        checkBoxEcritureQualite->setGeometry(QRect(10, 20, 131, 20));
        checkBoxEcritureQuantite = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxEcritureQuantite->setObjectName("checkBoxEcritureQuantite");
        checkBoxEcritureQuantite->setGeometry(QRect(10, 40, 131, 20));
        checkBoxEcritureQualiteQuantite = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxEcritureQualiteQuantite->setObjectName("checkBoxEcritureQualiteQuantite");
        checkBoxEcritureQualiteQuantite->setGeometry(QRect(10, 60, 191, 20));
        checkBoxDCConcentration = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxDCConcentration->setObjectName("checkBoxDCConcentration");
        checkBoxDCConcentration->setGeometry(QRect(150, 20, 111, 20));
        checkBoxMathematiquesCalcul = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxMathematiquesCalcul->setObjectName("checkBoxMathematiquesCalcul");
        checkBoxMathematiquesCalcul->setGeometry(QRect(150, 40, 161, 20));
        checkBoxMathematiquesCalculGeometrie = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxMathematiquesCalculGeometrie->setObjectName("checkBoxMathematiquesCalculGeometrie");
        checkBoxMathematiquesCalculGeometrie->setGeometry(QRect(200, 60, 231, 20));
        checkBoxMathematiquesGeometrie = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxMathematiquesGeometrie->setObjectName("checkBoxMathematiquesGeometrie");
        checkBoxMathematiquesGeometrie->setGeometry(QRect(330, 40, 191, 20));
        checkBoxOrganiser = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxOrganiser->setObjectName("checkBoxOrganiser");
        checkBoxOrganiser->setGeometry(QRect(270, 20, 111, 20));
        checkBoxFaireDevoirs = new QCheckBox(groupBoxDifficultesClasse);
        checkBoxFaireDevoirs->setObjectName("checkBoxFaireDevoirs");
        checkBoxFaireDevoirs->setGeometry(QRect(390, 20, 111, 20));
        groupBoxMatieresPreferees = new QGroupBox(Interface3);
        groupBoxMatieresPreferees->setObjectName("groupBoxMatieresPreferees");
        groupBoxMatieresPreferees->setGeometry(QRect(20, 220, 571, 91));
        checkBoxPrefereEPS = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereEPS->setObjectName("checkBoxPrefereEPS");
        checkBoxPrefereEPS->setGeometry(QRect(10, 20, 41, 20));
        checkBoxPrefereSVT = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereSVT->setObjectName("checkBoxPrefereSVT");
        checkBoxPrefereSVT->setGeometry(QRect(10, 40, 76, 20));
        checkBoxPrefereTechnologie = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereTechnologie->setObjectName("checkBoxPrefereTechnologie");
        checkBoxPrefereTechnologie->setGeometry(QRect(10, 60, 91, 20));
        checkBoxPrefereHistoireGeographie = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereHistoireGeographie->setObjectName("checkBoxPrefereHistoireGeographie");
        checkBoxPrefereHistoireGeographie->setGeometry(QRect(70, 20, 141, 20));
        checkBoxPrefereFrancais = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereFrancais->setObjectName("checkBoxPrefereFrancais");
        checkBoxPrefereFrancais->setGeometry(QRect(70, 40, 76, 20));
        checkBoxPrefereMusique = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereMusique->setObjectName("checkBoxPrefereMusique");
        checkBoxPrefereMusique->setGeometry(QRect(100, 60, 76, 20));
        checkBoxPrefereArtsPlastique = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereArtsPlastique->setObjectName("checkBoxPrefereArtsPlastique");
        checkBoxPrefereArtsPlastique->setGeometry(QRect(190, 60, 91, 20));
        checkBoxPrefereAnglais = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereAnglais->setObjectName("checkBoxPrefereAnglais");
        checkBoxPrefereAnglais->setGeometry(QRect(150, 40, 76, 20));
        checkBoxPrefereEspagnol = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereEspagnol->setObjectName("checkBoxPrefereEspagnol");
        checkBoxPrefereEspagnol->setGeometry(QRect(220, 40, 76, 20));
        checkBoxPrefereLangues = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereLangues->setObjectName("checkBoxPrefereLangues");
        checkBoxPrefereLangues->setGeometry(QRect(300, 40, 81, 20));
        checkBoxPrefereMathematiques = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPrefereMathematiques->setObjectName("checkBoxPrefereMathematiques");
        checkBoxPrefereMathematiques->setGeometry(QRect(210, 20, 111, 20));
        checkBoxPreferePhysiqueChimie = new QCheckBox(groupBoxMatieresPreferees);
        checkBoxPreferePhysiqueChimie->setObjectName("checkBoxPreferePhysiqueChimie");
        checkBoxPreferePhysiqueChimie->setGeometry(QRect(330, 20, 121, 20));
        labelAutreMatierePrefere = new QLabel(groupBoxMatieresPreferees);
        labelAutreMatierePrefere->setObjectName("labelAutreMatierePrefere");
        labelAutreMatierePrefere->setGeometry(QRect(290, 60, 49, 16));
        lineEditMatierePrefere = new QLineEdit(groupBoxMatieresPreferees);
        lineEditMatierePrefere->setObjectName("lineEditMatierePrefere");
        lineEditMatierePrefere->setGeometry(QRect(340, 60, 113, 22));
        groupBoxComportementClasse = new QGroupBox(Interface3);
        groupBoxComportementClasse->setObjectName("groupBoxComportementClasse");
        groupBoxComportementClasse->setGeometry(QRect(20, 20, 571, 81));
        checkBoxCCDifficultesConcentrer = new QCheckBox(groupBoxComportementClasse);
        checkBoxCCDifficultesConcentrer->setObjectName("checkBoxCCDifficultesConcentrer");
        checkBoxCCDifficultesConcentrer->setGeometry(QRect(10, 20, 151, 20));
        checkBoxConcentreBien = new QCheckBox(groupBoxComportementClasse);
        checkBoxConcentreBien->setObjectName("checkBoxConcentreBien");
        checkBoxConcentreBien->setGeometry(QRect(10, 40, 151, 20));
        checkBoxConcentrationFluctuente = new QCheckBox(groupBoxComportementClasse);
        checkBoxConcentrationFluctuente->setObjectName("checkBoxConcentrationFluctuente");
        checkBoxConcentrationFluctuente->setGeometry(QRect(10, 60, 321, 20));
        checkBoxBavardage = new QCheckBox(groupBoxComportementClasse);
        checkBoxBavardage->setObjectName("checkBoxBavardage");
        checkBoxBavardage->setGeometry(QRect(170, 20, 131, 20));
        checkBoxTravailNonAutonome = new QCheckBox(groupBoxComportementClasse);
        checkBoxTravailNonAutonome->setObjectName("checkBoxTravailNonAutonome");
        checkBoxTravailNonAutonome->setGeometry(QRect(170, 40, 271, 20));
        checkBoxParticipeBien = new QCheckBox(groupBoxComportementClasse);
        checkBoxParticipeBien->setObjectName("checkBoxParticipeBien");
        checkBoxParticipeBien->setGeometry(QRect(300, 20, 101, 20));
        checkBoxParticipePas = new QCheckBox(groupBoxComportementClasse);
        checkBoxParticipePas->setObjectName("checkBoxParticipePas");
        checkBoxParticipePas->setGeometry(QRect(400, 20, 121, 20));
        checkBoxParticipeSelonMatiere = new QCheckBox(groupBoxComportementClasse);
        checkBoxParticipeSelonMatiere->setObjectName("checkBoxParticipeSelonMatiere");
        checkBoxParticipeSelonMatiere->setGeometry(QRect(320, 60, 231, 20));
        groupBoxMatieresDetestees = new QGroupBox(Interface3);
        groupBoxMatieresDetestees->setObjectName("groupBoxMatieresDetestees");
        groupBoxMatieresDetestees->setGeometry(QRect(20, 320, 571, 91));
        checkBoxDetesteEPS = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteEPS->setObjectName("checkBoxDetesteEPS");
        checkBoxDetesteEPS->setGeometry(QRect(10, 20, 41, 20));
        checkBoxDetesteSVT = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteSVT->setObjectName("checkBoxDetesteSVT");
        checkBoxDetesteSVT->setGeometry(QRect(10, 40, 76, 20));
        checkBoxDetesteTechnologie = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteTechnologie->setObjectName("checkBoxDetesteTechnologie");
        checkBoxDetesteTechnologie->setGeometry(QRect(10, 60, 91, 20));
        checkBoxDetesteHistoireGeo = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteHistoireGeo->setObjectName("checkBoxDetesteHistoireGeo");
        checkBoxDetesteHistoireGeo->setGeometry(QRect(70, 20, 141, 20));
        checkBoxDetesteFrancais = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteFrancais->setObjectName("checkBoxDetesteFrancais");
        checkBoxDetesteFrancais->setGeometry(QRect(70, 40, 76, 20));
        checkBoxDetesteMusique = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteMusique->setObjectName("checkBoxDetesteMusique");
        checkBoxDetesteMusique->setGeometry(QRect(100, 60, 76, 20));
        checkBoxDetesteArtsPlastique = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteArtsPlastique->setObjectName("checkBoxDetesteArtsPlastique");
        checkBoxDetesteArtsPlastique->setGeometry(QRect(190, 60, 91, 20));
        checkBoxDetesteAnglais = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteAnglais->setObjectName("checkBoxDetesteAnglais");
        checkBoxDetesteAnglais->setGeometry(QRect(150, 40, 76, 20));
        checkBoxDetesteEspagnol = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteEspagnol->setObjectName("checkBoxDetesteEspagnol");
        checkBoxDetesteEspagnol->setGeometry(QRect(220, 40, 76, 20));
        checkBoxDetesteLangues = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteLangues->setObjectName("checkBoxDetesteLangues");
        checkBoxDetesteLangues->setGeometry(QRect(300, 40, 81, 20));
        checkBoxDetesteMathematiques = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetesteMathematiques->setObjectName("checkBoxDetesteMathematiques");
        checkBoxDetesteMathematiques->setGeometry(QRect(210, 20, 111, 20));
        checkBoxDetestePhysiqueChimie = new QCheckBox(groupBoxMatieresDetestees);
        checkBoxDetestePhysiqueChimie->setObjectName("checkBoxDetestePhysiqueChimie");
        checkBoxDetestePhysiqueChimie->setGeometry(QRect(330, 20, 121, 20));
        labelAutresMatiereDeteste = new QLabel(groupBoxMatieresDetestees);
        labelAutresMatiereDeteste->setObjectName("labelAutresMatiereDeteste");
        labelAutresMatiereDeteste->setGeometry(QRect(290, 60, 49, 16));
        lineEditMatiereDeteste = new QLineEdit(groupBoxMatieresDetestees);
        lineEditMatiereDeteste->setObjectName("lineEditMatiereDeteste");
        lineEditMatiereDeteste->setGeometry(QRect(340, 60, 113, 22));
        pushButtonSuivant = new QPushButton(Interface3);
        pushButtonSuivant->setObjectName("pushButtonSuivant");
        pushButtonSuivant->setGeometry(QRect(510, 420, 75, 24));

        retranslateUi(Interface3);

        QMetaObject::connectSlotsByName(Interface3);
    } // setupUi

    void retranslateUi(QDialog *Interface3)
    {
        Interface3->setWindowTitle(QCoreApplication::translate("Interface3", "Dialog", nullptr));
        groupBoxDifficultesClasse->setTitle(QCoreApplication::translate("Interface3", "Difficult\303\251 en classe ", nullptr));
        checkBoxEcritureQualite->setText(QCoreApplication::translate("Interface3", "d'\303\251criture (qualit\303\251)", nullptr));
        checkBoxEcritureQuantite->setText(QCoreApplication::translate("Interface3", "d'\303\251criture (quantit\303\251)", nullptr));
        checkBoxEcritureQualiteQuantite->setText(QCoreApplication::translate("Interface3", "d'\303\251criture (qualit\303\251 et quantit\303\251)", nullptr));
        checkBoxDCConcentration->setText(QCoreApplication::translate("Interface3", "de concentration ", nullptr));
        checkBoxMathematiquesCalcul->setText(QCoreApplication::translate("Interface3", "en math\303\251matiques (calcul)", nullptr));
        checkBoxMathematiquesCalculGeometrie->setText(QCoreApplication::translate("Interface3", "en math\303\251matiques (calcul et g\303\251om\303\251trie)", nullptr));
        checkBoxMathematiquesGeometrie->setText(QCoreApplication::translate("Interface3", "en math\303\251matiques (g\303\251om\303\251trie)", nullptr));
        checkBoxOrganiser->setText(QCoreApplication::translate("Interface3", "pour s'organiser", nullptr));
        checkBoxFaireDevoirs->setText(QCoreApplication::translate("Interface3", "faire ses devoirs", nullptr));
        groupBoxMatieresPreferees->setTitle(QCoreApplication::translate("Interface3", "Mati\303\250re(s) pr\303\251f\303\251r\303\251e(s)", nullptr));
        checkBoxPrefereEPS->setText(QCoreApplication::translate("Interface3", "EPS", nullptr));
        checkBoxPrefereSVT->setText(QCoreApplication::translate("Interface3", "SVT", nullptr));
        checkBoxPrefereTechnologie->setText(QCoreApplication::translate("Interface3", "Technologie", nullptr));
        checkBoxPrefereHistoireGeographie->setText(QCoreApplication::translate("Interface3", "Histoire-g\303\251ographie", nullptr));
        checkBoxPrefereFrancais->setText(QCoreApplication::translate("Interface3", "Fran\303\247ais ", nullptr));
        checkBoxPrefereMusique->setText(QCoreApplication::translate("Interface3", "Musique ", nullptr));
        checkBoxPrefereArtsPlastique->setText(QCoreApplication::translate("Interface3", "Art plastique", nullptr));
        checkBoxPrefereAnglais->setText(QCoreApplication::translate("Interface3", "Anglais", nullptr));
        checkBoxPrefereEspagnol->setText(QCoreApplication::translate("Interface3", "Espagnol", nullptr));
        checkBoxPrefereLangues->setText(QCoreApplication::translate("Interface3", "Les langues", nullptr));
        checkBoxPrefereMathematiques->setText(QCoreApplication::translate("Interface3", "Math\303\251matiques ", nullptr));
        checkBoxPreferePhysiqueChimie->setText(QCoreApplication::translate("Interface3", "Physique - chimie", nullptr));
        labelAutreMatierePrefere->setText(QCoreApplication::translate("Interface3", "Autre :", nullptr));
        groupBoxComportementClasse->setTitle(QCoreApplication::translate("Interface3", "Comportement en classe : ", nullptr));
        checkBoxCCDifficultesConcentrer->setText(QCoreApplication::translate("Interface3", "Difficult\303\251 \303\240 se concentrer", nullptr));
        checkBoxConcentreBien->setText(QCoreApplication::translate("Interface3", "Se concentre bien ", nullptr));
        checkBoxConcentrationFluctuente->setText(QCoreApplication::translate("Interface3", "La concentration est fluctuante au cours de la journ\303\251e ", nullptr));
        checkBoxBavardage->setText(QCoreApplication::translate("Interface3", "Bavardage en cours", nullptr));
        checkBoxTravailNonAutonome->setText(QCoreApplication::translate("Interface3", "Ne se met pas au travail de mani\303\250re autonome", nullptr));
        checkBoxParticipeBien->setText(QCoreApplication::translate("Interface3", "Participe bien ", nullptr));
        checkBoxParticipePas->setText(QCoreApplication::translate("Interface3", "Ne participe pas", nullptr));
        checkBoxParticipeSelonMatiere->setText(QCoreApplication::translate("Interface3", "Participation d\303\251pendante de la mati\303\250re", nullptr));
        groupBoxMatieresDetestees->setTitle(QCoreApplication::translate("Interface3", "Mati\303\250res les moins appr\303\251ci\303\251es :", nullptr));
        checkBoxDetesteEPS->setText(QCoreApplication::translate("Interface3", "EPS", nullptr));
        checkBoxDetesteSVT->setText(QCoreApplication::translate("Interface3", "SVT", nullptr));
        checkBoxDetesteTechnologie->setText(QCoreApplication::translate("Interface3", "Technologie", nullptr));
        checkBoxDetesteHistoireGeo->setText(QCoreApplication::translate("Interface3", "Histoire-g\303\251ographie", nullptr));
        checkBoxDetesteFrancais->setText(QCoreApplication::translate("Interface3", "Fran\303\247ais ", nullptr));
        checkBoxDetesteMusique->setText(QCoreApplication::translate("Interface3", "Musique ", nullptr));
        checkBoxDetesteArtsPlastique->setText(QCoreApplication::translate("Interface3", "Art plastique", nullptr));
        checkBoxDetesteAnglais->setText(QCoreApplication::translate("Interface3", "Anglais", nullptr));
        checkBoxDetesteEspagnol->setText(QCoreApplication::translate("Interface3", "Espagnol", nullptr));
        checkBoxDetesteLangues->setText(QCoreApplication::translate("Interface3", "Les langues", nullptr));
        checkBoxDetesteMathematiques->setText(QCoreApplication::translate("Interface3", "Math\303\251matiques ", nullptr));
        checkBoxDetestePhysiqueChimie->setText(QCoreApplication::translate("Interface3", "Physique -chimie", nullptr));
        labelAutresMatiereDeteste->setText(QCoreApplication::translate("Interface3", "Autre :", nullptr));
        pushButtonSuivant->setText(QCoreApplication::translate("Interface3", "Suivant ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Interface3: public Ui_Interface3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE3_H
