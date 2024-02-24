import QtQuick 2.2

import "../../BaseWidget"

NodestText1 {
    property int dataValue: 0
    property bool valid: false
    property string typeName: "int"

    text: dataValue
    color: valid ? "white" : "red"

    anchors.rightMargin: 0
}
