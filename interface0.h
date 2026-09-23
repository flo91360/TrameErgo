#ifndef INTERFACE0_H
#define INTERFACE0_H

#include <QDialog>

namespace Ui {
class Interface0;
}

class Interface0 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface0(QWidget *parent = nullptr);
    ~Interface0();

private slots:
    void on_pushButtonSuivant_clicked();

    void on_radioButtonEnfant_clicked();

    void on_radioButtonAdolescent_clicked();

    void on_radioButtonAdulte_clicked();

private:
    Ui::Interface0 *ui;
};

#endif // INTERFACE0_H
