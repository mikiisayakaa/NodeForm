import QtQuick 2.2

import QtQuick.Controls 2.12

import QtQuick.Dialogs 1.3

Item {
    id: item
    width: 50
    height: 25
    visible: true
    anchors.margins: 5

    property string imagePath: null
    property string typeName: "QString"

    signal dataSignal(string value);

    Button{
        id: button
        anchors.fill: parent
        focusPolicy: Qt.NoFocus
        focus: false
        text: "File"

        contentItem: Text{
            text: button.text
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: "white"
            font.family: "Calibri"
            font.pointSize: 8
        }

        background: Rectangle{
            id: bgd
            radius: 2
            implicitWidth: 50
            implicitHeight: 25
            color: "black"
        }

        onClicked:{
            fileDialog.visible = true;
        }
    }

    FileDialog {
        id: fileDialog
        title: "Select an Image file:"
        folder: "."

        onAccepted:{
            if (fileUrl != ""){
                dataSignal(fileUrl);
            }
        }

    }
}
