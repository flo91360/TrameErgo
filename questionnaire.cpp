#include "questionnaire.h"

#include <QDebug>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

static QJsonObject charger()
{
    QFile fichier(":/contenu/questionnaire.json");
    QJsonParseError erreur;
    QJsonDocument document;
    if (fichier.open(QIODevice::ReadOnly))
        document = QJsonDocument::fromJson(fichier.readAll(), &erreur);
    if (!document.isObject())
        QMessageBox::critical(nullptr, "TrameErgo", "Le contenu du questionnaire est illisible : "
                                                    + erreur.errorString());
    return document.object();
}

QJsonValue Questionnaire::valeur(const QString &chemin)
{
    static const QJsonObject racine = charger();
    QJsonValue valeur = racine;
    for (const QString &cle : chemin.split('/'))
        valeur = valeur.toObject().value(cle);
    if (valeur.isUndefined())
        qWarning() << "Questionnaire : valeur absente" << chemin;
    return valeur;
}

QStringList Questionnaire::liste(const QString &chemin)
{
    QStringList textes;
    for (const QJsonValue &element : valeur(chemin).toArray())
        textes << (element.isObject() ? element.toObject().value("libelle").toString() : element.toString());
    return textes;
}

QString Questionnaire::phrase(const QString &chemin, const QString &libelle)
{
    for (const QJsonValue &element : valeur(chemin).toArray()) {
        if (element.toObject().value("libelle").toString() == libelle)
            return element.toObject().value("phrase").toString();
    }
    return QString();
}
