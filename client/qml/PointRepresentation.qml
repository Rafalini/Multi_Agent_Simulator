import QtQuick 2.15

Item {
    id: pointRepresentation
    required property variant point
    property alias rec: rec

    Component.onCompleted: {
        initilize();
    }

    function initilize() {
        x = point.x*parent.width;
        y = point.y*parent.height;
    }

    onXChanged: point.x = x/parent.width;
    onYChanged: point.y = y/parent.height;


    Connections {
        target: parent
        function onWidthChanged() {
            x = point.x*parent.width;
        }
        function onHeightChanged() {
            y = point.y*parent.height;
        }
    }

    Drag.active: draggedRec.drag.active
    Drag.hotSpot.x: 0
    Drag.hotSpot.y: 0

    Rectangle {
        id: rec
        anchors.verticalCenter: parent.top
        anchors.horizontalCenter: parent.left
        color: "red"
        width: 14
        height: 14
        MouseArea {
            id: draggedRec
            anchors.fill: parent
            drag.target: parent.parent
            drag.minimumX: 0
            drag.maximumX: parent.parent.parent.width
            drag.minimumY: 0
            drag.maximumY: parent.parent.parent.height
            drag.smoothed: false
            cursorShape: Qt.PointingHandCursor
//            drag.onDragFinished: pointRepresentation.dragged()
//            onClicked: contextMenu.open();
        }
    }
}
