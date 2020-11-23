import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: listViewParent
    function editAgent(agent) {} //must be overwriten with acces to AgentsPage

    Label {
        id: headLabel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 10
        text: "Agenci:"
    }

    Row {
        id: listViewLabel
        anchors.left: headLabel.left
        anchors.top: headLabel.bottom
        height: 30
        Label {
            height: 20
            width: 200
            text: "Miasto początkowe"
        }
        Label {
            height: 20
            width: 200
            text: "Miasto końcowe"
        }
        Label {
            height: 20
            width: 200
            text: "Waga towaru do przewiezienia"
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
        cacheBuffer: 200
        width: 600
        height: 600//parent.height - listViewLabel.height - listViewLabel.topMargin - anchors.topMargin
        anchors.top: listViewLabel.bottom
        anchors.left: listViewLabel.left
        anchors.topMargin: 10
        anchors.leftMargin: 10
        interactive: true
        spacing: 10
        ScrollBar.vertical: agentsScrollBar
        delegate: ItemDelegate {
            height: 20
            width: 600
            background: Rectangle {
                anchors.fill: parent
                color: root.lightblue
            }

            Component.onCompleted: {
                beginingLabel.text = agentModel.get(index).agent.begining.name;
                destinationLabel.text = agentModel.get(index).agent.destination.name;
                weightLabel.text = agentModel.get(index).agent.weight;
            }

            Connections {
                target: agentModel.get(index).agent
                function onEdited() {
                    beginingLabel.text = agentModel.get(index).agent.begining.name;
                    destinationLabel.text = agentModel.get(index).agent.destination.name;
                    weightLabel.text = agentModel.get(index).agent.weight;
                }
                function onDeleted() {
                    target = null;
                    agentModel.remove(index);
                }
            }
            Connections {
                target: agentModel.get(index).agent.begining
                function onNameChanged(newName) {
                    beginingLabel.text = newName;
                }
            }

            Connections {
                target: agentModel.get(index).agent.destination
                function onNameChanged(newName) {
                    destinationLabel.text = newName;
                }
            }

            Row {
                width: parent.width
                height: 30
                Label {
                    id: beginingLabel
                    height: 20
                    width: 200
                }
                Label {
                    id: destinationLabel
                    height: 20
                    width: 200
                }
                Label {
                    id: weightLabel
                    height: 20
                    width: 100
                }
                StyledButton {
                    height: 20
                    width: 50
                    text: "E"
                    onClicked: {
                        listViewParent.editAgent(agentModel.get(index).agent);
                    }
                    onDoubleClicked: ;
                }
                StyledButton {
                    height: 20
                    width: 50
                    text: "X"
                    onClicked: {
                        agents.removeAgent(agentModel.get(index).agent);
                    }
                    onDoubleClicked: ;
                }
            }
        }

        model: ListModel {
            id: agentModel
        }
    }
    ScrollBar {
        id: agentsScrollBar
        active: true
        height: agentsListView.height
        policy: ScrollBar.AlwaysOn
        anchors.top: agentsListView.top
        anchors.left: agentsListView.right
    }
}
