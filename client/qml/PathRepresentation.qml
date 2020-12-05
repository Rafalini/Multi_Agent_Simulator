import QtQuick 2.15

SimplePathRepresentation {
    id: pathRepresentation
    property variant path
    property bool isDrawMode: false
    x2: path && path.end ? path.end.x*parent.width : 0
    y2: path && path.end ? path.end.y*parent.height : 0
    x: path && path.begining ? path.begining.x*parent.width : 0
    y: path && path.begining ? path.begining.y*parent.height : 0

    //signal for Repeater to open ContextMenu
    function clicked(mouse) {}
    MouseArea {
        enabled: !isDrawMode
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: (mouse) => {
                       let theta = rotation.angle * Math.PI / 180;
                       let x_offset = mouse.x * Math.cos(theta);
                       let y_offset = mouse.x * Math.sin(theta);
                       pathRepresentation.clicked(x_offset, y_offset);
                       mouse.accepted = true;
                   }
    }
}
