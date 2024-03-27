import QtQuick 2.12

import QtQuick.Controls 2.12

Rectangle {
    width: 212
    height: 120
    color: "black"

    property bool curImage: true

    anchors.margins: 5

    property string cppData: null
    property string cppType: "QImage"
    property string qmlType: "QString"

    property string preData: null


    Image{
        id: img1
        anchors.fill: parent
        source: cppData
        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
            if (status === Image.Ready){
                preData = cppData;
            }
        }
    }

    Image{
        id: img2
        anchors.fill: parent
        source: preData
        fillMode: Image.PreserveAspectFit


    }
}
