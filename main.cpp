#include <QApplication>
#include <QAxObject>
#include <QDebug>
#include <QFile>

#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Fixe le dossier des modèles : %LOCALAPPDATA%\TrameErgo\arborescence.
    QApplication::setApplicationName("TrameErgo");
    MainWindow w;
    w.show();
    return a.exec();
}


