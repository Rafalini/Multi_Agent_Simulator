import QtQuick 2.15


PointRepresentation {
    required property var city
    point: city
    Component.onCompleted: {
        cityName.text = city.name;
        initilize();
    }
    Text{
        id: cityName
        anchors.left: rec.right
        anchors.verticalCenter: rec.verticalCenter
        anchors.leftMargin: 2
        height: rec.height
    }
}
