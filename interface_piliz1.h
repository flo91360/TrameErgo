#ifndef INTERFACE_PILIZ1_H
#define INTERFACE_PILIZ1_H

#include <QDialog>

namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonSuivant_clicked();

private:
    Ui::Test *ui;
};

#endif // INTERFACE_PILIZ1_H
