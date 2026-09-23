#ifndef INTERFACE4_7_H
#define INTERFACE4_7_H

#include <QDialog>
#include <QList>
#include <QString>

namespace Ui {
class Interface4_7;
}

class Interface4_7 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_7(QWidget *parent = nullptr);
    ~Interface4_7();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_7 *ui;
};

#endif // INTERFACE4_7_H
