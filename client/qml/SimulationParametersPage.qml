import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: simulationParametersPage

    Connections {
        target: remoteConnector
        function onAnswerParsed() {
            submitButton.enabled = true;
        }
    }

    GridLayout {
        anchors.centerIn: parent
        anchors.topMargin: 20
        columns: 2

        Label {
            text: "Maksymalna prędkość na drodze zwykłej:"
        }
        TextField {
            validator: DoubleValidator {
                    locale: "en_US"
                    bottom: 0
                }
//            Keys.onEnterPressed: parent.save()
//            Keys.onReturnPressed: parent.save()
        }


        Label {
            text: "Maksymalna prędkość na drodze przyspieszonej:"
        }
        TextField {
            validator: DoubleValidator {
                    locale: "en_US"
                    bottom: 0
                }
//            Keys.onEnterPressed: parent.save()
//            Keys.onReturnPressed: parent.save()
        }


        Label {
            text: "Maksymalna prędkość na autostradzie:"
        }
        TextField {
            validator: DoubleValidator {
                    locale: "en_US"
                    bottom: 0
                }
//            Keys.onEnterPressed: parent.save()
//            Keys.onReturnPressed: parent.save()
        }


        StyledButton {
            id: submitButton
            Layout.rowSpan: 2
            text: "Wyślij"
            Layout.alignment: Qt.AlignCenter
//            anchors.centerIn: parent
            function activate() {
                tabBar.visible = false;
                remoteConnector.submit();
                enabled = false;
            }
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
            y: parent.height/2 + simulationParametersPage.radius * Math.cos((angle + 2*Math.PI*index/loadingCircle.count)%(2*Math.PI)) - height/2
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
