#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:19:27
#
#-------------------------------------------------

QT       += gui widgets sql network

TARGET = pixspace
TEMPLATE = lib
CONFIG += staticlib

DEFINES += SHARED_LIBRARY

SOURCES += private/body.cpp \
    private/universe.cpp \
    private/vector.cpp \
    private/renderbody.cpp \
    private/datamanager.cpp \
    private/connection.cpp \
    private/ship.cpp

HEADERS += private/shared_global.h \
    private/body.h \
    private/universe.h \
    private/vector.h \
    Universe \
    Vector \
    Body \
    DataManager \
    private/renderbody.h \
    RenderBody \
    private/datamanager.h \
    private/connection.h \
    Connection \
    private/ship.h \
    Ship

unix {
    target.path = /usr/lib
    INSTALLS += target
}
