#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:18:06
#
#-------------------------------------------------
QT       += core sql network

QT       -= gui

CONFIG   -= app_bundle
QT   += uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixspaceserver
TEMPLATE = app

SOURCES += main.cpp \
    networkserver.cpp \
    serverapp.cpp \
    datamanager.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Shared/release/ -lpixspace
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Shared/debug/ -lpixspace
else:unix: LIBS += -L$$OUT_PWD/../Shared/ -lpixspace

INCLUDEPATH += $$PWD/../Shared
DEPENDPATH += $$PWD/../Shared

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Shared/release/libpixspace.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Shared/debug/libpixspace.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Shared/release/pixspace.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Shared/debug/pixspace.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Shared/libpixspace.a

HEADERS += \
    networkserver.h\
    serverapp.h \
    datamanager.h

FORMS += \
    serverapp.ui

RESOURCES += \
    Icon.qrc
