#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:18:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += main.cpp

unix:!macx: LIBS += -L$$OUT_PWD/../Shared/ -lShared

INCLUDEPATH += $$PWD/../Shared
DEPENDPATH += $$PWD/../Shared
