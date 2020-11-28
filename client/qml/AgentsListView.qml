import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: listViewParent
    function editAgent(agent) {} //must be overwriten with acces to AgentsPage
    height: listViewLabel.height + agentsListView.height
    width: agentsListView.width
    Label {
        id: headLabel
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 20
        anchors.leftMargin: 10
        text: "Agenci:"
    }

    RowLayout {
        id: listViewLabel
        anchors.left: headLabel.left
        anchors.top: headLabel.bottom
        height: 30
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
            id: weightHeaderLabel
            height: parent.height
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
        width: listViewLabel.width + 100//additional 100  width is for buttons
        readonly property int itemHeight: 30
        height: model.count * (spacing + itemHeight)
        anchors.top: listViewLabel.bottom
        anchors.topMargin: 10
        interactive: true
        spacing: 10
        ScrollBar.vertical: ScrollBar {
                id: agentsScrollBar
                active: true
                height: agentsListView.height
                policy: ScrollBar.AlwaysOn
                anchors.top: agentsListView.top
                anchors.left: agentsListView.right
            }
        delegate: ItemDelegate {
            height: agentsListView.itemHeight
            width: 600
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
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: beginingHeaderLabel.width
                    text: agent.begining.name
                }
                Label {
                    id: destinationLabel
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: destinationHeaderLabel.width
                    text: agent.destination.name
                }
                Label {
                    id: weightLabel
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: weightHeaderLabel.width
                    text: agent.weight
                }
                StyledButton {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: 50
                    text: "E"
                    function activate() {
                        listViewParent.editAgent(agent);
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
}
