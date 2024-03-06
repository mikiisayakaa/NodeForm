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
        model: ListModel{
            id: lmodel
            Component.onCompleted: {
                var num = nodeFactory.getNodeNum();

                for (var i = 0; i < num; i++){
                    lmodel.append({"nodeName" : nodeFactory.getNodeName(i),
                                  "nodeIndex" : i});
                }
            }
        }

        delegate: NFButtonType1 {
            text: model.nodeName
            onClicked: nodeFactory.createNode(model.nodeIndex)
        }
    }
}

