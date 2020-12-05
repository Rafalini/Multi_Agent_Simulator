import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.preferredHeight: parent.height
        Layout.fillHeight: true
        RowLayout {
            id: listViewLabel
            Layout.fillWidth: true
            Label {
                id: beginingHeaderLabel
                Layout.minimumWidth: 300
                Layout.alignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                text: "Miasto początkowe"
            }
            Label {
                id: destinationHeaderLabel
                Layout.minimumWidth: 300
                Layout.alignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                text: "Miasto końcowe"
            }
            Label {
                id: loadHeaderLabel
                Layout.minimumWidth: 300
                Layout.alignment: Qt.AlignVCenter
                horizontalAlignment: Qt.AlignHCenter
                text: "Ładunek"
            }
        }

        ListView {
            id: agentsListView
            model: agents
            Layout.maximumHeight: page.height - listViewLabel.height - newAgentButton.height
            interactive: true
            Layout.preferredHeight: contentHeight
            Layout.fillHeight: true
            spacing: 10
            ScrollBar.vertical: ScrollBar {
                id: agentsScrollBar
                active: true
                interactive: true
                height: agentsListView.height
                visible: agentsListView.height < agentsListView.contentHeight
                policy: ScrollBar.AlwaysOn
            }
            delegate: ItemDelegate {
                required property var begining
                required property var destination
                required property var load
                required property var agent
                width: row.width
                height: row.height
                RowLayout {
                    id: row
                    Label {
                        id: beginingLabel
                        Layout.alignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: beginingHeaderLabel.width
                        text: begining.name
                    }
                    Label {
                        id: destinationLabel
                        Layout.alignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: destinationHeaderLabel.width
                        text: destination.name
                    }
                    Label {
                        id: loadLabel
                        Layout.alignment: Qt.AlignVCenter
                        horizontalAlignment: Qt.AlignHCenter
                        Layout.preferredWidth: loadHeaderLabel.width
                        text: load
                    }
                    StyledButton {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50
                        text: "E"
                        function activate() {
                            agentDefiner.editAgent(agent);
                        }
                    }
                    StyledButton {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 50
                        text: "X"
                        function activate() {
                            agents.removeAgent(agent);
                        }
                    }
                }
            }
        }


        StyledButton {
            id: newAgentButton
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.preferredHeight: 50
            text: "Dodaj nowego Agenta"
            Layout.preferredWidth: 200
            function activate() {
                agentDefiner.addNewAgent();
            }
        }
    }

    AgentDefiner {
        id: agentDefiner
    }
}
