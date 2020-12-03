import QtQuick 2.15
import QtQuick.Controls 2.15

Menu {
    id: cityContextMenu
    property var cityRepresentation
    onCityRepresentationChanged: {
        if(cityRepresentation) {
            x = cityRepresentation.x;
            y = cityRepresentation.y;
            open();
        }
    }

    MenuItem {
        text: "Usuń miasto"
        onTriggered: {
            map.removeCity(cityContextMenu.cityRepresentation.city);
        }
    }
}
