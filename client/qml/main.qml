import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Window {
    visible: true
    id: root

    readonly property string lightblue: "#6495ed"

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor

    }

    Rectangle {
        id: header
        width: parent.width
        height: 80
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        color: root.lightblue

        Row {
            anchors.leftMargin: 10
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            spacing: 10
            height: parent.height
            Text {
                id: headerText
                text: qsTr("Symulator Wieloagentowy")
                height: parent.height - 20
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                elide: Text.ElideMiddle
                width: 300
                color: "black"
                fontSizeMode: Text.Fit
                font.pixelSize: 70
            }

            StyledButton {
                text: qsTr("Agenci")
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    agentsPage.visible = true;
                    welcomeScreen.visible = false;
                    mapSelector.visible = false;
                }
            }


            StyledButton {
                text: qsTr("Mapa")
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    agentsPage.visible = false;
                    welcomeScreen.visible = false;
                    mapSelector.visible = true;
                }
            }
            StyledButton {
                text: qsTr("Wyślij mapę") //for now it just sends whatever was set in main.cpp to show how it works
                anchors.verticalCenter: parent.verticalCenter
                onClicked: {
                    remoteConnector.submit();
                }
            }
        }
    }

    Item {
        anchors.top: header.bottom
        anchors.left: parent.left
        width: parent.width
        height: parent.height - header.height

        WelcomeScreen {
            id: welcomeScreen
            anchors.fill: parent
            visible: true

        }

        AgentsPage {
            id: agentsPage
            anchors.fill: parent
            visible: false
        }

        MapEditor {
            id: mapSelector
            anchors.fill: parent
            visible: false
        }
    }

    StyledPopup {
        id: windowDialog
    }
}
