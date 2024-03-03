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

    //simply set focus to false to prevent the nodeBase
    //from grabbing key focus accidentally

    property real scaleValue: parent.scaleValue
    property real minWidth: 0

    //why not move scale to Background level?
    //background level scale does not work well with making connections
    transform: Scale{
        origin.x: nodeBase.parent.width / 2 - nodeBase.x
        origin.y: nodeBase.parent.height / 2 - nodeBase.y
        xScale: nodeBase.scaleValue
        yScale: nodeBase.scaleValue
    }

    z: parent.z + 10

    color: Qt.rgba(0.2,0.2,0.2,1.0)

    property bool selected: false
    property bool movable: false

    border.width: 1
    border.color: selected ? "yellow" : "white"

    signal position(real x, real y)
    signal select()


    MouseArea{
        id: mouseArea

        anchors.fill: parent

        preventStealing: true

        property real startMouseX: 0
        property real startMouseY: 0

        onPositionChanged: {
            //why not using drag here?
            //drag does not work well with scale, after scaling,
            //the actual move distance of the mouse will not be the same as
            //move distance of the node on the screen
            if (movable){
                nodeBase.x += mouseX - startMouseX;
                nodeBase.y += mouseY - startMouseY;
            }
        }

        onPressed: {
            if (!selected){
                //this key focus will pass keyboard input to background
                focus = true;
                select();
            }

            if (movable){
                startMouseX = mouseX;
                startMouseY = mouseY;
            }
        }
    }


}
