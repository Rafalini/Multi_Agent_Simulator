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
            agentsStatisticsListView.isGraphicalMode = true;
        }
        function onStatisticsParsed() {
            tabBar.currentIndex = 2;
            agentsStatisticsListView.isGraphicalMode = false;
            agentsStatisticsPopup.open();
        }
        function onAnswerParsed() {
            timeText.visible = true;
        }
    }


    MapLegend {}

    Rectangle {
        id: mapFrame
        anchors.centerIn: parent
        width: height
        height: 500
        scale: Math.min(parentItem.width/width, parentItem.height/height)
        property int speed: root.speed
        Image {
            anchors.fill: parent
            source: "../resource/MapOfPoland.png"
        }

        Text {
            id: timeText
            anchors.right: parent.right
            anchors.top: parent.top
            color: "black"
            visible: false //display only during animation
            property int minutes: 0
            property int hour: 22
            onVisibleChanged: {
                if(!visible) {
                    minutes = 0;
                    hour = 22;
                } else {
                    minutes = 0;
                    hour = 22;
                    minutesAnimation.restart();
                }
            }
            text: parseInt(hour) + ":" + (minutes < 10 ? "0" + minutes : minutes)
            PropertyAnimation on minutes {
                running: false
                id: minutesAnimation
                to: 60
                from: 0
                onFinished: {
                    timeText.minutes = 0;
                    timeText.hour += 1;
                    if(timeText.hour === 24)
                        timeText.hour = 0;
                    if(timeText.hour > 21 || timeText.hour < 6)
                        restart();
                    else {
                        timeText.visible = false;
                        draggableArea.enabled = true;
                        tabBar.visible = true;
                        agentsStatisticsPopup.open();
                    }
                }
                duration: mapFrame.speed * 60
            }

            NumberAnimation on x {
                id: xAnimation
            }
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
                anchors.fill: parent
                model: agents

                delegate: AgentRepresentation {
                    agent_: agent
                    isAnimationRunning: !draggableArea.enabled
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
        id: agentsStatisticsPopup
        anchors.centerIn: parent
        visible: false
        background: Rectangle {
            color: "white"
            border.width: 1
            border.color: "black"
        }

        contentItem: ColumnLayout {
            Layout.fillWidth: true
            RowLayout {
                id: listViewLabel
                Layout.fillWidth: true
                property var headers: agentsStatisticsListView.isGraphicalMode ? ["id", "Miasto początkowe","Miasto końcowe", "Dostarczono", "Przejechano", "Przepracowano"]
                                                                               : ["id", "Miasto początkowe","Miasto końcowe", "Średnio dostarczono", "Średnio przejechano", "Średnio przepracowano"]
                Repeater {
                    model: agentsStatisticsListView.columnWidths.length
                    Label {
                        Layout.preferredWidth: agentsStatisticsListView.columnWidths[index]
                        Layout.alignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        text: parent.headers[index]
                        font.bold: true
                    }
                }
            }

            ListView {
                model: agents
                id: agentsStatisticsListView

                property var columnWidths: agentsStatisticsListView.isGraphicalMode ? [30, 150, 150, 70, 100, 100] : [30, 150, 150, 150, 150, 150]

                Layout.preferredHeight: contentHeight
                Layout.preferredWidth: columnWidths.reduce(function(a, b){
                    return a + b;
                }, 0);

                property bool isGraphicalMode: true

                delegate: ItemDelegate {
                    required property var begining
                    required property var destination
                    required property var agent
                    width: row.width

                    height: row.height
                    id: delegate
                    property var repeaterValues: agentsStatisticsListView.isGraphicalMode ? [agent.id, begining.name, destination.name, agent.statistics["delivered"] ? Math.round(agent.statistics["delivered"]/agent.load*100)+"%" : "brak danych", agent.statistics["distance"] ? agent.statistics["distance"] : "brak danych", agent.statistics["working_time"] ? Math.round(parseFloat(agent.statistics["working_time"])/60) + "h" + Math.round(parseFloat(agent.statistics["working_time"])%60) + "min" : "brak danych"]
                                                                                          : [agent.id, begining.name, destination.name, agent.statistics["avg_delivered"] ?  Math.round(agent.statistics["avg_delivered"]/agent.load*100)+"%" : "brak danych", agent.statistics["avg_distance"] ? agent.statistics["avg_distance"] : "brak danych", agent.statistics["avg_working_time"] ? Math.round(parseFloat(agent.statistics["avg_working_time"])/60) + "h" + Math.round(parseFloat(agent.statistics["avg_working_time"])%60) + "min" : "brak danych"]

                    RowLayout {
                        id: row
                        Repeater {
                            model: delegate.repeaterValues.length
                            Label {
                                Layout.alignment: Qt.AlignVCenter
                                horizontalAlignment: Qt.AlignHCenter
                                Layout.preferredWidth: agentsStatisticsListView.columnWidths[index]
                                text: delegate.repeaterValues[index]
                            }
                        }
                    }
                }
            }
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
