import QtQuick 2.15

Rectangle {
    id: pathRepresentation
    property variant path
    height: 2
    color: "black"
    property int x2: path && path.end ? path.end.x*parent.width : 0
    property int y2: path && path.end ? path.end.y*parent.height : 0
    x: path && path.begining ? path.begining.x*parent.width : 0
    y: path && path.begining ? path.begining.y*parent.height : 0

    //signal for Repeater to open ContextMenu
    function clicked(mouse) {}

    width:Math.sqrt(Math.pow(Math.abs(x-x2),2) + Math.pow(Math.abs(y-y2),2));

    transform: Rotation {
        id: rotation
        origin.x: 0
        origin.y: 0
        angle: Math.atan2(y2 - y, x2 - x) * 180 / Math.PI
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: (mouse) => {
                       let theta = rotation.angle * Math.PI / 180;
                       let x_offset = mouse.x * Math.cos(theta);
                       let y_offset = mouse.x * Math.sin(theta);
                       pathRepresentation.clicked(x_offset, y_offset);
                   }
    }
}
