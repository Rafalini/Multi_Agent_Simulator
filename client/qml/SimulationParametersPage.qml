import QtQuick 2.0
import QtQuick.Controls 2.15

Page {
    id: simulationParametersPage

    Connections {
        target: remoteConnector
//        function onOnDisconnected() {
//            submitButton.enabled = true;
//        }
        function onAnswerParsed() {
            submitButton.enabled = true;
        }
    }

    StyledButton {
        id: submitButton
        text: "Wyślij"
        anchors.centerIn: parent
        function activate() {
            remoteConnector.submit();
            enabled = false;
        }
    }

    property int radius: 100


    Repeater {
        visible: !submitButton.enabled
        id: loadingCircle
        model: 6
        Rectangle {
            visible: !submitButton.enabled
            width: 2*radius
            height: width
            color: "black"
            radius: 10
            property real angle: 0
            x: parent.width/2 + simulationParametersPage.radius * Math.sin((angle + 2*Math.PI*index/loadingCircle.count)%(2*Math.PI)) - width/2
            y: parent.height/2 + simulationParametersPage.radius * Math.cos((angle + 2*Math.PI*index/loadingCircle.count)%(2*Math.PI))
            PropertyAnimation on angle {
                running: !submitButton.enabled
                loops: Animation.Infinite
                duration: 1000
                from: 2*Math.PI
                to: 0
            }
        }
    }
}
