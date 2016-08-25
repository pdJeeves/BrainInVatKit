#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T09:50:32
#
#-------------------------------------------------

QT       += core gui opengl
INCLUDEPATH += $$PWD/freetures /usr/include/libxml2/
CONFIG += c++11
QMAKESPEC=linux-g++-64
LIBS=-pthread -lxml2 -lm
QMAKE_CXXFLAGS += -Werror=incompatible-pointer-types
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Brain_Vat2
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
    colorwidget.cpp \
    freetures/catalogue/catalogue_array_range.c \
    freetures/catalogue/catalogue_array.c \
    freetures/catalogue/catalogue_file_range.c \
    freetures/catalogue/catalogue_loader.c \
    freetures/catalogue/catalogue_token_range.c \
    freetures/catalogue/catalogue.c \
    freetures/catalogue/trie.c \
    freetures/support/rw_lock.c \
    freetures/genetics/export_genome.c \
    freetures/genetics/gen_range.c \
    freetures/genetics/load_genome.c \
    freetures/genetics/import_genes.c \
    freetures/genetics/import_genome.c \
    freetures/genetics/gno_range.c \
    freetures/ranges/directory_range.c \
    freetures/brain/load_tract.c \
    freetures/brain/load_lobe.c \
    freetures/brain/load_temporal.c \
    freetures/brain/lobe.c \
    freetures/brain/tract.c \
    freetures/brain/temporal.c

HEADERS  += mainwindow.h \
    lobemodel.h \
    modelcommand.h \
    tractmodel.h \
    brainview.h \
    brainmodel.h \
    instinctmodel.h \
    lobegene.h \
    tractgene.h \
    colorwidget.h \
    freetures/catalogue/catalogue_array_range.h \
    freetures/catalogue/catalogue_array.h \
    freetures/catalogue/catalogue_file_range.h \
    freetures/catalogue/catalogue_interface.h \
    freetures/catalogue/catalogue_loader.h \
    freetures/catalogue/catalogue_token_range.h \
    freetures/catalogue/catalogue.h \
    freetures/catalogue/trie.h \
    freetures/support/rw_lock.h \
    freetures/support/threads.h \
    freetures/genetics/gene_header.h \
    freetures/genetics/gen_range.h \
    freetures/genetics/genome_symbols.h \
    freetures/genetics/genome.h \
    freetures/genetics/gno_range.h \
    freetures/ranges/directory_range.h \
    freetures/brain/tract.h \
    freetures/brain/waypoint.h \
    freetures/brain/temporal.h \
    freetures/brain/lobe.h \
    freetures/brain/brain.h \
    freetures/brain/brain_organ.h

FORMS    += mainwindow.ui \
    lobegene.ui \
    tractgene.ui
