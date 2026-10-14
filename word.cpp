#include "word.h"

#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QStandardPaths>

Word::Word() {}

QAxObject* Word::wordApp = nullptr;
QAxObject* Word::documents = nullptr;
QAxObject* Word::document = nullptr;
QAxObject* Word::selection = nullptr;
QString Word::filePathToSave = nullptr;

// Word ou le modèle absent laissait des pointeurs nuls et faisait planter
// l'application : on prévient l'utilisateur et on interrompt l'étape.
static bool signaler(const QString &message)
{
    QMessageBox::critical(nullptr, "TrameErgo", message);
    return false;
}

QString Word::modeleBilan()
{
    return QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) + "/contenu/bilan.docx";
}

bool Word::creerBilan(const QString &destFile)
{
    const QString modele = modeleBilan();
    if (!QFileInfo::exists(modele))
        return signaler("Modèle Word introuvable :\n" + QDir::toNativeSeparators(modele)
                        + "\n\nRéinstallez TrameErgo pour restaurer le modèle.");
    QDir().mkpath(QFileInfo(destFile).absolutePath());
    // Un bilan du même nom (même patient, même mois) est remplacé.
    QFile::remove(destFile);
    if (!QFile::copy(modele, destFile))
        return signaler("Impossible de créer le bilan :\n" + QDir::toNativeSeparators(destFile)
                        + "\n\nIl est peut-être ouvert dans Word.");
    QFile::setPermissions(destFile, QFile::permissions(destFile) | QFileDevice::WriteOwner);
    return true;
}

QAxObject* Word::ouvrir(const QString &file)
{
    if (!wordApp || wordApp->isNull() || !documents) {
        signaler("Microsoft Word est introuvable ou n'a pas pu être lancé.");
        return nullptr;
    }
    if (!QFileInfo::exists(file)) {
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

QString Word::enListe(const QStringList &elements)
{
    QStringList lignes;
    for (const QString &element : elements)
        lignes << "- " + element;
    return lignes.join("\n");
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
            find->setProperty("MatchCase", true);
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
                                    find->setProperty("MatchCase", true);
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

void Word::fermer()
{
    if (!wordApp || wordApp->isNull())
        return;
    // Un Word lancé par l'application reste invisible en mémoire après la
    // génération. On ne le ferme que s'il n'a aucun document ouvert, pour ne
    // jamais fermer les documents de l'utilisateur.
    const QVariant ouverts = documents ? documents->property("Count") : QVariant();
    if (ouverts.isValid() && ouverts.toInt() == 0)
        wordApp->dynamicCall("Quit()");
    delete wordApp;
    wordApp = nullptr;
    documents = nullptr;
    document = nullptr;
    selection = nullptr;
}
