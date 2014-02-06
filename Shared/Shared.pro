#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:19:27
#
#-------------------------------------------------

QT       -= gui

TARGET = Shared
TEMPLATE = lib

DEFINES += SHARED_LIBRARY

SOURCES += shared.cpp \
    app.cpp \
    body.cpp \
    simpledatamanager.cpp \
    universe.cpp \
    vector.cpp

HEADERS += shared.h\
        shared_global.h \
    app.h \
    body.h \
    datamanager.h \
    simpledatamanager.h \
    universe.h \
    vector.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SUBDIRS += \
    Server.pro
