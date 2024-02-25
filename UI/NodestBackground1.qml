import QtQuick 2.2

Rectangle {
    id: bgd
    width: 100000
    height: 100000
    color: Qt.rgba(0.1, 0.1, 0.1, 1.0)
    focus: true
    x: -50000
    y: -50000

    signal deletePressed()
    signal preCopy()
    signal copy()
    signal deselect()

    property real scaleValue: 1

    MouseArea{
        objectName: "bgdMouseArea"
        anchors.fill: parent

        drag.target: bgd

        onClicked:{
            deselect();
        }

        onWheel:{
            scaleValue += wheel.angleDelta.y / 1200;
            if (scaleValue < 0.2){
                scaleValue = 0.2;
            }
            else if (scaleValue > 3){
                scaleValue = 3;
            }
        }

    }



    Keys.onPressed:{
        if (event.key === Qt.Key_Delete){
            deletePressed();
        }
        else if (event.modifiers & Qt.ControlModifier){
            if (event.key === Qt.Key_C){
                preCopy();
            }
            else if (event.key === Qt.Key_V){
                copy();
            }
        }
    }

}
