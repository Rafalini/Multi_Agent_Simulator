import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: parentItem

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

            Repeater {
                id: pathRepeater
                anchors.fill: parent
                model: map.paths
                delegate: PathRepresentation {
                    path: modelData
                    function clicked() {
                        pathContextMenu.pathRepresentation = this;
                    }
                }
            }

            Repeater {
                id: pointRepeater
                anchors.fill: parent
                model: map.points
                delegate: PointRepresentation {
                    point: modelData
                    function clicked() {
                        pointContextMenu.pointRepresentation = this;
                    }
                }
            }

            Repeater {
                id: cityRepeater
                anchors.fill: parent
                model: map.cities
                delegate: PointRepresentation {
                    cities: modelData
                    function clicked() {
                        cityContextMenu.cityRepresentation = this;
                    }
                }
            }
        }

        Menu {
            id: pathContextMenu
        }
        Menu {
            id: pointContextMenu
        }
        Menu {
            id: cityContextMenu
        }

        Menu {
            id: mapContextMenu
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
