#ifndef INTERFACE1_H
#define INTERFACE1_H

#include <QDialog>
#include <QStandardPaths>

namespace Ui {
class Interface1;
}

class Interface1 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface1(QWidget *parent = nullptr);
    ~Interface1();

private slots:
    void on_pushButtonSuivant_clicked();

    void on_radioButtonBonneEntente_clicked();

    void on_radioButtonMauvaiseEntenre_clicked();

    void on_radioButtonNeutreEntente_clicked();

private:
    Ui::Interface1 *ui;
    QString sexe =  "";
    QString typeBilan =  "";
    QString entente =  "";
};

#endif // INTERFACE1_H
