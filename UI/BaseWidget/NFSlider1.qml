import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Slider{
    width: 100

    anchors.margins: 5
    value: 50
    minimumValue: 0
    maximumValue: 100

    style: SliderStyle {
        handle: Rectangle {
            implicitHeight: 10
            implicitWidth: 10
            radius: width / 2
            color: control.pressed ? "lightblue" : "blue"
        }

        groove: Rectangle {
            implicitHeight: 4
            radius: implicitHeight / 2

            color: "lightgray"
        }
    }
}

