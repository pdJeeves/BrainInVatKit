#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T09:50:32
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += src \
	../Kreatures/libFreetures/include/ \
	../Kreatures/libFreetures/src/

LIBS=-pthread -lm -lpcre16 -L/usr/lib/x86_64-linux-gnu/ -ldrm
TARGET = BrainInVatKit
TEMPLATE = app


SOURCES += main.cpp \
   ../Kreatures/libFreetures/src/body/pose_string_table.cpp \
   ../Kreatures/libFreetures/src/catalogue/catalogue_hash.cpp \
   ../Kreatures/libFreetures/src/biochemistry/emitter.c \
   ../Kreatures/libFreetures/src/biochemistry/organ.c \
   ../Kreatures/libFreetures/src/biochemistry/reaction.c \
   ../Kreatures/libFreetures/src/biochemistry/receptor.c \
   ../Kreatures/libFreetures/src/body/default_poses.c \
   ../Kreatures/libFreetures/src/body/pigment.c \
   ../Kreatures/libFreetures/src/body/skell.c \
   ../Kreatures/libFreetures/src/brain/brain_organ.c \
   ../Kreatures/libFreetures/src/brain/load_lobe.c \
   ../Kreatures/libFreetures/src/brain/load_temporal.c \
   ../Kreatures/libFreetures/src/brain/load_tract.c \
   ../Kreatures/libFreetures/src/brain/lobe.c \
   ../Kreatures/libFreetures/src/brain/temporal.c \
   ../Kreatures/libFreetures/src/brain/tract.c \
   ../Kreatures/libFreetures/src/catalogue/catalogue.c \
   ../Kreatures/libFreetures/src/catalogue/catalogue_array.c \
   ../Kreatures/libFreetures/src/catalogue/catalogue_array_range.c \
   ../Kreatures/libFreetures/src/catalogue/catalogue_file_range.c \
   ../Kreatures/libFreetures/src/catalogue/catalogue_loader.c \
   ../Kreatures/libFreetures/src/catalogue/genome_symbols.c \
   ../Kreatures/libFreetures/src/creature/create_creature.c \
   ../Kreatures/libFreetures/src/creature/creature.c \
   ../Kreatures/libFreetures/src/genetics/chromosomerange.c \
   ../Kreatures/libFreetures/src/genetics/createmoniker.c \
   ../Kreatures/libFreetures/src/genetics/export_genome.c \
   ../Kreatures/libFreetures/src/genetics/gen_range.c \
   ../Kreatures/libFreetures/src/genetics/genetichandle.c \
   ../Kreatures/libFreetures/src/genetics/import_genes.c \
   ../Kreatures/libFreetures/src/genetics/import_genome.c \
   ../Kreatures/libFreetures/src/genetics/import_support_flex.c \
   ../Kreatures/libFreetures/src/genetics/load_genome.c \
   ../Kreatures/libFreetures/src/genetics/mergegenome.c \
   ../Kreatures/libFreetures/src/genetics/mutate.c \
   ../Kreatures/libFreetures/src/genetics/sanatizegenome.c \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_conn.c \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_emitter.c \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_receptor.c \
   ../Kreatures/libFreetures/src/parser/grammar.c \
   ../Kreatures/libFreetures/src/parser/lexical.c \
   ../Kreatures/libFreetures/src/parser/strdup.c \
   ../Kreatures/libFreetures/src/ranges/directory_range.c \
    src/brainmodel.cpp \
    src/brainview.cpp \
    src/colorview.cpp \
    src/colorwidget.cpp \
    src/instinctmodel.cpp \
    src/lobegene.cpp \
    src/lobemodel.cpp \
    src/mainwindow.cpp \
    src/modelcommand.cpp \
    src/tractgene.cpp \
    src/tractmodel.cpp

