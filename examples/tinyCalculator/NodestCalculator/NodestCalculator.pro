#-------------------------------------------------
#
# Project created by QtCreator 2024-02-16T18:57:23
#
#-------------------------------------------------

QT       += core gui
QT       += qml
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodestCalculator
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
    numericfunctions.cpp \
    Controls/controlpaths.cpp \
    nodefactory.cpp

HEADERS += \
    nodedefines.h \
    typedefines.h \
    gsdefines.h \
    numericfunctions.h \
    Controls/controlpaths.h \
    nodefactory.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



DISTFILES += \
    UI/main.qml \
    UI/BaseWidget/SliderType1.qml \
    UI/SetterWidget/IntSetter/IntSlider_0.qml \
    UI/qmlWidgets/Setters/IntSlider1_0.qml \
    UI/BaseWidget/CircleType1.qml \
    UI/qmlWidgets/Handles/CircleHandle1.qml \
    UI/BaseWidget/TextType1.qml \
    UI/qmlWidgets/TextLabels/TextLabel1.qml \
    UI/qmlWidgets/NodeBase/VerticalNodeBase1.qml \
    UI/DummyGS.qml \
    UI/qmlWidgets/Setters/DoubleSlider1_2.qml \
    UI/BaseWidget/TriangleType1.qml \
    UI/qmlWidgets/Handles/TriangleHandle1.qml \
    UI/background.qml \
    UI/qmlWidgets/Lines/Line1.qml \
    UI/Line1.qml \
    UI/Line2.qml \
    UI/dummy.qml \
    UI/Line3.qml \
    UI/qmlWidgets/Getters/IntLabel1_0.qml \
    UI/BaseWidget/ModernSliderType1.qml \
    Controls/ButtonType1.qml \
    Controls/Button1.qml \
    Controls/ButtonManager.qml \
    Controls/main.qml \
    UI/AddIntNode.json \
    UI/ClampIntNode.json \
    UI/IntNode.json






unix|win32: LIBS += -L$$PWD/../../../build/debug/ -lNodest

INCLUDEPATH += $$PWD/../../../
DEPENDPATH += $$PWD/../../../

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../build/debug/Nodest.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../../build/debug/libNodest.a
