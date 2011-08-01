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
    ../man/noggin/AugmentedMCL.cpp

HEADERS  += simulatorwindow.h \
    Field.h \
    FieldPlayer.h \
    OdometrySimulator.h \
    CommonStructs.h \
    LocalizationSimulator.h \
    ../man/include/NBMath.h \
    ../man/noggin/ParticleFilter.h \
    ../man/noggin/LocSystem.h \
    ../man/noggin/AugmentedMCL.h

INCLUDEPATH += "../man/include"
INCLUDEPATH += "../man/noggin"

DEFINES += SIMULATOR
