import QtQuick 2.15

Item {
    id: pointRepresentation
    property variant point
    property alias rec: rec

    //signal for Repeater to open ContextMenu
    function clicked() {}

    x: point.x*parent.width
    y: point.y*parent.height

    //update in model only if change caused by drag, not parent size
    onXChanged: if(draggedRec.drag.active) point.x = x/parent.width;
    onYChanged: if(draggedRec.drag.active) point.y = y/parent.height;

    Drag.active: draggedRec.drag.active
    Drag.hotSpot.x: 0
    Drag.hotSpot.y: 0
    property var color: "blue"
    Rectangle {
        id: rec
        anchors.verticalCenter: parent.top
        anchors.horizontalCenter: parent.left
        color: parent.color
        width: 14
        height: 14
        MouseArea {
            id: draggedRec
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            anchors.fill: parent
            drag.target: pointRepresentation
            drag.minimumX: 0
            drag.maximumX: pointRepresentation.parent.width
            drag.minimumY: 0
            drag.maximumY: pointRepresentation.parent.height
            drag.smoothed: false
            cursorShape: Qt.PointingHandCursor
            onClicked: pointRepresentation.clicked();
        }
    }
}
