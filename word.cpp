#include "word.h"

Word::Word() {}

QAxObject* Word::wordApp = nullptr;
QAxObject* Word::documents = nullptr;
QAxObject* Word::document = nullptr;
QAxObject* Word::selection = nullptr;
QString Word::filePathToSave = nullptr;
QString Word::pathToArbo = nullptr;

void Word::copieColle(QString sourceFile, QString destFile)
{
    qDebug() << "coucou";
    // Ouvrir le document source à partir duquel vous souhaitez copier le texte
    QAxObject* sourceDocument = documents->querySubObject("Open(const QString&)", sourceFile);
        qDebug() << "coucou2";
    if (!sourceDocument->isNull()) {
                qDebug() << "coucou3";
        QAxObject* sourceSelection = wordApp->querySubObject("Selection");
                    qDebug() << "coucou4";
        if (!sourceSelection->isNull()) {
                            qDebug() << "coucou5";
            // Sélectionner tout le contenu du document source
            sourceSelection->dynamicCall("WholeStory()");
            // Copier le texte sélectionné
            sourceSelection->dynamicCall("Copy()");
                qDebug() << "coucou6";
        }
    }

    // Ouvrir le document cible dans lequel vous souhaitez coller le texte
    QAxObject* destDocument = documents->querySubObject("Open(const QString&)", destFile);
    if (!destDocument->isNull()) {
        // Sélectionner le contenu du nouveau document
        QAxObject* selection = wordApp->querySubObject("Selection");
        if (!selection->isNull()) {
            selection->dynamicCall("EndKey(int)", 6); // Se déplacer à la fin du document
            selection->dynamicCall("InsertBreak(int)", 7); // Insérer un saut de page
            // Coller le texte copié du document source
            selection->dynamicCall("Paste()");
        }
    }
    // Fermer le document source
    sourceDocument->dynamicCall("Close()");
    destDocument->dynamicCall("Save()");
    destDocument->dynamicCall("Close()");
}

void Word::copieCree(QString sourceFile, QString destFile)
{
    qDebug() << "coucou";
    qDebug() << sourceFile;
    // Ouvrir le document source à partir duquel vous souhaitez copier le texte
    QAxObject* sourceDocument = documents->querySubObject("Open(const QString&)", sourceFile);
    qDebug() << "coucou1";
    if (!sourceDocument->isNull()) {
        qDebug() << "coucou2";
        QAxObject* sourceSelection = wordApp->querySubObject("Selection");
        if (!sourceSelection->isNull()) {
            // Sélectionner tout le contenu du document source
            sourceSelection->dynamicCall("WholeStory()");
            // Copier le texte sélectionné
            sourceSelection->dynamicCall("Copy()");
        }
    }

    // Ouvrir le document cible dans lequel vous souhaitez coller le texte
    QAxObject* destDocument = documents->querySubObject("Add()");
    if (!destDocument->isNull()) {
        // Sélectionner le contenu du nouveau document
        QAxObject* selection = wordApp->querySubObject("Selection");
        if (!selection->isNull()) {
            // Coller le texte copié du document source
            selection->dynamicCall("Paste()");
        }
        // Enregistrer les modifications apportées au document cible
        destDocument->dynamicCall("SaveAs(const QString&)", destFile);

        // Fermer le document cible
        destDocument->dynamicCall("Close()");
    }

    // Fermer le document source
    sourceDocument->dynamicCall("Close()");
}


void Word::replaceText(QString originText, QString newText)
{
    if (!selection->isNull()) {

        qDebug() << "Text to replace:" << originText << "with" << newText;

        QAxObject* find = selection->querySubObject("Find");
        selection->dynamicCall("HomeKey(int)", 6); // Move to start of document
        if (!find->isNull()) {
            qDebug() << "find non null";
            find->dynamicCall("ClearFormatting()");
            find->setProperty("Text", originText);
            find->setProperty("Forward", true);
            find->setProperty("Wrap", 1); // wdFindContinue
            find->setProperty("Format", false);
            find->setProperty("MatchCase", false);
            find->setProperty("MatchWholeWord", false);
            find->setProperty("MatchWildcards", false);
            find->setProperty("MatchSoundsLike", false);
            find->setProperty("MatchAllWordForms", false);

            while (find->dynamicCall("Execute()").toBool()) {
                qDebug() << "Text trouve";
                QAxObject* range = selection->querySubObject("Range");
                if (!range->isNull()) {
                    qDebug() << "On remplace";
                    range->dynamicCall("Text", newText);
                }
            }
        }
    }
}


void Word::replaceTextFromZoneText(QString originText, QString newText)
{
    QAxObject* shapes = document->querySubObject("Shapes");
    if (!shapes->isNull()) {
        int shapeCount = shapes->dynamicCall("Count()").toInt();
        for (int i = 1; i <= shapeCount; ++i) {
            QAxObject* shape = shapes->querySubObject("Item(int)", i);
            if (!shape->isNull()) {
                // Vérifier si le shape est une zone de texte
                QString shapeType = shape->dynamicCall("Type").toString();
                if (shapeType == "17") { // Vérifier si c'est une zone de texte
                    QAxObject* textFrame = shape->querySubObject("TextFrame");
                    if (!textFrame->isNull()) {
                        QAxObject* textRange = textFrame->querySubObject("TextRange");
                        if (!textRange->isNull()) {
                            // Rechercher et remplacer le texte dans la zone de texte
                            if (!textRange->isNull()) {
                                QAxObject* find = textRange->querySubObject("Find");
                                if (!find->isNull()) {
                                    find->dynamicCall("ClearFormatting()");
                                    find->setProperty("Text", originText);
                                    find->setProperty("Forward", true);
                                    find->setProperty("Wrap", 1); // wdFindContinue
                                    find->setProperty("Format", false);
                                    find->setProperty("MatchCase", false);
                                    find->setProperty("MatchWholeWord", false);
                                    find->setProperty("MatchWildcards", false);
                                    find->setProperty("MatchSoundsLike", false);
                                    find->setProperty("MatchAllWordForms", false);

                                    while (find->dynamicCall("Execute()").toBool()) {
                                        textRange->dynamicCall("Text", newText);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
