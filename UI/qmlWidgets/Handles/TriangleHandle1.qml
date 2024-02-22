import QtQuick 2.2

import "../../BaseWidget"

TriangleType1{

    property int flow: 0
    property int index: 0

    signal connectionStart(int flow, int index)
    signal connectionEnd(real x, real y)

    signal position(real x, real y)

    MouseArea{
        anchors.fill: parent

//        onPressed: {
//            connectionStart(flow, index);
//        }

//        onReleased:{
//            if (containsMouse){
//                connectionEnd(flow, index);
//            }
//        }
    }
}
