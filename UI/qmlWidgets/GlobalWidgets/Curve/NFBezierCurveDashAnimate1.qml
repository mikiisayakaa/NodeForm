import QtQuick 2.2
import QtQuick.Shapes 1.12

import "../Curve"

NFBezierCurve2 {

    shapePath.strokeStyle : ShapePath.DashLine
    shapePath.dashPattern : [5,5]

    SequentialAnimation {
        id: dashAnimation

        running: true


        NumberAnimation {
            target: shapePath
            property: "dashOffset"
            to: -5 * shapePath.strokeWidth
            duration: 1000
            loops: Animation.Infinite
        }

    }
}
