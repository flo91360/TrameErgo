QT += core gui
QT += axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets uitools

CONFIG += c++17

# Version de l'application (exe Windows, installateur et Release GitHub).
# Chaque livraison l'augmente ; une nouvelle version publie la Release v<VERSION>.
VERSION = 1.1.0
QMAKE_TARGET_PRODUCT = TrameErgo
QMAKE_TARGET_DESCRIPTION = "Bilans d'ergothérapie"
DISTFILES += contenu/bilan.docx

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    interface0.cpp \
    interface1.cpp \
    interface2_1.cpp \
    interface2_2.cpp \
    interface3.cpp \
    interface4.cpp \
    interface4_7.cpp \
    interface4_8.cpp \
    interface5.cpp \
    listecases.cpp \
    main.cpp \
    mainwindow.cpp \
    patient.cpp \
    questionnaire.cpp \
    word.cpp

HEADERS += \
    interface0.h \
    interface1.h \
    interface2_1.h \
    interface2_2.h \
    interface3.h \
    interface4.h \
    interface4_7.h \
    interface4_8.h \
    interface5.h \
    listecases.h \
    mainwindow.h \
    patient.h \
    questionnaire.h \
    word.h

FORMS += \
    interface0.ui \
    interface1.ui \
    interface2_1.ui \
    interface2_2.ui \
    interface3.ui \
    interface4.ui \
    interface4_7.ui \
    interface4_8.ui \
    interface5.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Contenu du questionnaire, intégré à l'exécutable.
RESOURCES += contenu.qrc
