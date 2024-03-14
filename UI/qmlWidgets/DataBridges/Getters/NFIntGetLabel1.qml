import QtQuick 2.2

import "../../../BaseWidget"

NFText1 {
    property int cppData: 0
    property bool valid: false

    property string cppType: "int"
    property string qmlType: "int"

    text: cppData
    color: valid ? "white" : "red"

    anchors.rightMargin: 0
}
