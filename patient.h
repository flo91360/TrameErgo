#ifndef PATIENT_H
#define PATIENT_H

#include <QDate>
#include <QMap>
#include <QStringList>

class Patient
{
public:
    Patient();

    static QString calculerAge(QDate dateNaissance);
    // Mot accordé au sexe du patient : accord("il", "elle").
    static QString accord(const QString &masculin, const QString &feminin);
    // Activités OT Hope d'un domaine (maison, ecole, loisirs), tous niveaux confondus.
    static QStringList activitesOtHope(const QString &domaine);

    // « Femme » ou « Homme », « Enfant » ou « Ado ».
    static QString sexePatient;
    static QString typeBilan;
    static QString agePatient;
    static QString prenomPatient;
    // Activités OT Hope par « niveau_domaine » (aide_maison, difficulte_ecole…),
    // qui sont aussi les champs du bilan.
    static QMap<QString, QStringList> otHope;
    static QStringList objectfisAVQPatient;
    static QStringList objectfisAVSPatient;
    static QStringList objectfisAVLPatient;
    static QStringList objectfisFinauxPossibles;
    static QStringList objectfisFinauxPatients;

};

#endif // PATIENT_H
