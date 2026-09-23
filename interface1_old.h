#ifndef INTERFACE1_OLD_H
#define INTERFACE1_OLD_H

#include <QDialog>

namespace Ui {
class Interface1;
}

class Interface1 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface1(QWidget *parent = nullptr);
    ~Interface1();

private:
    Ui::Interface1 *ui;
    QString entente = "";
    QString sexe;
    QString typeBilan;
    QString filePathToSave;
    QString fileName;
    QString lateralite;
    QString modeDeGarde;
};

#endif // INTERFACE1_OLD_H
