import QtQuick 2.2

import CppObjects 1.0
import "../../../../UI/qmlWidgets/Buttons"

Item {
    visible: true
    height: parent ? parent.height : 0

    NodeFactory{
        id: nodeFactory
    }

    ListView {
        anchors.fill: parent
        spacing: 10
        model: ["VectorDisplay","IntVector4D","VectorConcat","VectorSort","VectorReverse",
                "VectorSplit", "VectorPopback"]

        delegate: NFButtonType1 {
            text: modelData
            onClicked: nodeFactory.createNode(index)
        }
    }
}

