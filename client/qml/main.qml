import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material 2.15

ApplicationWindow {
    visible: true
    id: root
    height: Screen.height/2
    width: Screen.width/2

    Material.theme: Material.Light
    Material.accent: Material.Orange

    ColumnLayout {
        height: parent.height
        width: parent.width
        spacing: 0
        TabBar {
            id: tabBar
            Layout.fillWidth: true
            Layout.maximumHeight: 150
            currentIndex: 0
            Repeater {
                model: ["Start", "Agenci", "Mapa", "Parametry Symulacji"]
                anchors.fill: parent
                TabButton {
                    id: button
                    text: modelData
                    height: tabBar.height
                    MouseArea {
                      anchors.fill: parent
                      cursorShape: Qt.PointingHandCursor
                      onPressed: parent.toggle()
                    }
                }
            }
        }

        StackLayout  {
            id: view
            clip: true
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 20
            Layout.minimumWidth: 20
            currentIndex: tabBar.currentIndex

            WelcomePage {
                id: welcomePage
            }

            AgentsPage {
                id: agentsPage
            }

            MapEditorPage {
                id: mapSelector
            }

            SimulationParametersPage {
                id: simulationParametersPage
            }
        }
    }
    Popup {
        id: windowDialog
        width: 200
        height: 200
        anchors.centerIn: parent
        contentItem: Text {
                id: popupText
                text: ""
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        }
        function showError(text) {
            popupText.text = text;
            open();
        }
    }
}
