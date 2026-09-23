#ifndef INTERFACE2_1_H
#define INTERFACE2_1_H

#include <QDialog>
#include <QAxObject>
#include <QDebug>

namespace Ui {
class Interface2_1;
}

class Interface2_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface2_1(QWidget *parent = nullptr);
    ~Interface2_1();

private slots:
    void on_pushButtonSuivant_clicked();

    void on_checkBoxMotif1_stateChanged(int arg1);

    void on_checkBoxMotif2_stateChanged(int arg1);

    void on_checkBoxMotif3_stateChanged(int arg1);

    void on_checkBoxTDASansHyperactivite_stateChanged(int arg1);

    void on_checkBoxDifficultesEcriture_stateChanged(int arg1);

    void on_checkBoxdDifficultesLecture_stateChanged(int arg1);

    void on_checkBoxDifficultesCoordination_stateChanged(int arg1);

    void on_checkBoxDifficultesConcentration_stateChanged(int arg1);

    void on_checkBoxDysgraphie_stateChanged(int arg1);

    void on_checkBoxDyslexie_stateChanged(int arg1);

    void on_checkBoxDystographie_stateChanged(int arg1);

    void on_checkBoxDifficultesSociales_stateChanged(int arg1);

    void on_checkBoxHyperlaxite_stateChanged(int arg1);

    void on_checkBoxDeveloppementCoordination_stateChanged(int arg1);

    void on_checkBoxTSA_stateChanged(int arg1);

    void on_checkBoxAutistiqueAsperger_stateChanged(int arg1);

    void on_checkBoxTDAAvecHyperactivite_stateChanged(int arg1);

    void on_checkBoxPsychologique_stateChanged(int arg1);

    void on_checkBoxPsychiatrique_stateChanged(int arg1);

private:
    Ui::Interface2_1 *ui;
    QString motifs =  "";
    QString troubles =  "";
};

#endif // INTERFACE2_1_H
