import QtQuick 2.2
import QtQuick.Shapes 1.12

Shape{
    id: shape

    z: parent? parent.z + 5 : 5

    property real x1: handle1 ? handle1.parent.x + handle1.x + handle1.width / 2 : 0
    property real x2: handle2 ? handle2.parent.x + handle2.x + handle2.width / 2 : 0
    property real y1: handle1 ? handle1.parent.y + handle1.y + handle1.height / 2 : 0
    property real y2: handle2 ? handle2.parent.y + handle2.y + handle2.height / 2 : 0


    property var handle1: null
    property var handle2: null


    property color colorValue: selected ? "yellow" : "white"
    property bool selected: false
    property real lineWidth: 2

    property real scaleValue: parent.scaleValue

    signal select()

    transform: Scale{
        origin.x: shape.parent ? shape.parent.width / 2 - shape.x : 0
        origin.y: shape.parent ? shape.parent.height / 2 - shape.y : 0
        xScale: shape.scaleValue
        yScale: shape.scaleValue
    }

    ShapePath {
        id: path

        startX: shape.x1
        startY: shape.y1

        strokeColor: colorValue
        strokeWidth: lineWidth
        fillColor: Qt.rgba(0,0,0,0)

        PathQuad{x: shape.x1 * 0.5 + shape.x2 * 0.5;
                 y: shape.y1 * 0.5 + shape.y2 * 0.5;
                 controlX: shape.x1 < shape.x2 ? shape.x1 * 0.8 + shape.x2 * 0.2 :
                            shape.x1 * 1.2 - shape.x2 * 0.2;
                 controlY: shape.y1}
        PathQuad{x: shape.x2;
                 y: shape.y2;
                 controlX: shape.x1 < shape.x2 ? shape.x1 * 0.2 + shape.x2 * 0.8 :
                            -shape.x1 * 0.2 + shape.x2 * 1.2;
                 controlY: shape.y2}


    }

    //use this to visualize mouseArea

//    ShapePath{
//        startX: shape.x1
//        startY: shape.y1

//        fillColor: "red"

//        PathLine{x: shape.x1 < shape.x2 ? shape.x1 * 0.88 + shape.x2 * 0.12 :
//                                          shape.x1 * 1.12 - shape.x2 * 0.12;
//                 y: shape.y1}
//        PathLine{x: shape.x2; y: shape.y2}
//        PathLine{x: shape.x1 < shape.x2 ? shape.x1 * 0.12 + shape.x2 * 0.88 :
//                                          -shape.x1 * 0.12 + shape.x2 * 1.12;
//                 y: shape.y2}
//        PathLine{x: shape.x1; y: shape.y1}
//    }



    MouseArea{
        id: mouseArea

        x: (shape.x1 < shape.x2 ? shape.x1 : shape.x2) - 5
        y: (shape.y1 < shape.y2 ? shape.y1 : shape.y2) - 5
        width: Math.abs(shape.x1 - shape.x2) + 5
        height: Math.abs(shape.y1 - shape.y2) + 5

        propagateComposedEvents: true

        onClicked: {

            //judge if the click is on the line

            //point coordinates for the parallelogram
            var aX = shape.x1;
            var aY = shape.y1;
            var bX = shape.x1 < shape.x2 ? shape.x1 * 0.88 + shape.x2 * 0.12 :
                                              shape.x1 * 1.12 - shape.x2 * 0.12;
            var bY = shape.y1;
            var cX = shape.x1 < shape.x2 ? shape.x1 * 0.12 + shape.x2 * 0.88 :
                                           -shape.x1 * 0.12 + shape.x2 * 1.12
            var cY = shape.y2;
            var pX = mouseX + x;
            var pY = mouseY + y;

            //vectors
            var v1X = bX - aX;
            var v1Y = bY - aY;
            var v2X = cX - aX;
            var v2Y = cY - aY;
            var vpX = pX - aX;
            var vpY = pY - aY;

            var d = v1X * v2Y - v2X * v1Y;
            var cos = (v1X * v2X + v1Y * v2Y) / (Math.sqrt(v1X * v1X + v1Y * v1Y) *
                                                 Math.sqrt(v2X * v2X + v2Y * v2Y));
            var doSelect = false;

            var threshold = 15;

            //process horizontal and vertical conditions
            if (Math.abs(cos) < 0.01 || Math.abs(cos) > 0.999 || isNaN(cos)){
                if (Math.abs(vpX) < threshold
                    && Math.max(aY, cY) > pY && Math.min(aY, cY) < pY){
                    doSelect = true;
                }
                else if (Math.abs(vpY) < threshold
                         && Math.max(aX, cX) > pX && Math.min(aX, cX) < pX){
                    doSelect = true;
                }

            }
            else{
                d = 1 / d;

                var m1 = (vpX * v2Y - v2X * vpY) * d;
                var m2 = (v1X * vpY - vpX * v1Y) * d;

                doSelect = m1 >= 0 && m2 >= 0 && m1 <= 1 && m2 <= 1;
            }


            if (doSelect){
                if (!selected){
                    select();
                }
                mouse.accepted = true;
            }
            else{
                mouse.accepted = false;
            }
        }
    }


}
