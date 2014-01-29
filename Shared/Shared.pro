#-------------------------------------------------
#
# Project created by QtCreator 2014-01-29T17:41:19
#
#-------------------------------------------------

QT       -= gui

TARGET = Shared
TEMPLATE = lib

DEFINES += SHARED_LIBRARY

SOURCES += shared.cpp

HEADERS += shared.h\
        shared_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
