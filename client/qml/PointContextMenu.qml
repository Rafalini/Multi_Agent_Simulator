import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: pointContextMenu
    property var pointRepresentation

    onPointRepresentationChanged: {
        if(pointRepresentation) {
            x = pointRepresentation.x;
            y = pointRepresentation.y;
            open();
        }
    }
    MenuItem {
        text: "Usuń punkt"
        onTriggered: {
            map.removePoint(pointContextMenu.pointRepresentation.point);
        }
    }
}
