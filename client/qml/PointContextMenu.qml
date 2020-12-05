import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: pointContextMenu
    property var pointRepresentation


    function show(pointRepresentation) {
        this.pointRepresentation = pointRepresentation;
        x = pointRepresentation.x;
        y = pointRepresentation.y;
        open();
    }

    MenuItem {
        text: "Usuń punkt"
        onTriggered: {
            map.removePoint(pointContextMenu.pointRepresentation.point);
        }
    }
    MenuItem {
        text: "Dodaj drogę"
        onTriggered: {
            mapFrame.newPathFrom(pointRepresentation);
        }
    }
    MenuItem {
        text: "Zmień w miasto"
        onTriggered: {
            cityPopup.promotePointToCity(pointRepresentation);
        }
    }
}
