#-------------------------------------------------
#
# Project created by QtCreator 2015-11-02T22:40:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BuildingImitation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    machine.cpp \
    worker.cpp \
    day.cpp

HEADERS  += mainwindow.h \
    machine.h \
    worker.h \
    day.h

FORMS    += mainwindow.ui
