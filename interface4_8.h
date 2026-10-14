#ifndef INTERFACE4_8_H
#define INTERFACE4_8_H

#include <QComboBox>
#include <QDialog>

namespace Ui {
class Interface4_8;
}

class Interface4_8 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4_8(QWidget *parent = nullptr);
    ~Interface4_8();

private slots:
    void on_pushButtonValiderObjectifsFinaux_clicked();

    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4_8 *ui;

    // Les 5 objectifs finaux choisis pour le patient, puis par ses parents.
    QList<QComboBox*> choixPatient() const;
    QList<QComboBox*> choixParents() const;
};

#endif // INTERFACE4_8_H
