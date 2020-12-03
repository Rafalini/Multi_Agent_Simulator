import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: parentItem

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        ScrollBar.vertical: verticalScrollbar
        ScrollBar.horizontal: horizontalScrollbar
        Canvas {
            id:canvas
            anchors.horizontalCenter: parent.horizontalCenter
            width: height
            height: parent.height

            Image {
                anchors.fill: parent
                source: "../resource/MapOfPoland.png"
            }
            MouseArea {
                id: draggableArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: (mouse) => {
                               mapContextMenu.x = mouse.x;
                               mapContextMenu.y = mouse.y;
                               mapContextMenu.open();
                           }
                onWheel: (wheel) => {
                             if(wheel.modifiers & Qt.ControlModifier) {
                                 canvas.height *= wheel.angleDelta.y < 0 || wheel.angleDelta.x < 0 ? 0.9 : 1.1;
                             } else if (wheel.modifiers & Qt.ShiftModifier ) {
                                if(wheel.angleDelta.y < 0 || wheel.angleDelta.x < 0 )
                                    horizontalScrollbar.increase();
                                else
                                    horizontalScrollbar.decrease();
                             } else {
                                 if(wheel.angleDelta.y < 0 || wheel.angleDelta.x < 0 )
                                     verticalScrollbar.increase();
                                 else
                                     verticalScrollbar.decrease();
                             }
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
                    delegate: CityRepresentation {
                        city: modelData
                        function clicked() {
                            cityContextMenu.cityRepresentation = this;
                        }
                    }
                }
            }

            PathContextMenu {
                id: pathContextMenu
            }
            PointContextMenu {
                id: pointContextMenu
            }
            CityContextMenu {
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
                            map.addCity(newCityName.text, mapContextMenu.x/draggableArea.width, mapContextMenu.y/draggableArea.height);
                            newCityName.text = "";
                            mapContextMenu.close();
                        }
                    }
                }
                MenuSeparator{}
                MenuItem {
                    text: "Dodaj punkt"
                    onTriggered: {
                        map.addPoint(mapContextMenu.x/draggableArea.width, mapContextMenu.y/draggableArea.height);
                    }
                }
            }

            onPaint: {}
        }
    }

    ScrollBar {
        id: verticalScrollbar
        visible: true
        anchors.right: scrollView.right
        width: 100
        height: scrollView.height
        anchors.top: scrollView.top
    }
    ScrollBar {
        id: horizontalScrollbar
        visible: true
        anchors.right: scrollView.right
        width: 20
        anchors.bottom: scrollView.bottom
    }

}
