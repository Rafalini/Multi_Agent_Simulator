import QtQuick 2.15


PointRepresentation {
    id: cityRepresentation
    property var city
    point: city
    color: "red"
    rec.radius: 5
    Text {
        id: cityName
        text: city ? city.name : ""
        anchors.left: rec.right
        anchors.verticalCenter: rec.verticalCenter
        anchors.leftMargin: 2
        font.pixelSize: 10
    }
}
