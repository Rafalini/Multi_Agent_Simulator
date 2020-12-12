import QtQuick 2.0
import QtQuick.Controls 2.15


TabButton {
    id: button
    MouseArea {
      anchors.fill: parent
      cursorShape: Qt.PointingHandCursor
      onPressed: parent.toggle()
    }
}
