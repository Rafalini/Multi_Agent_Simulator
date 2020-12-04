import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: pathContextMenu
    property var pathRepresentation

    function show(pathRepresentation, x_offset, y_offset) {
        this.pathRepresentation = pathRepresentation;
        x = pathRepresentation.x + x_offset;
        y = pathRepresentation.y + y_offset;
        open();
    }

    MenuItem {
        text: "Usuń drogę"
        onTriggered: {
            map.removePath(pathRepresentation.path);
        }
    }
}
