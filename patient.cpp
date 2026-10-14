#include "patient.h"
#include "questionnaire.h"

#include <QJsonArray>
#include <QJsonObject>

Patient::Patient() {}

QString Patient::sexePatient = nullptr;
QString Patient::typeBilan = nullptr;
QString Patient::agePatient = nullptr;
QString Patient::prenomPatient = nullptr;
QMap<QString, QStringList> Patient::otHope;
QStringList Patient::objectfisFinauxPossibles;
QStringList Patient::objectfisAVQPatient;
QStringList Patient::objectfisAVSPatient;
QStringList Patient::objectfisAVLPatient;
QStringList Patient::objectfisFinauxPatients;

QString Patient:: calculerAge(QDate dateNaissance) {
    // Âge en années et mois révolus à la date du jour. Le calcul en jours
    // (365 et 30 jours) se décalait : 10 ans et 11 mois devenaient 11 ans et 0 mois.
    QDate dateDuJour = QDate::currentDate();
    int mois = (dateDuJour.year() - dateNaissance.year()) * 12
               + dateDuJour.month() - dateNaissance.month();
    if (dateDuJour.day() < dateNaissance.day())
        --mois; // Le mois en cours n'est pas encore révolu
    int ans = mois / 12;

    return QString("%1 %2 et %3 mois").arg(ans).arg(ans > 1 ? "ans" : "an").arg(mois % 12);
}

QString Patient::accord(const QString &masculin, const QString &feminin)
{
    return sexePatient == "Homme" ? masculin : feminin;
}

QStringList Patient::activitesOtHope(const QString &domaine)
{
    QStringList activites;
    for (const QJsonValue &niveau : Questionnaire::valeur("otHope/niveaux").toArray())
        activites += otHope.value(niveau.toObject().value("id").toString() + "_" + domaine);
    return activites;
}