HEADERS  += \
   ../Kreatures/libFreetures/include/brain.h \
   ../Kreatures/libFreetures/include/catalogue.h \
   ../Kreatures/libFreetures/include/creature.h \
   ../Kreatures/libFreetures/include/definitions.h \
   ../Kreatures/libFreetures/include/genetics.h \
   ../Kreatures/libFreetures/include/gui_adapter.h \
   ../Kreatures/libFreetures/include/skell.h \
   ../Kreatures/libFreetures/include/types.h \
   ../Kreatures/libFreetures/src/behavior/behavior.h \
   ../Kreatures/libFreetures/src/behavior/instinct.h \
   ../Kreatures/libFreetures/src/behavior/stimulus.h \
   ../Kreatures/libFreetures/src/biochemistry/biochemistry.h \
   ../Kreatures/libFreetures/src/biochemistry/emitter.h \
   ../Kreatures/libFreetures/src/biochemistry/half_lives.h \
   ../Kreatures/libFreetures/src/biochemistry/organ.h \
   ../Kreatures/libFreetures/src/biochemistry/reaction.h \
   ../Kreatures/libFreetures/src/biochemistry/receptor.h \
   ../Kreatures/libFreetures/src/biochemistry/sources.h \
   ../Kreatures/libFreetures/src/biochemistry/waypoint.h \
   ../Kreatures/libFreetures/src/body/appearance.h \
   ../Kreatures/libFreetures/src/body/body.h \
   ../Kreatures/libFreetures/src/body/expression.h \
   ../Kreatures/libFreetures/src/body/pigment.h \
   ../Kreatures/libFreetures/src/body/pose_gait.h \
   ../Kreatures/libFreetures/src/body/pose_string_table.h \
   ../Kreatures/libFreetures/src/body/skell.h \
   ../Kreatures/libFreetures/src/brain/brain.h \
   ../Kreatures/libFreetures/src/brain/brain_organ.h \
   ../Kreatures/libFreetures/src/brain/lobe.h \
   ../Kreatures/libFreetures/src/brain/temporal.h \
   ../Kreatures/libFreetures/src/brain/tract.h \
   ../Kreatures/libFreetures/src/brain/waypoint.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue_array.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue_array_range.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue_file_range.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue_interface.h \
   ../Kreatures/libFreetures/src/catalogue/catalogue_loader.h \
   ../Kreatures/libFreetures/src/creature/creature.h \
   ../Kreatures/libFreetures/src/creature/genetic_creature.h \
   ../Kreatures/libFreetures/src/genetics/chromosomerange.h \
   ../Kreatures/libFreetures/src/genetics/gen_range.h \
   ../Kreatures/libFreetures/src/genetics/gene_header.h \
   ../Kreatures/libFreetures/src/genetics/genes.h \
   ../Kreatures/libFreetures/src/genetics/genetichandle.h \
   ../Kreatures/libFreetures/src/genetics/genome.h \
   ../Kreatures/libFreetures/src/genetics/genome_symbols.h \
   ../Kreatures/libFreetures/src/genetics/import_support_flex.h \
   ../Kreatures/libFreetures/src/genetics/sanatizegenome.h \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_conn.h \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_emitter.h \
   ../Kreatures/libFreetures/src/neurochemistry/neuro_receptor.h \
   ../Kreatures/libFreetures/src/neurochemistry/neurochemistry.h \
   ../Kreatures/libFreetures/src/parser/lexer.h \
   ../Kreatures/libFreetures/src/parser/strdup.h \
   ../Kreatures/libFreetures/src/ranges/directory_range.h \
    src/brainmodel.h \
    src/brainview.h \
    src/colorview.h \
    src/colorwidget.h \
    src/instinctmodel.h \
    src/lobegene.h \
    src/lobemodel.h \
    src/mainwindow.h \
    src/modelcommand.h \
    src/tractgene.h \
    src/tractmodel.h

FORMS    += \
    lobegene.ui \
    mainwindow.ui \
    tractsettings.ui
