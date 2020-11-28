import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    AgentsListView {
        id: agentsList
        anchors.horizontalCenter: parent.horizontalCenter
        height: parent.height - newAgentButton.height

        function editAgent(agent) {
            agentDefiner.editAgent(agent);
        }
    }

    StyledButton {
        id: newAgentButton
        anchors.bottom: agentsList.bottom
        anchors.left: agentsList.right
        height: 50
        text: "Dodaj nowego Agenta"
        width: 200
        function activate() {
            agentDefiner.addNewAgent();
        }
        onDoubleClicked: ;
    }

    AgentDefiner {
        id: agentDefiner
        visible: false
    }
}
