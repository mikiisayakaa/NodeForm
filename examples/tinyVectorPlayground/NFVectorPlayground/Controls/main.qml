import QtQuick 2.2
import QtQuick.Window 2.2

import "../../../../UI/qmlWidgets/Buttons"

Window {
    id: mainwindow
    visible: true
    width: 1024
    height: 768
    color: Qt.rgba(0, 0, 0, 1.0)

    ButtonManager{
        z: parent.z + 1000
    }
}
