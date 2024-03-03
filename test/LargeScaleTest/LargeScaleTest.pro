#-------------------------------------------------
#
# Project created by QtCreator 2024-03-03T21:48:03
#
#-------------------------------------------------

QT       += core gui
QT       += qml
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LargeScaleTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        main.cpp \
    main.cpp \
    nodefactory.cpp \
    numericfunctions.cpp \
    Controls/controlpaths.cpp

HEADERS += \
    gsdefines.h \
    nodedefines.h \
    nodefactory.h \
    numericfunctions.h \
    typedefines.h \
    Controls/controlpaths.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    LargeScaleTest.pro

DISTFILES += \
    LargeScaleTest.pro.user \
    Controls/ButtonManager.qml \
    Controls/main.qml

unix|win32: LIBS += -L$$PWD/../../build/debug/ -lNodest

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../build/debug/Nodest.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../build/debug/libNodest.a
