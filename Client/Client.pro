#-------------------------------------------------
#
# Project created by QtCreator 2014-02-05T18:18:52
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pixspaceclient
TEMPLATE = app


SOURCES += main.cpp\
    connectiondialog.cpp \
    clientapp.cpp \
    controller.cpp \
    playercontroller.cpp \
    clientgraphicsscene.cpp \
    clientgraphicsview.cpp

HEADERS  += \
    connectiondialog.h \
    clientapp.h \
    controller.h \
    playercontroller.h \
    clientgraphicsscene.h \
    clientgraphicsview.h

FORMS    += \
    connectiondialog.ui

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

RESOURCES += \
    Assets.qrc
