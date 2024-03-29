#-------------------------------------------------
#
# Project created by QtCreator 2024-01-24T16:20:42
#
#-------------------------------------------------

QT       += core gui
QT       += qml
QT       += quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NodeForm
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
    Core/abstractevalnode.cpp \
    Global/globalqmlfiles.cpp \
    Global/globaluiparams.cpp \
    Global/globalpaths.cpp \
    Utils/fileoperations.cpp \
    Global/globalinit.cpp \
    Global/globalitems.cpp \
    Core/basicnodegraph.cpp \
    Interface/connectionobject.cpp \
    Utils/qmlcreationutils.cpp \
    Interface/abstractnodeobject.cpp \
    Core/abstractnode.cpp \
    Interface/verticalnodeobject.cpp \
    Interface/basicgraphobject.cpp \
    Interface/abstractslotobject.cpp \
    Interface/slotobject.cpp \
    Interface/abstractgraphobject.cpp \
    Global/globalcleanup.cpp \
    Core/abstractboolevalnode.cpp \
    Extension/abstractextension.cpp \
    Extension/Node/nodeselectionextension.cpp \
    Extension/Graph/graphnodeselectionextension.cpp \
    Extension/Graph/graphconnectionselectionextension.cpp \
    Extension/Connection/connectionselectionextension.cpp \
    Extension/extensionfactory.cpp \
    Interface/abstractconnectionobject.cpp \
    Extension/Graph/movebackgroundextension.cpp \
    Extension/Graph/scalebackgroundextension.cpp \
    Extension/Node/movenodeextension.cpp \
    Extension/Graph/deleteselectednodeextension.cpp \
    Extension/Graph/deleteselectedconnecitonextension.cpp \
    Extension/Slot/indragaddconnectionextension.cpp \
    Extension/Slot/outdragaddconnectionextension.cpp \
    Extension/Slot/dragaddconnectionextension.cpp \
    Utils/debugutils.cpp \
    Core/abstractnodegraph.cpp \
    Interface/abstractdatabridge.cpp \
    Core/basicnodemacro.cpp \
    Interface/databridgemacro.cpp

HEADERS += \
    Core/connection.h \
    Core/inputslot.h \
    Core/abstractslot.h \
    Core/outputslot.h \
    Utils/tupleutils.h \
    Utils/slottupleutils.h \
    Utils/variant.h \
    Core/abstractevalnode.h \
    Global/globalqmlfiles.h \
    Global/globaluiparams.h \
    Global/globalpaths.h \
    Utils/fileoperations.h \
    Global/globalitems.h \
    Global/typenamemacro.h \
    Core/basicnodegraph.h \
    Core/abstractnodegraph.h \
    Interface/connectionobject.h \
    Utils/qmlcreationutils.h \
    Interface/abstractnodeobject.h \
    Core/abstractnode.h \
    Interface/verticalnodeobject.h \
    Interface/basicgraphobject.h \
    Interface/abstractslotobject.h \
    Interface/slotobject.h \
    Interface/abstractgraphobject.h \
    Global/globalcleanup.h \
    Global/globalinit.h \
    Core/abstractboolevalnode.h \
    Core/basicboolnodemacro.h \
    Extension/abstractextension.h \
    Extension/Node/nodeselectionextension.h \
    Extension/Graph/graphnodeselectionextension.h \
    Extension/Graph/graphconnectionselectionextension.h \
    Extension/Connection/connectionselectionextension.h \
    Extension/extensionfactory.h \
    Extension/extensiontypes.h \
    Interface/abstractconnectionobject.h \
    Extension/Graph/movebackgroundextension.h \
    Extension/Graph/scalebackgroundextension.h \
    Extension/Node/movenodeextension.h \
    Extension/Graph/deleteselectednodeextension.h \
    Extension/Graph/deleteselectedconnecitonextension.h \
    Extension/Slot/indragaddconnectionextension.h \
    Extension/Slot/outdragaddconnectionextension.h \
    Extension/Slot/dragaddconnectionextension.h \
    Utils/debugutils.h \
    Interface/abstractdatabridge.h \
    Interface/databridgemacro.h \
    Core/basicnodemacro.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    UI/main.qml \
    UI/dummy.qml \
    UI/BaseWidget/NFCircle1.qml \
    UI/BaseWidget/NFSlider2.qml \
    UI/BaseWidget/NFSlider1.qml \
    UI/BaseWidget/NFSpinBox1.qml \
    UI/BaseWidget/NFTextInput1.qml \
    UI/BaseWidget/NFText1.qml \
    UI/BaseWidget/NFTriangle1.qml \
    UI/NFLine1.qml \
    UI/NFBezierCurve2.qml \
    UI/NFBezierCurve1.qml \
    UI/NFBackground1.qml \
    UI/qmlWidgets/Handles/NFCircleHandle1.qml \
    UI/qmlWidgets/Handles/NFTriangleHandle1.qml \
    UI/qmlWidgets/NodeBase/NFVerticalBase1.qml \
    UI/qmlWidgets/TextLabels/NFTextLabel1.qml \
    UI/qmlWidgets/GlobalWidgets/Curve/NFBezierCurve2.qml \
    UI/qmlWidgets/GlobalWidgets/Curve/NFBezierCurveDashAnimate1.qml \
    UI/qmlWidgets/GlobalWidgets/Background/NFBackground1.qml \
    UI/qmlWidgets/DataBridges/Getters/NFIntGetLabel1.qml \
    UI/qmlWidgets/DataBridges/Setters/NFDoubleSetSlider1.qml \
    UI/qmlWidgets/DataBridges/Setters/NFIntSetSlider1.qml \
    UI/qmlWidgets/DataBridges/Setters/NFIntSetSpinBox1.qml \
    UI/qmlWidgets/DataBridges/Setters/NFtIntSetTextInput1.qml
