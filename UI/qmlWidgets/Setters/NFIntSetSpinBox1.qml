import QtQuick 2.2

import "../../BaseWidget"

NFSpinBox1 {
    value: 0
    validator: IntValidator{bottom: -1000; top: 1000}

    property string typeName: "int"

    signal dataSignal(int value)

    onValueChanged: {
        dataSignal(value);
    }

    Component.onCompleted: {
        dataSignal(0);
    }

}
