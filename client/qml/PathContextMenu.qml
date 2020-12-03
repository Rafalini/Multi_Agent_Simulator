import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: pathContextMenu
    property var pathRepresentation

    onPathRepresentationChanged: {
        if(pathRepresentation) {
            x = pathRepresentation.x;
            y = pathRepresentation.y;
            open();
        }
    }
    MenuItem {
        text: "Usuń drogę"
        onTriggered: {
            map.removePath(pathRepresentation.path);
        }
    }
}
