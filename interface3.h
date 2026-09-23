#ifndef INTERFACE3_H
#define INTERFACE3_H

#include <QDialog>

namespace Ui {
class Interface3;
}

class Interface3 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface3(QWidget *parent = nullptr);
    ~Interface3();

private slots:
    void on_checkBoxCCDifficultesConcentrer_stateChanged(int arg1);

    void on_checkBoxBavardage_stateChanged(int arg1);

    void on_checkBoxParticipeBien_stateChanged(int arg1);

    void on_checkBoxParticipePas_stateChanged(int arg1);

    void on_checkBoxConcentreBien_stateChanged(int arg1);

    void on_checkBoxTravailNonAutonome_stateChanged(int arg1);

    void on_checkBoxConcentrationFluctuente_stateChanged(int arg1);

    void on_checkBoxParticipeSelonMatiere_stateChanged(int arg1);

    void on_checkBoxEcritureQualite_stateChanged(int arg1);

    void on_checkBoxDCConcentration_stateChanged(int arg1);

    void on_checkBoxOrganiser_stateChanged(int arg1);

    void on_checkBoxFaireDevoirs_stateChanged(int arg1);

    void on_checkBoxEcritureQuantite_stateChanged(int arg1);

    void on_checkBoxMathematiquesCalcul_stateChanged(int arg1);

    void on_checkBoxMathematiquesGeometrie_stateChanged(int arg1);

    void on_checkBoxEcritureQualiteQuantite_stateChanged(int arg1);

    void on_checkBoxMathematiquesCalculGeometrie_stateChanged(int arg1);

    void on_checkBoxPrefereEPS_stateChanged(int arg1);

    void on_checkBoxPrefereHistoireGeographie_stateChanged(int arg1);

    void on_checkBoxPrefereMathematiques_stateChanged(int arg1);

    void on_checkBoxPreferePhysiqueChimie_stateChanged(int arg1);

    void on_checkBoxPrefereSVT_stateChanged(int arg1);

    void on_checkBoxPrefereFrancais_stateChanged(int arg1);

    void on_checkBoxPrefereAnglais_stateChanged(int arg1);

    void on_checkBoxPrefereEspagnol_stateChanged(int arg1);

    void on_checkBoxPrefereLangues_stateChanged(int arg1);

    void on_checkBoxPrefereTechnologie_stateChanged(int arg1);

    void on_checkBoxPrefereMusique_stateChanged(int arg1);

    void on_checkBoxPrefereArtsPlastique_stateChanged(int arg1);

    void on_checkBoxDetesteEPS_stateChanged(int arg1);

    void on_checkBoxDetesteHistoireGeo_stateChanged(int arg1);

    void on_checkBoxDetesteMathematiques_stateChanged(int arg1);

    void on_checkBoxDetestePhysiqueChimie_stateChanged(int arg1);

    void on_checkBoxDetesteSVT_stateChanged(int arg1);

    void on_checkBoxDetesteFrancais_stateChanged(int arg1);

    void on_checkBoxDetesteAnglais_stateChanged(int arg1);

    void on_checkBoxDetesteEspagnol_stateChanged(int arg1);

    void on_checkBoxDetesteLangues_stateChanged(int arg1);

    void on_checkBoxDetesteTechnologie_stateChanged(int arg1);

    void on_checkBoxDetesteMusique_stateChanged(int arg1);

    void on_checkBoxDetesteArtsPlastique_stateChanged(int arg1);

    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface3 *ui;
    QString comportementClasse = "";
    QString difficultesClasse = "";
    QString matieresPreferees = "";
    QString matieresDetestees = "";
};

#endif // INTERFACE3_H
