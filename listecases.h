#ifndef LISTECASES_H
#define LISTECASES_H

#include <QCheckBox>
#include <QList>
#include <QStringList>
#include <QWidget>

// Liste de cases à cocher construite à partir d'une liste du questionnaire.
// Dans les .ui : QWidget promu en ListeCases (en-tête listecases.h).
class ListeCases : public QWidget
{
    Q_OBJECT

public:
    explicit ListeCases(QWidget *parent = nullptr);

    // Une case par libellé, réparties en colonnes de haut en bas.
    void remplir(const QStringList &libelles, int colonnes = 1);
    // Libellés cochés, dans l'ordre de la liste, puis autre s'il est rempli.
    QStringList cochees(const QString &autre = QString()) const;

signals:
    void caseModifiee(const QString &libelle, bool cochee);

private:
    QList<QCheckBox*> cases;
};

#endif // LISTECASES_H
