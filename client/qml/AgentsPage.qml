import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: page
    property var labelWidth: [30, 150, 150, 70, 70]
    property var headers: ["id", "Miasto początkowe","Miasto końcowe", "Ładunek", "Ładowność"]

    MouseArea {
        anchors.fill: parent
        onWheel: (wheel) => {
            if(wheel.angleDelta.y < 0)
                agentsScrollBar.increase();
            else
                agentsScrollBar.decrease();
        }
    }

    ColumnLayout {
        id: columns
        anchors.horizontalCenter: parent.horizontalCenter
        Layout.preferredHeight: parent.height
        Layout.fillHeight: true
        RowLayout {
            id: listViewLabel
            Layout.fillWidth: true
            Repeater {
                model: page.headers.length
                Label {
                    Layout.preferredWidth: page.labelWidth[index]
                    Layout.alignment: Qt.AlignVCenter
                    horizontalAlignment: Qt.AlignHCenter
                    text: page.headers[index]
                    font.bold: true
                }
            }
        }

        ListView {
            id: agentsListView
            model: agents
            Layout.maximumHeight: page.height - listViewLabel.height - newAgentButton.height
            interactive: false
            Layout.preferredHeight: contentHeight
            Layout.fillHeight: false
            spacing: 10

            ScrollBar.vertical: agentsScrollBar
            delegate: ItemDelegate {
                required property var begining
                required property var destination
                required property var load
                required property var agent
                required property var capacity
                required property int index
                width: row.width
                height: row.height
                id: delegate
                property var repeaterValues: [agent.id, begining.name, destination.name, load, capacity]
                RowLayout {
                    id: row
                    Repeater {
                        model: page.headers.length
                        Label {
                            Layout.alignment: Qt.AlignVCenter
                            horizontalAlignment: Qt.AlignHCenter
                            Layout.preferredWidth: page.labelWidth[index]
                            text: delegate.repeaterValues[index]
                        }
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

    ScrollBar {
        id: agentsScrollBar
        active: true
        interactive: true
        height: agentsListView.height
        visible: agentsListView.height < agentsListView.contentHeight
        policy: ScrollBar.AlwaysOn
        wheelEnabled: true
        anchors.right: parent.right
        anchors.top: columns.top
        anchors.topMargin: listViewLabel.height
    }

    AgentDefiner {
        id: agentDefiner
    }
}
