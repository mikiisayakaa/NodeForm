import QtQuick 2.2

import "../../../BaseWidget"

NFText1 {
    property int cppData: 0

    property string cppType: "int"
    property string qmlType: "int"

    text: cppData
    color: "white"

    anchors.rightMargin: 0
}
