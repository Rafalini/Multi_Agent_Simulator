import QtQuick 2.15

Rectangle {
    id: pathRepresentation
    required property variant path
    height: 1
    color: "black"
    property int x2
    property int y2
    Component.onCompleted: {
        let pointA = path.begining;
        let pointB = path.end;
        x = pointA.x*parent.width;
        y = pointA.y*parent.height;
        x2 = pointB.x*parent.width;
        y2 = pointB.y*parent.height;
    }

    Connections {
        target: path
        function onAboutToDelete() {
            parent.deletePath(pathRepresentation);
        }
    }

    width:Math.sqrt(Math.pow(Math.abs(x-x2),2) + Math.pow(Math.abs(y-y2),2));

    transform: Rotation {
        id: rot
        origin.x: 0
        origin.y: 0
        angle: Math.atan2(y2 - y, x2 - x) * 180 / Math.PI
    }
    Connections {
        target: path.begining
        function onXChanged() {
            x = path.begining.x*parent.width;
        }
        function onYChanged() {
            y = path.begining.y*parent.width;
        }
    }

    Connections {
        target: path.end
        function onXChanged() {
            x2 = path.end.x*parent.width;
        }
        function onYChanged() {
            y2 = path.end.y*parent.width;
        }
    }

    Connections {
        target: parent
        function onWidthChanged() {
            x = path.begining.x*parent.width;
            x2 = path.end.x*parent.width;
        }
        function onHeightChanged() {
            y = path.begining.y*parent.height;
            y2 = path.end.y*parent.height;
        }
    }
    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        //            onClicked: contextMenu.open();
    }
}
