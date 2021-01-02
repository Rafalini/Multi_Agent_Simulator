import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: agentPopup
    anchors.centerIn: parent

    function addNewAgent() {
        begining.currentIndex = -1;
        end.currentIndex = -1;
        load.text = "";
        editedAgent = 0;
        this.visible = true;
    }

    function editAgent(agent) {
        editedAgent = agent;
        load.text = agent.load.toString();
        begining.currentIndex = -1;
        end.currentIndex = -1;
        for(var i = 0; i < begining.model.length; i++) {
            if(agent.begining === begining.model[i]) {
                begining.currentIndex = i;
            }
            if(agent.destination === end.model[i]) {
                end.currentIndex = i;
            }
        }
        this.visible = true;
    }

    property var editedAgent: 0;
    contentItem: GridLayout {
        id: column
        columns: 2

        function validate() {
            if(begining.currentIndex < 0) {
                windowDialog.showError("Nie wybrano miasta początkowego");
                return false;
            }

            if(end.currentIndex < 0) {
                windowDialog.showError("Nie wybrano miasta końcowego");
                return false;
            }

            if(end.currentIndex == begining.currentIndex) {
                windowDialog.showError("Miasto początkowe musi być różne od miasta końcowego");
                return false;
            }

            if(load.text === "") {
                windowDialog.showError("Nie podano ładunku");
                return false;
            }
            return true;
        }

        Text {
            text: qsTr("Miasto początkowe")
        }

        ComboBox {
            id: begining
            displayText: currentIndex > -1 ? model[currentIndex].name : qsTr("Wybierz miasto")
            Layout.fillWidth: true
            model: map ? map.cities : 0
            delegate: ItemDelegate {
                text: modelData.name
                width: begining.width
            }
        }


        Text {
            text: qsTr("Miasto docelowe")
        }

        ComboBox {
            displayText: currentIndex > -1 ? model[currentIndex].name : qsTr("Wybierz miasto")
            Layout.fillWidth: true
            id: end
            model: map ? map.cities : 0
            delegate: ItemDelegate {
                text: modelData.name
                width: end.width
            }
        }

        Text {
            text: qsTr("Ładunek [kg]")
        }

        TextField {
            id: load
            Layout.preferredWidth: 300
            validator: DoubleValidator {
                    locale: "en_US"
                    bottom: 0
                }
            Keys.onEnterPressed: parent.save()
            Keys.onReturnPressed: parent.save()
        }

        function save() {
            if( !validate() ) return;
            if( editedAgent === 0 ) {
                agents.addAgent(begining.model[begining.currentIndex], end.model[end.currentIndex], load.text.replace(',', ''));
            } else {
                editedAgent.update(begining.model[begining.currentIndex], end.model[end.currentIndex], load.text.replace(',', ''));
            }
            agentPopup.visible = false;
        }

        StyledButton {
            Layout.columnSpan: 2
            Layout.alignment: Qt.AlignCenter
            text: editedAgent !== 0 ? "Zapisz" : "Dodaj"
            function activate() { parent.save(); }
        }
    }
}
