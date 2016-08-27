#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T09:50:32
#
#-------------------------------------------------

QT       += core gui opengl
INCLUDEPATH += /usr/local/include/libfreetures /usr/include/libxml2/
CONFIG += c++11
QMAKESPEC=linux-g++-64
LIBS=-L/usr/local/lib/libfreetures/ -lfreetures -pthread -lm -lpcre16 -L/usr/lib/x86_64-linux-gnu/ -lxml2 -lz
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BrainInVatKit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lobemodel.cpp \
    modelcommand.cpp \
    tractmodel.cpp \
    brainview.cpp \
    brainmodel.cpp \
    instinctmodel.cpp \
    lobegene.cpp \
    tractgene.cpp \
    colorwidget.cpp

HEADERS  += mainwindow.h \
    lobemodel.h \
    modelcommand.h \
    tractmodel.h \
    brainview.h \
    brainmodel.h \
    instinctmodel.h \
    lobegene.h \
    tractgene.h \
    colorwidget.h

FORMS    += mainwindow.ui \
    lobegene.ui \
    tractgene.ui
