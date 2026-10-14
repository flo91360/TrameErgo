#ifndef INTERFACE3_H
#define INTERFACE3_H

#include <QDialog>

namespace Ui {
class Interface3;
}

class Interface3 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface3(QWidget *parent = nullptr);
    ~Interface3();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface3 *ui;
};

#endif // INTERFACE3_H
