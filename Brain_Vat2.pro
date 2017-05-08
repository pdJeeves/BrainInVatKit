#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T09:50:32
#
#-------------------------------------------------

QT       += core gui opengl
INCLUDEPATH += \
	/home/anyuser/Developer/Kreatures/libFreetures/include/ \
	/home/anyuser/Developer/Kreatures/libFreetures/src/
CONFIG += c++11
QMAKESPEC=linux-g++-64
LIBS=-pthread -lm -lpcre16 -L/usr/lib/x86_64-linux-gnu/ -lxml2 -ldrm
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
    colorwidget.cpp \
    ../../../Developer/Kreatures/libFreetures/src/body/pose_string_table.cpp \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_hash.cpp \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/emitter.c \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/organ.c \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/reaction.c \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/receptor.c \
    ../../../Developer/Kreatures/libFreetures/src/body/default_poses.c \
    ../../../Developer/Kreatures/libFreetures/src/body/pigment.c \
    ../../../Developer/Kreatures/libFreetures/src/body/skell.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/brain_organ.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/load_lobe.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/load_temporal.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/load_tract.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/lobe.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/temporal.c \
    ../../../Developer/Kreatures/libFreetures/src/brain/tract.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_array.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_array_range.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_file_range.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_loader.c \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/genome_symbols.c \
    ../../../Developer/Kreatures/libFreetures/src/creature/create_creature.c \
    ../../../Developer/Kreatures/libFreetures/src/creature/creature.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/chromosomerange.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/createmoniker.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/export_genome.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/gen_range.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/genetichandle.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/import_genes.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/import_genome.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/import_support_flex.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/load_genome.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/mergegenome.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/mutate.c \
    ../../../Developer/Kreatures/libFreetures/src/genetics/sanatizegenome.c \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_conn.c \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_emitter.c \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_receptor.c \
    ../../../Developer/Kreatures/libFreetures/src/parser/grammar.c \
    ../../../Developer/Kreatures/libFreetures/src/parser/lexical.c \
    ../../../Developer/Kreatures/libFreetures/src/parser/strdup.c \
    ../../../Developer/Kreatures/libFreetures/src/ranges/directory_range.c

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
    ../../../Developer/Kreatures/libFreetures/include/brain.h \
    ../../../Developer/Kreatures/libFreetures/include/catalogue.h \
    ../../../Developer/Kreatures/libFreetures/include/creature.h \
    ../../../Developer/Kreatures/libFreetures/include/definitions.h \
    ../../../Developer/Kreatures/libFreetures/include/genetics.h \
    ../../../Developer/Kreatures/libFreetures/include/gui_adapter.h \
    ../../../Developer/Kreatures/libFreetures/include/skell.h \
    ../../../Developer/Kreatures/libFreetures/include/types.h \
    ../../../Developer/Kreatures/libFreetures/src/behavior/behavior.h \
    ../../../Developer/Kreatures/libFreetures/src/behavior/instinct.h \
    ../../../Developer/Kreatures/libFreetures/src/behavior/stimulus.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/biochemistry.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/emitter.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/half_lives.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/organ.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/reaction.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/receptor.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/sources.h \
    ../../../Developer/Kreatures/libFreetures/src/biochemistry/waypoint.h \
    ../../../Developer/Kreatures/libFreetures/src/body/appearance.h \
    ../../../Developer/Kreatures/libFreetures/src/body/body.h \
    ../../../Developer/Kreatures/libFreetures/src/body/expression.h \
    ../../../Developer/Kreatures/libFreetures/src/body/pigment.h \
    ../../../Developer/Kreatures/libFreetures/src/body/pose_gait.h \
    ../../../Developer/Kreatures/libFreetures/src/body/pose_string_table.h \
    ../../../Developer/Kreatures/libFreetures/src/body/skell.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/brain.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/brain_organ.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/lobe.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/temporal.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/tract.h \
    ../../../Developer/Kreatures/libFreetures/src/brain/waypoint.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_array.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_array_range.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_file_range.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_interface.h \
    ../../../Developer/Kreatures/libFreetures/src/catalogue/catalogue_loader.h \
    ../../../Developer/Kreatures/libFreetures/src/creature/creature.h \
    ../../../Developer/Kreatures/libFreetures/src/creature/genetic_creature.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/chromosomerange.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/gen_range.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/gene_header.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/genes.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/genetichandle.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/genome.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/genome_symbols.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/import_support_flex.h \
    ../../../Developer/Kreatures/libFreetures/src/genetics/sanatizegenome.h \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_conn.h \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_emitter.h \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neuro_receptor.h \
    ../../../Developer/Kreatures/libFreetures/src/neurochemistry/neurochemistry.h \
    ../../../Developer/Kreatures/libFreetures/src/parser/lexer.h \
    ../../../Developer/Kreatures/libFreetures/src/parser/strdup.h \
    ../../../Developer/Kreatures/libFreetures/src/ranges/directory_range.h

FORMS    += mainwindow.ui \
    lobegene.ui \
    tractgene.ui
