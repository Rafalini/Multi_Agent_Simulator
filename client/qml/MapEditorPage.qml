import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: parentItem
    property list<CityRepresentation> cities
    property list<PointRepresentation> points
    property list<PathRepresentation> paths
    property var cityComponent
    property var pointComponent
    property var pathComponent

    Connections {
        target: map
        function onCityAdded(city) {
            let newCityRepresentation = cityComponent.createObject(draggableArea, {city: city});
            cities.push(newCityRepresentation);
        }

        function onDuplicateCityName(name) {
            windowDialog.showError("Miasto nie dodane.\nPowód: Miasto o nazwie " + name + " już istnieje.");
        }

        function onPointAdded(point) {
            let newPointRepresentation = pointComponent.createObject(draggableArea, {point: point});
            points.push(newPointRepresentation);
        }
    }

    Component.onCompleted: {
        let cityArray = [];
        let currentCities = map.cities;
        cityComponent = Qt.createComponent("CityRepresentation.qml");
        for(let i = 0; i < currentCities.length; ++i) {
            let city = currentCities[i];
            let newCityRepresentation = cityComponent.createObject(draggableArea, {city: city});
            cities.push(newCityRepresentation);
        }
        pointComponent = Qt.createComponent("PointRepresentation.qml");
        let pointArray = [];
        let currentPoints = map.points;
        for(let j = 0; j < currentPoints.length; ++j) {
            let point = currentPoints[j];
            let newPointRepresentation = pointComponent.createObject(draggableArea, {point: point});
            points.push(newPointRepresentation);
        }

        pathComponent = Qt.createComponent("PathRepresentation.qml");
        let pathArray = [];
        let currentPaths = map.paths;
        for(let l = 0; l < currentPaths.length; ++l) {
            let path = currentPaths[l];
            let newPathRepresentation = pathComponent.createObject(draggableArea, {path: path});
            paths.push(newPathRepresentation);
        }
    }

    Image {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width
        source: "../resource/MapOfPoland.png"
    }
    Canvas {
        id:canvas
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width

        MouseArea {
            id: draggableArea
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            onClicked: (mouse) => {
                           contextMenu.x = mouse.x;
                           contextMenu.y = mouse.y;
                           contextMenu.open();
                       }
            function openPointContextMenu(point) {
                pointContextMenu.pointRepresentation = point;
            }
            function openCityContextMenu(city) {
                cityContextMenu.cityRepresentation = city;
            }
            function deletePath(pathRepresentation) {
                parentItem.paths = Array.from(parentItem.paths).filter(r => r !== pathRepresentation);
                pathRepresentation.destroy();
            }
            function deleteCity(cityRepresentation) {
                parentItem.cities = Array.from(parentItem.cities).filter(r => r !== cityRepresentation);
                cityRepresentation.destroy();
            }
            function deletePoint(pointRepresentation) {
                parentItem.points = Array.from(parentItem.points).filter(r => r !== pointRepresentation);
                pointRepresentation.destroy();
            }
        }

        Menu {
            id: pointContextMenu
            property var pointRepresentation

            onPointRepresentationChanged: {
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
        }


        Menu {
            id: cityContextMenu
            property var cityRepresentation
            onCityRepresentationChanged: {
                x = cityRepresentation.x;
                y = cityRepresentation.y;
                open();
            }

            MenuItem {
                text: "Usuń miasto"
                onTriggered: {
                    map.removeCity(cityContextMenu.cityRepresentation.city);
                }
            }
        }

        Menu {
            id: contextMenu
            Menu {
                title: "Dodaj miasto"
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
                        map.addCity(newCityName.text, contextMenu.x/draggableArea.width, contextMenu.y/draggableArea.height);
                        newCityName.text = "";
                        contextMenu.close();
                    }
                }
            }
            MenuSeparator{}
            MenuItem {
                text: "Dodaj punkt"
                onTriggered: {
                    map.addPoint(contextMenu.x/draggableArea.width, contextMenu.y/draggableArea.height);
                }
            }
        }

        onPaint: {}

    }
}
