#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T17:40:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolejki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    advanceddialog.cpp \
    ../../kolejki/src/urand.cpp \
    ../../kolejki/src/System.cpp \
    ../../kolejki/src/Queue.cpp \
    ../../kolejki/src/nrand.cpp \
    ../../kolejki/src/Client.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    advanceddialog.h \
    ../../kolejki/src/urand.h \
    ../../kolejki/src/System.h \
    ../../kolejki/src/randSeed.h \
    ../../kolejki/src/Queue.h \
    ../../kolejki/src/nrand.h \
    ../../kolejki/src/Client.h \
    qcustomplot.h \
    sleeper.h

FORMS    += mainwindow.ui \
    advanceddialog.ui
