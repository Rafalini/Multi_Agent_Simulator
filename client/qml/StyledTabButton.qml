import QtQuick 2.0
import QtQuick.Controls 2.15


TabButton {
    id: button

//    implicitHeight: parent.height

    background: Rectangle {
        border.color: button.enabled ? "white" : "black"
        color: button.enabled ? root.lightblue : root.darkblue
    }

    MouseArea {
      anchors.fill: parent
      cursorShape: Qt.PointingHandCursor
      onPressed: parent.toggle()
    }
}
