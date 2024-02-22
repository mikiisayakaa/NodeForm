import QtQuick 2.12

import QtQuick.Controls 2.12

Rectangle {
    width: 212
    height: 120
    color: "black"

    property bool curImage: true

    anchors.margins: 5

    property string dataValue: null
    property string preValue: null

    property bool valid: false
    property string typeName: "QImage"

    Image{
        id: img1
        anchors.fill: parent
        source: dataValue
        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
            if (status === Image.Ready){
                preValue = dataValue;
            }
        }
    }

    Image{
        id: img2
        anchors.fill: parent
        source: preValue
        fillMode: Image.PreserveAspectFit


    }
}
