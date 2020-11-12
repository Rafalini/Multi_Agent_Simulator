import QtQuick 2.15

Rectangle {

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
    }
}
