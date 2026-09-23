#ifndef INTERFACE4_3_H
#define INTERFACE4_3_H

#include <QDialog>

namespace Ui {
class Interface4_3;
}

class Interface4_3 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_3(QWidget *parent = nullptr);
    ~Interface4_3();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_3 *ui;

    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_3_H
