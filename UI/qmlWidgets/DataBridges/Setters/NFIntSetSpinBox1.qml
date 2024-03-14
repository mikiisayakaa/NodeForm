import QtQuick 2.2

import "../../../BaseWidget"

NFSpinBox1 {
    value: 0
    validator: IntValidator{bottom: -1000; top: 1000}

    property string cppType: "int"
    property string qmlType: "int"

    signal dataSignal(int value)

    onValueChanged: {
        dataSignal(value);
    }

    Component.onCompleted: {
        dataSignal(0);
    }

}
