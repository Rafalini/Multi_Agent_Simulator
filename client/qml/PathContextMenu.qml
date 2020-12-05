import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: pathContextMenu
    property var pathRepresentation_

    function show(pathRepresentation, x_offset, y_offset) {
        pathRepresentation_ = pathRepresentation;
        x = pathRepresentation.x + x_offset;
        y = pathRepresentation.y + y_offset;
        open();
    }

    MenuItem {
        text: "Usuń drogę"
        onTriggered: {
            map.removePath(pathRepresentation_.path);
            pathRepresentation_ = 0;
        }
    }

    MenuItem {
        text: "Podziel drogę"
        onTriggered: {
            map.splitPath(pathRepresentation_.path, pathContextMenu.x/pathContextMenu.parent.width, pathContextMenu.y/pathContextMenu.parent.height);
            pathRepresentation_ = 0;
        }
    }
}
