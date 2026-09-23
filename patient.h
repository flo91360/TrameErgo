#ifndef PATIENT_H
#define PATIENT_H

#include <QDir>

class Patient
{
public:
    Patient();

    static QString calculerAge(QDate dateNaissance);

    static QString sexePatient;
    static QString typeBilan;
    static QString agePatient;
    static QString prenomPatient;
    static QString aideMaison;
    static QString aideEcole;
    static QString aideLoisirs;
    static QString difficulteMaison;
    static QString difficulteEcole;
    static QString difficulteLoisirs;
    static QString grandeDifficulteMaison;
    static QString grandeDifficulteEcole;
    static QString grandeDifficulteLoisirs;
    static QStringList objectfisAVQPatient;
    static QStringList objectfisAVSPatient;
    static QStringList objectfisAVLPatient;
    static QStringList objectfisFinauxPossibles;
    static QStringList objectfisFinauxPatients;

};

#endif // PATIENT_H
