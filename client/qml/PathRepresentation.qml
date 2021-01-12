import QtQuick 2.15
import MultiAgentSimulator 1.0

SimplePathRepresentation {
    id: pathRepresentation
    property variant path
    property bool isDrawMode: false
    property bool isInAnimationMode: false
    property bool isTraffic: false
    x2: path && path.end ? path.end.x*parent.width : 0
    y2: path && path.end ? path.end.y*parent.height : 0
    x: path && path.begining ? path.begining.x*parent.width : 0
    y: path && path.begining ? path.begining.y*parent.height : 0

    Connections {
        target: path
        function onTrafficDataChanged() {
            let startTimer = Qt.createQmlObject('import QtQuick 2.15; Timer{ running: true; interval: ' + path.trafficData["begin_time"] * mapFrame.speed + '; onTriggered: { parent.isTraffic = true; destroy();} }', pathRepresentation);
            let endTimer = Qt.createQmlObject('import QtQuick 2.15; Timer{ running: true; interval: ' + path.trafficData["end_time"] * mapFrame.speed +'; onTriggered: { parent.isTraffic = false; destroy();} }', pathRepresentation);

        }
    }

    //change height and color according to road TYPE
    height: {
        if(!path) return 0;
        switch(path.type) {
        case RoadType.HIGHWAY:
            return 4;
        case RoadType.DUALCARRIAGEWAY:
            return 3;
        default:
            return 2;
        }
    }

    color: {
        if(!path) return 0;
        if(isTraffic) return "red";
        switch(path.type) {
        case RoadType.HIGHWAY:
            return "purple";
        case RoadType.DUALCARRIAGEWAY:
            return "darkblue";
        default:
            return "black";
        }
    }

    //signal for Repeater to open ContextMenu
    function clicked(x_offset, y_offset) {}
    MouseArea {
        enabled: !isDrawMode && !isInAnimationMode
        anchors.fill: parent
        acceptedButtons: Qt.RightButton | Qt.LeftButton
        cursorShape: enabled ? Qt.PointingHandCursor : Qt.ArrowCursor
        onClicked: (mouse) => {
                       let theta = pathRepresentation.rotation.angle * Math.PI / 180;
                       let x_offset = mouse.x * Math.cos(theta);
                       let y_offset = mouse.x * Math.sin(theta);
                       pathRepresentation.clicked(x_offset, y_offset);
                   }
    }
}
