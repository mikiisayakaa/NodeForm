import QtQuick 2.12
import QtQuick.Controls 2.12

Button {
    id: control
    z: parent.z
    focusPolicy: Qt.NoFocus

    contentItem: Text {
      text: control.text
      font.family: "Calibri"
      font.bold: true
      opacity: enabled ? 0.8 : 0.3
      color: control.down ? "#17a81a" : "#21be2b"
      horizontalAlignment: Text.AlignHCenter
      verticalAlignment: Text.AlignVCenter
      elide: Text.ElideRight
    }

    background: Rectangle {
      implicitWidth: 100
      implicitHeight: 40
      opacity: enabled ? 1 : 0.3
      color: Qt.rgba(0.1, 0.1, 0.1, 1)
      border.color: control.down ? "#17a81a" : "#21be2b"
      border.width: 1
      radius: 4
    }

}
