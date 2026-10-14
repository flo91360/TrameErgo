#ifndef INTERFACE2_1_H
#define INTERFACE2_1_H

#include <QDialog>

namespace Ui {
class Interface2_1;
}

class Interface2_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface2_1(QWidget *parent = nullptr);
    ~Interface2_1();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface2_1 *ui;
};

#endif // INTERFACE2_1_H
