import QtQuick 2.15
import QtQuick.Controls 2.15

Button {
    width: 200
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: parent.clicked()
    }
    onDoubleClicked: {clicked(); clicked();}
    Keys.onEnterPressed: clicked()
    Keys.onReturnPressed: clicked()
}
