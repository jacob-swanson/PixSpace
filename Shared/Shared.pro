#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:19:27
#
#-------------------------------------------------

QT       -= gui

TARGET = pixspace
TEMPLATE = lib
CONFIG += staticlib

DEFINES += SHARED_LIBRARY

SOURCES += private/body.cpp \
    private/simpledatamanager.cpp \
    private/universe.cpp \
    private/vector.cpp \
    private/serverapp.cpp

HEADERS += private/shared_global.h \
    private/body.h \
    private/datamanager.h \
    private/simpledatamanager.h \
    private/universe.h \
    private/vector.h \
    private/serverapp.h \
    SimpleDataManager \
    Universe \
    Vector \
    Body \
    DataManager \
    ServerApp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
