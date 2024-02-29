#-------------------------------------------------
#
# Project created by QtCreator 2024-01-24T16:20:42
#
#-------------------------------------------------

QT       += core gui
QT       += qml
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Nodest
TEMPLATE = lib
CONFIG += staticlib

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
    Core/connection.cpp \
    Core/inputslot.cpp \
    Core/outputslot.cpp \
    main.cpp \
    Utils/debugutils.cpp \
    Utils/variant.cpp \
    Core/abstractslot.cpp \
    Core/abstractevalnode.cpp \
    Wrapper/slotsetter.cpp \
    Global/globalqmlfiles.cpp \
    Global/globaluiparams.cpp \
    Global/globalpaths.cpp \
    Utils/fileoperations.cpp \
    Global/globalinit.cpp \
    Global/globalitems.cpp \
    Core/basicnodegraph.cpp \
    Core/abstractnodegraph.cpp \
    Interface/connectionobject.cpp \
    Interface/inputslotobject.cpp \
    Utils/qmlcreationutils.cpp \
    Interface/outputslotobject.cpp \
    Interface/abstractnodeobject.cpp \
    Core/abstractnode.cpp \
    Interface/verticalnodeobject.cpp \
    Interface/basicgraphobject.cpp \
    Interface/abstractslotobject.cpp \
    Interface/slotobject.cpp \
    Wrapper/abstractslotgetter.cpp \
    Interface/abstractgraphobject.cpp \
    Global/globalcleanup.cpp \
    Core/abstractboolevalnode.cpp \
    Extension/abstractextension.cpp \
    Extension/Node/nodeselectionextension.cpp \
    Extension/Graph/graphnodeselectionextension.cpp \
    Extension/Graph/graphconnectionselectionextension.cpp \
    Extension/Connection/connectionselectionextension.cpp \
    Extension/extensionfactory.cpp

HEADERS += \
    Core/connection.h \
    Core/inputslot.h \
    Core/abstractslot.h \
    Core/outputslot.h \
    Utils/debugutils.h \
    Utils/tupleutils.h \
    Utils/slottupleutils.h \
    Utils/variant.h \
    Core/basicnodemacro.h \
    Core/abstractevalnode.h \
    Wrapper/slotsettermacro.h \
    Wrapper/abstractslotsetter.h \
    Global/globalqmlfiles.h \
    Global/globaluiparams.h \
    Global/globalpaths.h \
    Utils/fileoperations.h \
    Global/globalitems.h \
    Global/typenamemacro.h \
    Global/typenameregistry.h \
    Core/basicnodegraph.h \
    Core/abstractnodegraph.h \
    Interface/connectionobject.h \
    Interface/inputslotobject.h \
    Utils/qmlcreationutils.h \
    Interface/outputslotobject.h \
    Interface/abstractnodeobject.h \
    Core/abstractnode.h \
    Interface/verticalnodeobject.h \
    Interface/basicgraphobject.h \
    Interface/abstractslotobject.h \
    Interface/slotobject.h \
    Interface/abstractgraphobject.h \
    Wrapper/abstractslotgetter.h \
    Wrapper/slotgettermacro.h \
    Global/globalcleanup.h \
    Global/globalinit.h \
    Utils/gstupleutils.h \
    Core/abstractboolevalnode.h \
    Core/basicboolnodemacro.h \
    Extension/abstractextension.h \
    Extension/Node/nodeselectionextension.h \
    Extension/Graph/graphnodeselectionextension.h \
    Extension/Graph/graphconnectionselectionextension.h \
    Extension/Connection/connectionselectionextension.h \
    Extension/extensionfactory.h \
    Extension/extensiontypes.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    UI/main.qml \
    UI/SetterWidget/IntSetter/IntSlider_0.qml \
    UI/qmlWidgets/Setters/IntSlider1_0.qml \
    UI/DummyGS.qml \
    UI/qmlWidgets/Setters/DoubleSlider1_2.qml \
    UI/qmlWidgets/Lines/Line1.qml \
    UI/dummy.qml \
    UI/qmlWidgets/Getters/IntLabel1_0.qml \
    UI/qmlWidgets/Setters/TextInput1_int.qml \
    UI/qmlWidgets/Setters/IntSlider1_int.qml \
    UI/qmlWidgets/Setters/SpinBox1_int.qml \
    UI/qmlWidgets/Getters/IntLabel1_int.qml \
    UI/BaseWidget/NodestCircle1.qml \
    UI/BaseWidget/NodestSlider2.qml \
    UI/BaseWidget/NodestSlider1.qml \
    UI/BaseWidget/NodestSpinBox1.qml \
    UI/BaseWidget/NodestTextInput1.qml \
    UI/BaseWidget/NodestText1.qml \
    UI/BaseWidget/NodestTriangle1.qml \
    UI/NodestLine1.qml \
    UI/NodestBezierCurve2.qml \
    UI/NodestBezierCurve1.qml \
    UI/NodestBackground1.qml \
    UI/qmlWidgets/Getters/NodestIntGetLabel1.qml \
    UI/qmlWidgets/Handles/NodestCircleHandle1.qml \
    UI/qmlWidgets/Handles/NodestTriangleHandle1.qml \
    UI/qmlWidgets/NodeBase/NodestVerticalBase1.qml \
    UI/qmlWidgets/Setters/NodestDoubleSetSlider1.qml \
    UI/qmlWidgets/Setters/NodestIntSetSlider1.qml \
    UI/qmlWidgets/Setters/NodestIntSetTextInput1.qml \
    UI/qmlWidgets/Setters/NodestIntSetSpinBox1.qml \
    UI/qmlWidgets/TextLabels/NodestTextLabel1.qml
