import QtQuick 2.12
import QtQuick.Controls 2.12

SpinBox {
    id: spinBox
    editable: true
    validator: IntValidator{bottom: -1000; top: 1000}

    contentItem: TextInput {
      text: spinBox.textFromValue(spinBox.value, spinBox.locale)

      font: spinBox.font
      color: "#21be2b"
      selectionColor: "#21be2b"
      selectedTextColor: "#ffffff"
      horizontalAlignment: Qt.AlignHCenter
      verticalAlignment: Qt.AlignVCenter

      readOnly: !spinBox.editable
      validator: spinBox.validator
      inputMethodHints: Qt.ImhFormattedNumbersOnly
    }

    up.indicator: Rectangle {
      x: spinBox.mirrored ? 0 : parent.width - width
      height: parent.height
      implicitWidth: 40
      implicitHeight: 40
      color: spinBox.up.pressed ? "#e4e4e4" : "#f6f6f6"
      border.color: enabled ? "#21be2b" : "#bdbebf"

      Text {
          text: "+"
          font.pixelSize: spinBox.font.pixelSize * 2
          color: "#21be2b"
          anchors.fill: parent
          fontSizeMode: Text.Fit
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
      }
    }

    down.indicator: Rectangle {
      x: spinBox.mirrored ? parent.width - width : 0
      height: parent.height
      implicitWidth: 40
      implicitHeight: 40
      color: spinBox.down.pressed ? "#e4e4e4" : "#f6f6f6"
      border.color: enabled ? "#21be2b" : "#bdbebf"

      Text {
          text: "-"
          font.pixelSize: spinBox.font.pixelSize * 2
          color: "#21be2b"
          anchors.fill: parent
          fontSizeMode: Text.Fit
          horizontalAlignment: Text.AlignHCenter
          verticalAlignment: Text.AlignVCenter
      }
    }

    background: Rectangle {
      implicitWidth: 140
      border.color: "#bdbebf"
    }
}
