#-------------------------------------------------
#
# Project created by QtCreator 2014-02-10T18:54:57
#
#-------------------------------------------------

QT       += testlib sql

QT       -= gui

TARGET = tst_testvector
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testvector.cpp \
    main.cpp \
    tst_testbody.cpp \
    tst_testrenderbody.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_testvector.h \
    tst_testbody.h \
    tst_testrenderbody.h

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
