import QtQuick 2.12

import QtQuick.Controls 2.12

TextField {
    id: textField

    font.family: "Calibri"
    font.pointSize: 8
    color: "white"


    background: Rectangle{
        implicitWidth: 120
        implicitHeight: 8
        color: "black"
        border.color: "green"
        border.width: 2
    }


}
