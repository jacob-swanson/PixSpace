#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:19:27
#
#-------------------------------------------------

QT       += gui widgets network

TARGET = pixspace
TEMPLATE = lib
CONFIG += staticlib

DEFINES += SHARED_LIBRARY

SOURCES += private/body.cpp \
    private/universe.cpp \
    private/vector.cpp \
    private/renderbody.cpp \
    private/connection.cpp \
    private/ship.cpp \
    private/particle.cpp \
    private/particleemitter.cpp \
    private/configurator.cpp

HEADERS += private/shared_global.h \
    private/body.h \
    private/universe.h \
    private/vector.h \
    Universe \
    Vector \
    Body \
    private/renderbody.h \
    RenderBody \
    private/connection.h \
    Connection \
    private/ship.h \
    Ship \
    private/particle.h \
    private/particleemitter.h \
    private/configurator.h \
    Configurator

unix {
    target.path = /usr/lib
    INSTALLS += target
}
