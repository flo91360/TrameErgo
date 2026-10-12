#include "word.h"

#include <QFileInfo>
#include <QMessageBox>

Word::Word() {}

QAxObject* Word::wordApp = nullptr;
QAxObject* Word::documents = nullptr;
QAxObject* Word::document = nullptr;
QAxObject* Word::selection = nullptr;
QString Word::filePathToSave = nullptr;
QString Word::pathToArbo = nullptr;

// Word ou un modèle absent laissait des pointeurs nuls et faisait planter
// l'application : on prévient l'utilisateur et on interrompt l'étape.
static bool signaler(const QString &message)
{
    QMessageBox::critical(nullptr, "TrameErgo", message);
    return false;
}

static bool disponible(const QString &sourceFile)
{
    if (!Word::wordApp || Word::wordApp->isNull() || !Word::documents)
        return signaler("Microsoft Word est introuvable ou n'a pas pu être lancé.");
    if (!QFileInfo::exists(sourceFile))
        return signaler("Modèle Word introuvable :\n" + QDir::toNativeSeparators(sourceFile)
                        + "\n\nRéinstallez TrameErgo pour restaurer les modèles.");
    return true;
}

QAxObject* Word::ouvrir(const QString &file)
{
    if (!documents || !QFileInfo::exists(file)) {
        signaler("Document introuvable :\n" + QDir::toNativeSeparators(file));
        return nullptr;
    }
    QAxObject* opened = documents->querySubObject("Open(const QString&)", QDir::toNativeSeparators(file));
    if (!opened || opened->isNull()) {
        signaler("Word n'a pas pu ouvrir :\n" + QDir::toNativeSeparators(file));
        return nullptr;
    }
    return opened;
}

void Word::copieColle(QString sourceFile, QString destFile)
{
    if (!disponible(sourceFile))
        return;
    // Copier tout le contenu du modèle
    QAxObject* sourceDocument = ouvrir(sourceFile);
    if (!sourceDocument)
        return;
    QAxObject* sourceSelection = wordApp->querySubObject("Selection");
    if (sourceSelection && !sourceSelection->isNull()) {
        sourceSelection->dynamicCall("WholeStory()");
        sourceSelection->dynamicCall("Copy()");
    }

    // Le coller à la fin du bilan, après un saut de page
    QAxObject* destDocument = ouvrir(destFile);
    if (destDocument) {
        QAxObject* selection = wordApp->querySubObject("Selection");
        if (selection && !selection->isNull()) {
            selection->dynamicCall("EndKey(int)", 6); // Fin du document
            selection->dynamicCall("InsertBreak(int)", 7); // Saut de page
            selection->dynamicCall("Paste()");
        }
    }
    sourceDocument->dynamicCall("Close()");
    if (destDocument) {
        destDocument->dynamicCall("Save()");
        destDocument->dynamicCall("Close()");
    }
}

void Word::copieCree(QString sourceFile, QString destFile)
{
    if (!disponible(sourceFile))
        return;
    // Copier tout le contenu du modèle
    QAxObject* sourceDocument = ouvrir(sourceFile);
    if (!sourceDocument)
        return;
    QAxObject* sourceSelection = wordApp->querySubObject("Selection");
    if (sourceSelection && !sourceSelection->isNull()) {
        sourceSelection->dynamicCall("WholeStory()");
        sourceSelection->dynamicCall("Copy()");
    }

    // Créer le bilan dans un nouveau document (dossier créé si besoin)
    QDir().mkpath(QFileInfo(destFile).absolutePath());
    QAxObject* destDocument = documents->querySubObject("Add()");
    if (destDocument && !destDocument->isNull()) {
        QAxObject* selection = wordApp->querySubObject("Selection");
        if (selection && !selection->isNull()) {
            selection->dynamicCall("Paste()");
        }
        destDocument->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(destFile));
        destDocument->dynamicCall("Close()");
    } else {
        signaler("Word n'a pas pu créer le bilan.");
    }
    sourceDocument->dynamicCall("Close()");
}


void Word::replaceText(QString originText, QString newText)
{
    if (selection && !selection->isNull()) {

        qDebug() << "Text to replace:" << originText << "with" << newText;

        QAxObject* find = selection->querySubObject("Find");
        selection->dynamicCall("HomeKey(int)", 6); // Move to start of document
        if (find && !find->isNull()) {
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
                if (range && !range->isNull()) {
                    qDebug() << "On remplace";
                    range->dynamicCall("Text", newText);
                }
            }
        }
    }
}


void Word::replaceTextFromZoneText(QString originText, QString newText)
{
    QAxObject* shapes = document ? document->querySubObject("Shapes") : nullptr;
    if (shapes && !shapes->isNull()) {
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
