#ifndef QUESTIONNAIRE_H
#define QUESTIONNAIRE_H

#include <QJsonValue>
#include <QStringList>

// Contenu du questionnaire (listes de choix, phrases du bilan), lu dans
// contenu/questionnaire.json, intégré à l'exécutable (contenu.qrc).
// Les chemins désignent une valeur du JSON : "scolarite/matieres".
class Questionnaire
{
public:
    static QJsonValue valeur(const QString &chemin);
    // Textes d'une liste ; pour une liste d'objets, leurs « libelle ».
    static QStringList liste(const QString &chemin);
    // « phrase » de l'objet de la liste dont le « libelle » est donné.
    static QString phrase(const QString &chemin, const QString &libelle);
};

#endif // QUESTIONNAIRE_H
