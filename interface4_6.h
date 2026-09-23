#ifndef INTERFACE4_6_H
#define INTERFACE4_6_H

#include <QDialog>

namespace Ui {
class Interface4_6;
}

class Interface4_6 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_6(QWidget *parent = nullptr);
    ~Interface4_6();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_6 *ui;

    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_6_H
