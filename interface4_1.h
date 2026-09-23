#ifndef INTERFACE4_1_H
#define INTERFACE4_1_H

#include <QDialog>

namespace Ui {
class Interface4_1;
}

class Interface4_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_1(QWidget *parent = nullptr);
    ~Interface4_1();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_1 *ui;

    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_1_H
