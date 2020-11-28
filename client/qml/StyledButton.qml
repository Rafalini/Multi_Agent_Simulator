import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    width: 200
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onPressed: parent.activate()
    }
    function activate() {}
}
