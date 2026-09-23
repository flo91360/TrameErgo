#ifndef INTERFACE4_5_H
#define INTERFACE4_5_H

#include <QDialog>

namespace Ui {
class Interface4_5;
}

class Interface4_5 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_5(QWidget *parent = nullptr);
    ~Interface4_5();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_5 *ui;

    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_5_H
