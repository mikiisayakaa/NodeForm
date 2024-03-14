import QtQuick 2.2

import "../../../BaseWidget"

NFTextInput1 {
    text: "0"
    signal dataSignal(int value)

    property string cppType: "int"
    property string qmlType: "int"

    enabled: parent? parent.select : false

    onEditingFinished: {
        var value = parseInt(text);
        if (!isNaN(value)){
            value = value > 1000 ? 1000 : (value < -1000 ? -1000 : value)
            dataSignal(value);
            text = value.toString();
        }
        else{
            text = "0";
            dataSignal(0);
        }
    }

    Component.onCompleted: {
        dataSignal(0);
    }

}
