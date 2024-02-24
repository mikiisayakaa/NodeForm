import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Controls.Styles 1.4

//adapted from Qt's help documents

Slider {
    id: control
    padding: 4

    background: Rectangle {
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 150
        implicitHeight: 4
        width: control.availableWidth
        height: implicitHeight
        radius: 2
        color: "#bdbebf"

        //give different color to the left part of the groove
        Rectangle {
          width: control.visualPosition * parent.width
          height: parent.height
          color: "#21be2b"
          radius: 2
        }
    }

    handle: Rectangle {
        x: control.leftPadding + control.visualPosition * (control.availableWidth - width)
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 12
        implicitHeight: 12
        radius: implicitWidth / 2
        color: control.pressed ? "#c0c0c0" : "#f6f6f6"
        border.color: "#080808"
        border.width: 1
    }
}
