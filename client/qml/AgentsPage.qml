import QtQuick 2.15
import QtQuick.Controls 2.15

Item {

    AgentsListView {
        id: agentsList
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
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
        onClicked: {
            agentDefiner.addNewAgent();
        }
        onDoubleClicked: ;
    }

    AgentDefiner {
        id: agentDefiner
        visible: false
    }
}
