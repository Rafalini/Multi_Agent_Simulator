import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: parentItem
    property var cities
    property var points
    property var cityComponent
    property var pointComponent

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
            cityArray.push(newCityRepresentation);
        }
        pointComponent = Qt.createComponent("PointRepresentation.qml");
        cities = cityArray;
        let pointArray = [];
        let currentPoints = map.points;
        for(let j = 0; j < currentPoints.length; ++j) {
            let point = currentPoints[j];
            let newPointRepresentation = pointComponent.createObject(draggableArea, {point: point});
            pointArray.push(newPointRepresentation);
        }
        points = pointArray;
    }

    Image {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width
        source: "../resource/MapOfPoland.png"
    }
    Canvas {
        id:canvas
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width

        //property color strokeStyle:  Qt.darker(fillStyle, 1.4)
        //        property bool fill: true
        //        property bool stroke: true
        //        property real alpha: 1.0
        //        antialiasing: true

        MouseArea {
            id: draggableArea
            anchors.fill: parent
            acceptedButtons: Qt.RightButton | Qt.LeftButton
            onClicked: (mouse) => {
                           contextMenu.x = mouse.x;
                           contextMenu.y = mouse.y;
                           contextMenu.open();
                       }
        }

        Menu {
            id: contextMenu
            Menu {
                title: "Dodaj miasto"
                MenuItem {
                    onTriggered: activate();
                    TextInput {
                        anchors.leftMargin: 2
                        onVisibleChanged: if(visible) forceActiveFocus();
                        width: parent.width-80
                        height: parent.height
                        id: newCityName
                    }
                    StyledButton {
                        anchors.left: newCityName.right
                        height: newCityName.height
                        width: 80
                        text: "Dodaj"
                        onClicked: parent.activate()
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

        onPaint: {
            //            var ctx = canvas.getContext('2d');
            //            var originX = 85
            //            var originY = 75
            //            ctx.save();
            //            ctx.clearRect(0, 0, canvas.width, canvas.height);
            //            ctx.translate(originX, originX);
            //            ctx.globalAlpha = canvas.alpha;
            //            ctx.strokeStyle = canvas.strokeStyle;
            //            ctx.fillStyle = canvas.fillStyle;
            //            ctx.lineWidth = canvas.lineWidth;
            //            ctx.translate(originX, originY)
            //            ctx.scale(canvas.scale, canvas.scale);
            //            ctx.translate(-originX, -originY)
            //! [0]
            //            ctx.beginPath();
            //            ctx.moveTo(75,40);
            //            ctx.bezierCurveTo(75,37,70,25,50,25);
            //            ctx.bezierCurveTo(20,25,20,62.5,20,62.5);
            //            ctx.bezierCurveTo(20,80,40,102,75,120);
            //            ctx.bezierCurveTo(110,102,130,80,130,62.5);
            //            ctx.bezierCurveTo(130,62.5,130,25,100,25);
            //            ctx.bezierCurveTo(85,25,75,37,75,40);
            //            ctx.closePath();
            //! [0]
            //            if (canvas.fill)
            //                ctx.fill();
            //            if (canvas.stroke)
            //                ctx.stroke();
            //            ctx.restore();
        }

    }
}
