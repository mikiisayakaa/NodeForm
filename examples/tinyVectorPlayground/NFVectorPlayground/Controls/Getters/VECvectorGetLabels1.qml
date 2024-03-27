import QtQuick 2.12

import QtQuick.Controls 2.12

Rectangle {
    id: labels
    color: "transparent"

    property var cppData: []
    property string cppType: "std::vector<int>"
    property string qmlType: "QVariantList"

    property real blockHeight: 32

    anchors.margins: 5


    width: row.width
    height: blockHeight

    property real preWidth

    Row{
        id: row
        anchors.right: parent.right
        spacing: -5
        Repeater {
            id: repeater

            model: cppData

            delegate: ItemDelegate {

                contentItem: Text{
                    id: itemText
                    text: modelData
                    color: "white"
                    font.family: "Calibri"
                    anchors.horizontalCenter: itemBgd.horizontalCenter
                    anchors.verticalCenter: itemBgd.verticalCenter
                }

                background: Rectangle{
                    id: itemBgd
                    width: itemText.contentWidth + 15
                    height: blockHeight
                    color: "black"
                    radius: 4
                    border.color:"#21be2b"
                    border.width: 1
                }
            }

        }
    }

    onWidthChanged: {
        if (preWidth == labels.width){
            return;
        }


        if(labels.parent){
            if (labels.width > labels.parent.minWidth - 30){
                labels.parent.width += labels.width - preWidth;
            }
            else{
                labels.parent.width = labels.parent.minWidth;
            }
        }
        preWidth = labels.width;

    }

}
