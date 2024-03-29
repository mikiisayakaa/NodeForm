import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "../../../../../UI/BaseWidget"

Item {
    id: intSlider1
    width: slider1.width
    height: slider1.height

    property string typeName: "int"

    signal dataSignal(int value)

    NFSlider2 {
        id: slider1
        from: -100
        to: 100
        value: 0
        onValueChanged: {
            intSlider1.dataSignal(Math.round(value))
        }

    }

    Component.onCompleted:{
        slider1.onValueChanged();
    }

}


