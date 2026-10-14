#include "listecases.h"

#include <QGridLayout>

ListeCases::ListeCases(QWidget *parent)
    : QWidget(parent)
{
    auto *grille = new QGridLayout(this);
    grille->setContentsMargins(0, 0, 0, 0);
}

void ListeCases::remplir(const QStringList &libelles, int colonnes)
{
    auto *grille = static_cast<QGridLayout*>(layout());
    const int lignes = (libelles.size() + colonnes - 1) / qMax(colonnes, 1);
    for (int i = 0; i < libelles.size(); ++i) {
        auto *caseACocher = new QCheckBox(libelles[i], this);
        connect(caseACocher, &QCheckBox::toggled, this, [this, caseACocher](bool cochee) {
            emit caseModifiee(caseACocher->text(), cochee);
        });
        grille->addWidget(caseACocher, i % lignes, i / lignes);
        cases << caseACocher;
    }
}

QStringList ListeCases::cochees(const QString &autre) const
{
    QStringList libelles;
    for (const QCheckBox *caseACocher : cases) {
        if (caseACocher->isChecked())
            libelles << caseACocher->text();
    }
    if (!autre.trimmed().isEmpty())
        libelles << autre.trimmed();
    return libelles;
}
