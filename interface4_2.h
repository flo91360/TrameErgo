#ifndef INTERFACE4_2_H
#define INTERFACE4_2_H

#include <QDialog>

namespace Ui {
class Interface4_2;
}

class Interface4_2 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_2(QWidget *parent = nullptr);
    ~Interface4_2();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_2 *ui;

    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_2_H
