import QtQuick 2.2

import CppObjects 1.0
import "../../../../UI/qmlWidgets/Buttons"

Item {
    visible: true
    height: parent.height

    NodeFactory{
        id: nodeFactory
    }

    ListView {
        anchors.fill: parent
        spacing: 10
        model: ["IntNode", "AddIntNode", "MultiplyIntNode", "MaxIntNode", "NegativeIntNode",
                "ClampIntNode"]

        delegate: NFButtonType1 {
            text: modelData
            onClicked: nodeFactory.createNode(index)
        }
    }
}

