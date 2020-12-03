import QtQuick 2.15

Rectangle {
    id: pathRepresentation
    property variant path
    height: 1
    color: "black"
    property int x2: path && path.end ? path.end.x*parent.width : 0
    property int y2: path && path.end ? path.end.y*parent.height : 0
    x: path && path.begining ? path.begining.x*parent.width : 0
    y: path && path.begining ? path.begining.y*parent.height : 0

    //signal for Repeater to open ContextMenu
    function clicked() {}

    width:Math.sqrt(Math.pow(Math.abs(x-x2),2) + Math.pow(Math.abs(y-y2),2));

    transform: Rotation {
        origin.x: 0
        origin.y: 0
        angle: Math.atan2(y2 - y, x2 - x) * 180 / Math.PI
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: pathRepresentation.clicked();
    }
}
