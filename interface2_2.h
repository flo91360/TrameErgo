#ifndef INTERFACE2_2_H
#define INTERFACE2_2_H

#include <QComboBox>
#include <QDialog>
#include <QMap>

namespace Ui {
class Interface2_2;
}

class Interface2_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface2_2(QWidget *parent = nullptr);
    ~Interface2_2();

private slots:
    void on_checkBoxAucun_toggled(bool checked);

    void on_pushButtonSuivant_clicked();

private:
    // Ajoute ou retire la fréquence de suivi du professionnel coché ou décoché.
    void suiviModifie(const QString &professionnel, bool suivi);

    Ui::Interface2_2 *ui;
    QMap<QString, QComboBox*> frequences;
};

#endif // INTERFACE2_2_H
