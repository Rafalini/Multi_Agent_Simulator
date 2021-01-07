import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

Page {
    id: parentItem
    title: "Edytuj mapę"

    Connections {
        target: remoteConnector
        function onAnswerReceived() {
            tabBar.currentIndex = 2;
            draggableArea.enabled = false;
        }
        function onAnswerParsed() {
            agentRepeater.visible = true;
        }
    }

    Rectangle {
        id: mapFrame
        anchors.centerIn: parent
        width: height
        height: 500
        scale: Math.min(parentItem.width/width, parentItem.height/height)
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
            visible: x !== -1 && y && -1 && x2 !== -1 && y2 !== -1
            x: mapFrame.startPoint ? mapFrame.drawing ? mapFrame.startPoint.x*mapFrame.width : -1 : -1
            y: mapFrame.startPoint ? mapFrame.drawing ? mapFrame.startPoint.y*mapFrame.height : -1 : -1
            x2: mapFrame.startPoint ? draggableArea.mouseX : x
            y2: mapFrame.startPoint ? draggableArea.mouseY : y
        }

        MouseArea {
            id: draggableArea
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            onClicked: mapContextMenu.visible ? mapContextMenu.dismiss() : mapContextMenu.popup()
            hoverEnabled: mapFrame.drawing
            Repeater {
                id: pathRepeater
                anchors.fill: parent
                model: map ? map.paths : 0
                delegate: PathRepresentation {
                    path: modelData
                    isInAnimationMode: !draggableArea.enabled
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
                model: map ? map.points : 0
                delegate: PointRepresentation {
                    point: modelData
                    isInAnimationMode: !draggableArea.enabled
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
                model: map ? map.cities : 0
                delegate: CityRepresentation {
                    city: modelData
                    isDrawMode: mapFrame.drawing
                    isInAnimationMode: !draggableArea.enabled
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

            Repeater {
                id: agentRepeater
                visible: false
                anchors.fill: parent
                model: agents
                property int finishedAnimations: 0;
                onFinishedAnimationsChanged: {
                    if(finishedAnimations === agents.rowCount()) {
                        tabBar.visible = true;
                        draggableArea.enabled = true;
                        visible = false;
                        finishedAnimations = 0;
                    }
                }
                delegate: AgentRepresentation {
                    agent_: agent
                    isAnimationRunning: !draggableArea.enabled
                    function animationFinished() {
                        agentRepeater.finishedAnimations++;
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
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextInput {
                        onVisibleChanged: if(visible) forceActiveFocus();
                        verticalAlignment: Text.AlignVCenter
                        id: newCityName
                        Keys.onReturnPressed: parent.activate();
                        Keys.onEnterPressed: parent.activate();
                        Layout.minimumWidth: 200
                        Layout.preferredHeight: 60
                        selectByMouse: true
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

    Popup {
        id: pathTypeEditPopup
        anchors.centerIn: parent
        property var path: 0
        function show(path) {
            this.path = path;
            pathTypeEditPopupComboBox.currentIndex = path.type;
            open();
        }
        contentItem: Column {
            ComboBox {
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                id: pathTypeEditPopupComboBox
                model: ['Krajowa', 'Droga ekspresowa', 'Autostrada']
            }
            StyledButton {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Zapisz"
                function activate() {
                    if(pathTypeEditPopupComboBox.currentIndex !== -1) {
                        pathTypeEditPopup.path.type = pathTypeEditPopupComboBox.currentIndex;
                    }
                    pathTypeEditPopup.close();
                }
            }
        }
    }
}
