#ifndef INTERFACE5_H
#define INTERFACE5_H

#include <QDialog>

namespace Ui {
class Interface5;
}

class Interface5 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface5(QWidget *parent = nullptr);
    ~Interface5();

private slots:
    void on_pushButtonSuivant_clicked();

    void on_checkBoxAESH_stateChanged(int arg1);

    void on_checkBoxOrdinateur_stateChanged(int arg1);

    void on_checkBoxMiseEnPlacePAP_stateChanged(int arg1);

    void on_checkBoxMiseEnPlacePPS_stateChanged(int arg1);

    void on_checkBoxMiseEnPlacePPRE_stateChanged(int arg1);

    void on_checkBoxPolycopiesDonnes_stateChanged(int arg1);

    void on_checkBoxTierTemps_stateChanged(int arg1);

    void on_checkBoxMoinsExercices_stateChanged(int arg1);

    void on_checkBoxDicterTrous_stateChanged(int arg1);

private:
    Ui::Interface5 *ui;
    QString amenagementsScolaires = "";
};

#endif // INTERFACE5_H
