#-------------------------------------------------
#
# Project created by QtCreator 2013-12-05T17:40:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kolejki
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    advanceddialog.cpp \
    qcustomplot.cpp \
    urand.cpp \
    System.cpp \
    Queue.cpp \
    nrand.cpp \
    Client.cpp

HEADERS  += mainwindow.h \
    advanceddialog.h \
    qcustomplot.h \
    urand.h \
    System.h \
    randSeed.h \
    Queue.h \
    nrand.h \
    Client.h \

FORMS    += mainwindow.ui \
    advanceddialog.ui

OTHER_FILES += \
    makefile
