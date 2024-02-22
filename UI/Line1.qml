import QtQuick 2.2
import QtQuick.Shapes 1.12

Shape{
    id: shape

    z: parent.z + 5

    property real x1: 0
    property real x2: 0
    property real y1: 0
    property real y2: 0

    property real deltaX1: 0
    property real deltaX2: 0
    property real deltaY1: 0
    property real deltaY2: 0

    property color colorValue: "white"
    property bool select: false
    property real lineWidth: 2

    signal selected()

    ShapePath {
        id: path

        startX: shape.x1
        startY: shape.y1

        strokeColor: colorValue
        strokeWidth: lineWidth

        PathLine{x: shape.x2; y: shape.y2}

    }


    MouseArea{
        id: mouseArea

        x: shape.x1 < shape.x2 ? shape.x1 : shape.x2
        y: shape.y1 < shape.y2 ? shape.y1 : shape.y2
        width: Math.abs(shape.x1 - shape.x2)
        height: Math.abs(shape.y1 - shape.y2)

        propagateComposedEvents: true

        onClicked: {

            //judge if the click is on the line
            var perpendicularX = shape.y2 - shape.y1;
            var perpendicularY = -(shape.x2 - shape.x1);
            var dist = perpendicularX * perpendicularX + perpendicularY * perpendicularY

            var threshold = 0.0001;
            if (dist < threshold){
                return;
            }

            dist = 1 / Math.sqrt(dist);
            // 5 is area width of the line
            var offsetX = perpendicularX * dist * 5;
            var offsetY = perpendicularY * dist * 5;

            //point coordinates for the parallelogram
            var aX = shape.x1 + offsetX;
            var aY = shape.y1 + offsetY;
            var bX = shape.x1 - offsetX;
            var bY = shape.y1 - offsetY;
            var cX = shape.x2 + offsetX;
            var cY = shape.y2 + offsetY;
            var pX = mouseX + x;
            var pY = mouseY + y;

            //vectors
            var v1X = bX - aX;
            var v1Y = bY - aY;
            var v2X = cX - aX;
            var v2Y = cY - aY;
            var vpX = pX - aX;
            var vpY = pY - aY;

            var d = 1 / (v1X * v2Y - v2X * v1Y);

            var m1 = (vpX * v2Y - v2X * vpY) * d;
            var m2 = (v1X * vpY - vpX * v1Y) * d;

            if (m1 >= 0 && m2 >= 0 && m1 <= 1 && m2 <= 1){
                if (!select){
                    selected();
                }
                mouse.accepted = true;
            }
            else{
                mouse.accepted = false;
            }
        }
    }
}
