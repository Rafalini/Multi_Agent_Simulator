import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Page {
    id: parentItem
    title: "Edytuj mapę"

    ScrollView {
        id: scrollView
        anchors.fill: parent
        clip: true
        ScrollBar.vertical: verticalScrollbar
        ScrollBar.horizontal: horizontalScrollbar
        Rectangle {
            id: mapFrame
            anchors.horizontalCenter: parent.horizontalCenter
            width: height
            height: parent.height > parent.width? parent.width : parent.height
            Image {
                anchors.fill: parent
                source: "../resource/MapOfPoland.png"
            }

            function finishDrawingPathAt(endPoint) {
                map.addPath(startPoint, endPoint);
                drawing = false;
                startPoint = null;
            }

            property bool drawing: false
            property var startPoint: null

            function newPathFrom(pointRepresentation) {
                startPoint = pointRepresentation.point;
                drawing = true;
            }

            SimplePathRepresentation {
                id: drawingPath
                visible: parent.drawing
                x: mapFrame.drawing ? mapFrame.startPoint ? mapFrame.startPoint.x*mapFrame.width : 0 : 0
                y: mapFrame.drawing ? mapFrame.startPoint ? mapFrame.startPoint.y*mapFrame.height : 0 : 0
                x2: mapFrame.drawing ? draggableArea.mouseX : 0
                y2: mapFrame.drawing ? draggableArea.mouseY : 0
            }

            MouseArea {
                id: draggableArea
                anchors.fill: parent
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onClicked: (mouse) => {
                               if(!mapContextMenu.visible)
                                    mapContextMenu.popup();
                               else mapContextMenu.dismiss();
                           }
                onWheel: (wheel) => {
                             if(wheel.modifiers & Qt.ControlModifier) {
                                 mapFrame.height *= wheel.angleDelta.y < 0 || wheel.angleDelta.x < 0 ? 0.9 : 1.1;
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
                hoverEnabled: mapFrame.drawing
                Repeater {
                    id: pathRepeater
                    anchors.fill: parent
                    model: map.paths
                    delegate: PathRepresentation {
                        path: modelData
                        isDrawMode: mapFrame.drawing
                        function clicked(x_offset, y_offset) {
                            if(!pathContextMenu.visible)
                                pathContextMenu.show(this, x_offset, y_offset);
                            else
                                pathContextMenu.dismiss();
                        }
                    }
                }

                Repeater {
                    id: pointRepeater
                    anchors.fill: parent
                    model: map.points
                    delegate: PointRepresentation {
                        point: modelData
                        isDrawMode: mapFrame.drawing
                        function clicked() {
                            if(isDrawMode)
                                mapFrame.finishDrawingPathAt(point);
                            else if(!pointContextMenu.visible)
                                pointContextMenu.show(this);
                            else
                                pointContextMenu.dismiss();
                        }
                    }
                }

                Repeater {
                    id: cityRepeater
                    anchors.fill: parent
                    model: map.cities
                    delegate: CityRepresentation {
                        city: modelData
                        isDrawMode: mapFrame.drawing
                        function clicked() {
                            if(isDrawMode)
                                mapFrame.finishDrawingPathAt(city);
                            else if(!cityContextMenu.visible)
                                cityContextMenu.show(this);
                            else
                                cityContextMenu.dismiss();
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

                Popup {
                    id: cityPopup
                    property var cityRepresentation_
                    property var pointRepresentation_
                    function editCity(cityRepresentation) {
                        cityRepresentation_ = cityRepresentation.city;
                        pointRepresentation_ = 0;
                        x = cityRepresentation.x;
                        y = cityRepresentation.y;
                        newCityName.text = cityRepresentation_.name;
                        open();
                    }

                    function addCity(x, y) {
                        cityRepresentation_ = 0;
                        pointRepresentation_ = 0;
                        this.x = x;
                        this.y = y;
                        newCityName.text = "";
                        open();
                    }

                    function promotePointToCity(pointRepresentation) {
                        cityRepresentation_ = 0;
                        pointRepresentation_ = pointRepresentation;
                        x = pointRepresentation_.x;
                        y = pointRepresentation_.y;
                        newCityName.text = "";
                        open();
                    }

                    contentItem: GridLayout {
                        columns: 2
                        Label {
                            text: qsTr("Nazwa miasta: ")
                            Layout.preferredHeight: 60
                        }
                        TextInput {
                            onVisibleChanged: if(visible) forceActiveFocus();
                            verticalAlignment: Text.AlignVCenter
                            id: newCityName
                            Keys.onReturnPressed: parent.activate();
                            Keys.onEnterPressed: parent.activate();
                            Layout.minimumWidth: 200
                            Layout.preferredHeight: 60
                        }
                        StyledButton {
                            Layout.columnSpan: 2
                            Layout.alignment: Qt.AlignHCenter
                            Layout.preferredHeight: 50
                            Layout.preferredWidth: 100
                            text: "Zapisz"
                            function activate() { parent.activate() }
                        }
                        function activate() {
                            if(newCityName.text == "") {
                                windowDialog.showError("Nazwa miasta nie może być pusta!");
                                return;
                            }
                            if(cityPopup.cityRepresentation_) {
                                cityPopup.cityRepresentation_.name = newCityName.text;
                            } else if(cityPopup.pointRepresentation_) {
                                map.promotePointToCity(cityPopup.pointRepresentation_.point, newCityName.text);
                            } else {
                                map.addCity(newCityName.text, cityPopup.x/draggableArea.width, cityPopup.y/draggableArea.height);
                            }
                            newCityName.text = "";
                            cityPopup.close();
                        }
                    }
                }

                Menu {
                    id: mapContextMenu
                    MenuItem {
                        text: "Dodaj miasto"
                        onTriggered: cityPopup.addCity(mapContextMenu.x, mapContextMenu.y)
                    }
                    MenuItem {
                        text: "Dodaj punkt"
                        onTriggered: map.addPoint(mapContextMenu.x/draggableArea.width, mapContextMenu.y/draggableArea.height)
                    }
                }
            }
        }
    }

    Connections {
        target: map
        function onPathAlreadyExist() {
            mapErrorPopup.showError("Taka ścieżka już istnieje!");
        }

        function onPathEndOnBegining() {
            mapErrorPopup.showError("Ścieżka nie może zaczynać się i kończyć w tym samym miejscu!");
        }
    }

    Popup {
        id: mapErrorPopup
        anchors.centerIn: parent
        function showError(errorString) {
            errorText.text = errorString;
            open();
        }

        contentItem: Text {
                id: errorText
                text: qsTr("Nazwa miasta: ")
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
