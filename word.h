#ifndef WORD_H
#define WORD_H

#include <QAxObject>
#include <QDebug>
#include <QDir>

class Word
{
public:
    Word();

    // Modèle du bilan installé : %LOCALAPPDATA%\TrameErgo\contenu\bilan.docx.
    static QString modeleBilan();
    // Crée le bilan destFile, copie du modèle ; false (et message) en cas d'échec.
    static bool creerBilan(const QString &destFile);
    // Ouvre un document Word ; nullptr si Word ou le fichier est indisponible.
    static QAxObject* ouvrir(const QString &file);
    // Texte d'un champ liste : une ligne « - élément » par élément.
    static QString enListe(const QStringList &elements);
    // Remplace un champ {…} dans le texte du document ouvert (casse respectée).
    static void replaceText(QString originText, QString newText);
    // Idem dans les zones de texte (page de garde).
    static void replaceTextFromZoneText(QString originText, QString newText);
    // Ferme Word s'il n'a plus aucun document ouvert.
    static void fermer();

    static QAxObject* wordApp;
    static QAxObject* documents;
    static QAxObject* document;
    static QAxObject* selection;
    static QString filePathToSave;

};

#endif // WORD_H
