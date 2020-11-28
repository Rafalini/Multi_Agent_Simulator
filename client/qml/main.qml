import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Window 2.15

Window {
    visible: true
    id: root

    readonly property string lightblue: "#6495ed"
    readonly property string darkblue: "#483d8b"

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.ArrowCursor
        ColumnLayout {
            height: parent.height
            width: parent.width
            spacing: 0
            TabBar {
                id: tabBar
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                Layout.maximumHeight: 40
                currentIndex: 0

                StyledTabButton {
                    text: qsTr("Symulator Wieloagentowy")
                }

                StyledTabButton {
                    text: qsTr("Agenci")
                }

                StyledTabButton {
                    text: qsTr("Mapa")
                }

                StyledTabButton {
                    text: qsTr("Parametry Symulacji")
                }
            }
            SwipeView {
                id: view
                clip: true
                interactive: false
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

        StyledPopup {
            id: windowDialog
        }
    }
}
