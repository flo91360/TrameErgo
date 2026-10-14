#ifndef WORD_H
#define WORD_H

#include <QAxObject>
#include <QDebug>
#include <QDir>

class Word
{
public:
    Word();

    // Modèle d'un écran pour le sexe et l'âge du patient :
    // arborescence/<Sexe>/<Âge>/<ecran>/<ecran>.docx
    static QString modele(const QString &ecran);
    // Ouvre un document Word ; nullptr si Word ou le fichier est indisponible.
    static QAxObject* ouvrir(const QString &file);
    static void copieCree(QString sourceFile, QString destFile);
    static void copieColle(QString sourceFile, QString destFile);
    // Remplace le champ du document ouvert par le contenu du modèle sourceFile.
    static bool insereModele(const QString &champ, const QString &sourceFile);
    static void replaceText(QString originText, QString newText);
    static void replaceTextFromZoneText(QString originText, QString newText);
    // Ferme Word s'il n'a plus aucun document ouvert.
    static void fermer();

    static QAxObject* wordApp;
    static QAxObject* documents;
    static QAxObject* document;
    static QAxObject* selection;
    static QString filePathToSave;
    static QString pathToArbo;

};

#endif // WORD_H
