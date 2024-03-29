#-------------------------------------------------
#
# Project created by QtCreator 2024-02-18T17:41:30
#
#-------------------------------------------------

QT       += core gui
QT       += qml
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NFVectorPlayground
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
    typeconversion.cpp \
    vectorfunctions.cpp \
    nodefactoryvector.cpp

HEADERS += \
    typedefines.h \
    gsdefines.h \
    typeconversion.h \
    vectorfunctions.h \
    nodedefines.h \
    nodefactoryvector.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


DISTFILES += \
    main.qml \
    Controls/IntVectorGetter.qml \
    Controls/main.qml \
    Controls/ButtonManager.qml \
    Controls/Getters/NFVECvectorGetLabels1.qml \
    UI/IntVector4DNode.json \
    UI/VectorConcatNode.json \
    UI/VectorDisplayNode.json \
    UI/VectorReverseNode.json \
    UI/VectorSortNode.json \
    UI/VectorSplitNode.json \
    Controls/Getters/VECvectorGetLabels1.qml

unix|win32: LIBS += -L$$PWD/../../../build/debug/ -lNodeForm

INCLUDEPATH += $$PWD/../../../
DEPENDPATH += $$PWD/../../../

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../build/debug/NodeForm.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../build/debug/NodeForm.a
