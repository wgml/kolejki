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
    qcustomplot.cpp \
    urand.cpp \
    System.cpp \
    show.cpp \
    saveToFile.cpp \
    Queue.cpp \
    nrand.cpp \
    Client.cpp \
    showplotswindow.cpp

HEADERS  += mainwindow.h \
    advanceddialog.h \
    qcustomplot.h \
    sleeper.h \
    urand.h \
    System.h \
    show.h \
    saveToFile.h \
    randSeed.h \
    Queue.h \
    nrand.h \
    Client.h \
    showplotswindow.h \

FORMS    += mainwindow.ui \
    advanceddialog.ui \
    showplotswindow.ui

OTHER_FILES += \
    makefile
