import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: cityContextMenu
    property var cityRepresentation

    function show(cityRepresentation) {
        this.cityRepresentation = cityRepresentation;
        x = cityRepresentation.x;
        y = cityRepresentation.y;
        open();
    }

    MenuItem {
        text: "Dodaj drogę"
        onTriggered: mapFrame.newPathFrom(cityRepresentation)
    }
    MenuItem {
        text: "Usuń miasto"
        onTriggered: {
            if(agents.isCityUsed(cityContextMenu.cityRepresentation.city)) {
                windowDialog.showError("Nie można usunąć miasto ustawionego dla jednego z agentów!");
                return;
            }
            map.removeCity(cityContextMenu.cityRepresentation.city);
        }
    }
    MenuItem {
        text: "Zmień nazwę"
        onTriggered: cityPopup.editCity(cityRepresentation);
    }
}
