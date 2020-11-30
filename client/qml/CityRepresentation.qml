import QtQuick 2.15


PointRepresentation {
    id: cityRepresentation
    required property var city
    point: city
    color: "red"
    Component.onCompleted: {
        cityName.text = city.name;
        initilize();
    }

    Connections {
        target: city
        function onDeleted() {
            parent.deleteCity(pointRepresentation);
        }
    }

    function clicked() {
        parent.openCityContextMenu(cityRepresentation);
    }
    Text{
        id: cityName
        anchors.left: rec.right
        anchors.verticalCenter: rec.verticalCenter
        anchors.leftMargin: 2
        height: rec.height
    }
}
