import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true
        RowLayout {
            id: listViewLabel
            Layout.preferredHeight: 30
            Label {
                id: beginingHeaderLabel
                height: parent.height
                width: 200
                text: "Miasto początkowe"
            }
            Label {
                id: destinationHeaderLabel
                height: parent.height
                width: 200
                text: "Miasto końcowe"
            }
            Label {
                id: loadHeaderLabel
                height: parent.height
                width: 200
                text: "Ładunek"
            }
        }

        Connections {
            target: agents
            function onAgentAdded(new_agent) {
                agentModel.append({
                                      agent: new_agent
                                  });
                agentsListView.positionViewAtEnd();
            }
        }

        ListView {
            id: agentsListView
            Layout.preferredWidth: listViewLabel.width + agentsScrollBar.width + 100//additional 100  width is for buttons
            readonly property int itemHeight: 30
            readonly property bool scrollNeeded: height < model.count * (spacing + itemHeight)
            Layout.preferredHeight: model.count * (spacing + itemHeight)
            Layout.maximumHeight: page.height - listViewLabel.height - newAgentButton.height
            interactive: true
            clip: true
            spacing: 10
            ScrollBar.vertical: ScrollBar {
                    id: agentsScrollBar
                    active: true
                    interactive: true
                    height: agentsListView.height
                    visible: agentsListView.scrollNeeded
                    policy: ScrollBar.AlwaysOn
                }
            delegate: ItemDelegate {
                height: agentsListView.itemHeight
                width: agentsListView.width
                background: Rectangle {
                    anchors.fill: parent
                    color: root.lightblue
                }

                Connections {
                    target: agent
                    function onDeleted() {
                        target = null;
                        agentModel.remove(index);
                    }
                }
                RowLayout {
                    width: parent.width
                    height: parent.height
                    Label {
                        id: beginingLabel
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: beginingHeaderLabel.width
                        text: agent.begining.name
                    }
                    Label {
                        id: destinationLabel
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: destinationHeaderLabel.width
                        text: agent.destination.name
                    }
                    Label {
                        id: loadLabel
                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: loadHeaderLabel.width
                        text: agent.load
                    }
                    StyledButton {
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: 50
                        text: "E"
                        function activate() {
                           agentDefiner.editAgent(agent);
                        }
                    }
                    StyledButton {
                        Layout.preferredHeight: parent.height
                        Layout.preferredWidth: 50
                        text: "X"
                        function activate() {
                            agents.removeAgent(agent);
                        }
                    }
                }
            }

            model: ListModel {
                id: agentModel
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
