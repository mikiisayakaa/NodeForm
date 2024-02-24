import QtQuick 2.12
import QtQuick.Controls 2.2

import "../../BaseWidget"
import "../../qmlWidgets/TextLabels"

Rectangle {
    id: nodeBase
    objectName: "nodeBase"
    x: 50000
    y: 50000
    width: 0
    radius: 10
    height: 0

    property real scaleValue: parent.scaleValue
    property real minWidth: 0

    transform: Scale{
        origin.x: nodeBase.parent.width / 2 - nodeBase.x
        origin.y: nodeBase.parent.height / 2 - nodeBase.y
        xScale: nodeBase.scaleValue
        yScale: nodeBase.scaleValue
    }

    z: parent.z + 10

    color: Qt.rgba(0.2,0.2,0.2,1.0)

    property color colorValue: Qt.rgba(1, 1, 1, 1)
    property bool select: false

    border.width: 1
    border.color: colorValue

    signal position(real x, real y)
    signal selected()


    MouseArea{
        id: mouseArea

        anchors.fill: parent

        preventStealing: true

        property real startMouseX: 0
        property real startMouseY: 0

        onPositionChanged: {
            nodeBase.x += mouseX - startMouseX;
            nodeBase.y += mouseY - startMouseY;
            position(nodeBase.x, nodeBase.y);
        }

        onPressed: {
            if (!select){
                select = true;
                selected();
            }
            startMouseX = mouseX;
            startMouseY = mouseY;
        }
    }


}
