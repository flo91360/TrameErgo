#ifndef INTERFACE4_4_H
#define INTERFACE4_4_H

#include <QDialog>

namespace Ui {
class Interface4_4;
}

class Interface4_4 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_4(QWidget *parent = nullptr);
    ~Interface4_4();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_4 *ui;


    void checkRadioButtonAide();
    void checkRadioButtonDifficulte();
    void checkRadioButtonGrandeDifficulte();
};

#endif // INTERFACE4_4_H
