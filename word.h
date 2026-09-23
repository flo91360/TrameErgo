#ifndef WORD_H
#define WORD_H

#include <QAxObject>
#include <QDebug>
#include <QDir>

class Word
{
public:
    Word();

    static void copieCree(QString sourceFile, QString destFile);
    static void copieColle(QString sourceFile, QString destFile);
    static void replaceText(QString originText, QString newText);
    static void replaceTextFromZoneText(QString originText, QString newText);

    static QAxObject* wordApp;
    static QAxObject* documents;
    static QAxObject* document;
    static QAxObject* selection;
    static QString filePathToSave;
    static QString pathToArbo;

};

#endif // WORD_H
