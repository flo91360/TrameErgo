#ifndef INTERFACE4_H
#define INTERFACE4_H

#include <QButtonGroup>
#include <QDialog>
#include <QJsonObject>
#include <QList>

namespace Ui {
class Interface4;
}

// Évaluation OT Hope d'un domaine de questionnaire.json (otHope/domaines) :
// pour chaque activité, « rien à signaler » ou un niveau de difficulté.
class Interface4 : public QDialog
{
    Q_OBJECT

public:
    explicit Interface4(int domaine, QWidget *parent = nullptr);
    ~Interface4();

private slots:
    void on_pushButtonSuivant_clicked();

private:
    Ui::Interface4 *ui;
    int numeroDomaine;
    QJsonObject domaine;
    // Une réponse par activité : 0 = rien à signaler, n = n-ième niveau.
    QList<QButtonGroup*> reponses;
};

#endif // INTERFACE4_H
