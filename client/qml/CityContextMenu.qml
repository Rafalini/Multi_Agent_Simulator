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
        onTriggered: {
            parent.newPathFrom(cityRepresentation);
        }
    }
    MenuItem {
        text: "Usuń miasto"
        onTriggered: {
            map.removeCity(cityContextMenu.cityRepresentation.city);
        }
    }
    Menu {
        title: "Zmień nazwę"
        MenuItem {
            onTriggered: activate();
            TextInput {
                leftPadding: 4
                onVisibleChanged: if(visible) forceActiveFocus();
                verticalAlignment: Text.AlignVCenter
                width: parent.width-80
                height: parent.height
                id: newCityName
            }
            StyledButton {
                anchors.left: newCityName.right
                height: newCityName.height
                width: 80
                text: "Dodaj"
                function activate() { parent.activate() }
            }
            function activate() {
                if(newCityName.text == "") {
                    windowDialog.showError("Nazwa miasta nie może być pusta!");
                    return;
                }
                cityRepresentation.city.name = newCityName.text;
                newCityName.text = "";
                cityContextMenu.close();
            }
        }
    }
}
