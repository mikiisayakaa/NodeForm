import QtQuick 2.2

import "../../BaseWidget"


NFCircle1 {
    id: handle

    color: mouseArea.pressed ? Qt.rgba(0.7, 1, 0.7, 1) : Qt.rgba(0.3, 1, 0.3, 1)

    signal connectionStart()
    signal connectionEnd(real x, real y)

    property int flow: 0
    property int index: 0

    signal position(real x, real y)

    property real globalX: x + parent.x
    property real globalY: y + parent.y


    MouseArea{
        id: mouseArea

        anchors.fill: parent

        onPressed: {
            connectionStart();

        }


        onPositionChanged:{
            position(mouseX + globalX, mouseY + globalY);
        }

        onReleased: {
            connectionEnd(mouseX + globalX, mouseY + globalY);
        }


    }
}


