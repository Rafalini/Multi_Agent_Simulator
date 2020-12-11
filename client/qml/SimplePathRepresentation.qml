import QtQuick 2.15

Rectangle {
    id: pathRepresentation
    height: 2
    color: "black"
    property alias rotation: rotation
    property int x2: 0
    property int y2: 0
    x: 0
    y: 0

    //signal for Repeater to open ContextMenu
    function clicked(mouse) {}
    antialiasing: true
    width:Math.sqrt(Math.pow(Math.abs(x-x2),2) + Math.pow(Math.abs(y-y2),2));

    transform: Rotation {
        id: rotation
        origin.x: 0
        origin.y: 0
        angle: Math.atan2(y2 - y, x2 - x) * 180 / Math.PI
    }
}

