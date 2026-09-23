#include "patient.h"

Patient::Patient() {}

QString Patient::sexePatient = nullptr;
QString Patient::typeBilan = nullptr;
QString Patient::agePatient = nullptr;
QString Patient::prenomPatient = nullptr;
QString Patient::aideMaison= nullptr;
QString Patient::aideEcole= nullptr;
QString Patient::aideLoisirs= nullptr;
QString Patient::difficulteMaison= nullptr;
QString Patient::difficulteEcole= nullptr;
QString Patient::difficulteLoisirs= nullptr;
QString Patient::grandeDifficulteMaison= nullptr;
QString Patient::grandeDifficulteEcole= nullptr;
QString Patient::grandeDifficulteLoisirs= nullptr;
QStringList Patient::objectfisFinauxPossibles;
QStringList Patient::objectfisAVQPatient;
QStringList Patient::objectfisAVSPatient;
QStringList Patient::objectfisAVLPatient;
QStringList Patient::objectfisFinauxPatients;

QString Patient:: calculerAge(QDate dateNaissance) {
    // Obtenez la date actuelle
    QDate dateDuJour = QDate::currentDate();

    // Calculez la différence entre la date actuelle et la date de naissance
    int years = dateNaissance.daysTo(dateDuJour) / 365;
    int months = (dateNaissance.daysTo(dateDuJour) % 365) / 30;

    // Créez la chaîne de caractères représentant l'âge
    QString ageString = QString("%1 ans et %2 mois").arg(years).arg(months);

    return ageString;
}
