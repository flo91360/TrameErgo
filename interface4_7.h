#ifndef INTERFACE4_7_H
#define INTERFACE4_7_H

#include <QComboBox>
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

    // Les 5 choix d'objectifs de chaque catégorie : vie quotidienne, école, loisirs.
    QList<QComboBox*> choixAVQ() const;
    QList<QComboBox*> choixAVS() const;
    QList<QComboBox*> choixAVL() const;
};

#endif // INTERFACE4_7_H
