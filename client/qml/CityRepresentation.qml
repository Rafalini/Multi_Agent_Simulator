import QtQuick 2.15


PointRepresentation {
    id: cityRepresentation
    required property var city
    z: 3
    point: city
    color: "red"

    function objectDeleted() {
        parent.deleteCity(this);
    }

    function clicked() {
        parent.openCityContextMenu(cityRepresentation);
    }

    Text{
        id: cityName
        text: city ? city.name : ""
        anchors.left: rec.right
        anchors.verticalCenter: rec.verticalCenter
        anchors.leftMargin: 2
        height: rec.height
    }
}
