import QtQuick 2.2


Rectangle{
    width: 12
    height: 12
    anchors.margins: 5
    color: Qt.rgba(0,0,0,0)

    Canvas {
        id: canvas
        anchors.fill: parent

        property color triColor: Qt.rgba(0.3, 1, 0.3, 1);

        onPaint: {
            var ctx = getContext("2d");
            ctx.fillStyle = triColor

            ctx.beginPath();
            ctx.moveTo(parent.width / 2, 0);
            ctx.lineTo(parent.width, parent.height);
            ctx.lineTo(0, parent.height);
            ctx.closePath();

            ctx.fill();
        }
    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent
        propagateComposedEvents: true

        onPressed:{
            canvas.triColor = Qt.rgba(0.7, 1, 0.7, 1);
            canvas.requestPaint()
        }

        onReleased: {
            canvas.triColor = Qt.rgba(0.3, 1, 0.3, 1);
            canvas.requestPaint()
        }
    }
}
