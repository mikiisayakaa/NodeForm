import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../BaseWidget"

Item {
    id: doubleSlider1
    anchors.margins: 5
    width: slider1.width
    height: slider1.height

    property string typeName: "double"

    signal dataSignal(double value)

    NFSlider2 {
        id: slider1
        onValueChanged: {
            doubleSlider1.dataSignal(value)
        }
    }
}
