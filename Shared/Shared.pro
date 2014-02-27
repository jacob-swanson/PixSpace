#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:19:27
#
#-------------------------------------------------

QT       += gui widgets sql

TARGET = pixspace
TEMPLATE = lib
CONFIG += staticlib

DEFINES += SHARED_LIBRARY

SOURCES += private/body.cpp \
    private/universe.cpp \
    private/vector.cpp \
    private/serverapp.cpp \
    private/renderbody.cpp \
    private/clientapp.cpp \
    private/datamanager.cpp

HEADERS += private/shared_global.h \
    private/body.h \
    private/universe.h \
    private/vector.h \
    private/serverapp.h \
    Universe \
    Vector \
    Body \
    DataManager \
    ServerApp \
    private/renderbody.h \
    RenderBody \
    private/clientapp.h \
    private/datamanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
