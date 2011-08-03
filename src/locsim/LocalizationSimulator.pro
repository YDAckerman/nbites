#-------------------------------------------------
#
# Project created by QtCreator 2011-07-28T16:07:20
#
#-------------------------------------------------

QT       += core gui

TARGET = LocalizationSimulator
TEMPLATE = app


SOURCES += main.cpp\
        simulatorwindow.cpp \
    Field.cpp \
    FieldPlayer.cpp \
    OdometrySimulator.cpp \
    LocalizationSimulator.cpp \
    ../man/include/NBMath.cpp \
    ../man/noggin/AugmentedMCL.cpp \
    FieldParticle.cpp \
    FieldLandmark.cpp \
    PlayerIndicator.cpp

HEADERS  += simulatorwindow.h \
    FieldPlayer.h \
    OdometrySimulator.h \
    CommonStructs.h \
    LocalizationSimulator.h \
    ../man/include/NBMath.h \
    ../man/noggin/ParticleFilter.h \
    ../man/noggin/LocSystem.h \
    ../man/noggin/AugmentedMCL.h \
    FieldLandmark.h \
    FieldParticle.h \
    Field.h \
    PlayerIndicator.h

INCLUDEPATH += "../man/include"
INCLUDEPATH += "../man/noggin"

DEFINES += SIMULATOR
