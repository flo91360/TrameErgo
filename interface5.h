#ifndef INTERFACE5_H
#define INTERFACE5_H

#include <QDialog>

namespace Ui {
class Interface5;
}

class Interface5 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface5(QWidget *parent = nullptr);
    ~Interface5();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface5 *ui;
};

#endif // INTERFACE5_H
