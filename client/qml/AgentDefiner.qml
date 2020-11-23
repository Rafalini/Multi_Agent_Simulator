import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: agentPopup
    anchors.centerIn: parent
    width: 300
    height: 500
    background: Rectangle {
        anchors.fill: parent
        color: "white"
        border.color: "black"
        border.width: 2
    }

    function addNewAgent() {
        begining.currentIndex = -1;
        end.currentIndex = -1;
        totalWeight.text = "";
        editedAgent = 0;
        this.visible = true;
    }

    function editAgent(agent) {
        editedAgent = agent;
        totalWeight.text = agent.weight.toString();
        begining.currentIndex = -1;
        end.currentIndex = -1;
        for(var i = 0; i < citiesModel.count; i++) {
            if(agent.begining === citiesModel.get(i).city) {
                begining.currentIndex = i;
            }
            if(agent.destination === citiesModel.get(i).city) {
                end.currentIndex = i;
            }
        }
        if(end.currentIndex == -1) {
            citiesModel.append({
                            city = agent.destination
                           });
            end.currentIndex = citiesModel.count-1;
        }

        if(begining.currentIndex == -1) {
            citiesModel.append({
                            city = agent.begining
                           });
            begining.currentIndex = citiesModel.count-1;
        }
        this.visible = true;
    }


    property var editedAgent: 0;
    contentItem: Column {
        id: column
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 10

        function validate() {
            if(begining.currentIndex < 0) {
                windowDialog.showError("Nie wybrano miasta początkowego");
                return false;
            }

            if(end.currentIndex < 0) {
                windowDialog.showError("Nie wybrano miasta końcowego");
                return false;
            }

            if(totalWeight.text === "") {
                windowDialog.showError("Nie podany wagi towaru");
                return false;
            }
            return true;
        }

        ListModel {
            id: citiesModel
            Component.onCompleted: {
                let cities = map.getCities();
                for(let i = 0; i < cities.length; i++) {
                    citiesModel.append({
                                        text: cities[i].name,
                                        city: cities[i]
                                       });
                }
            }
        }

        Text {
            text: qsTr("Wybierz miasto Początkowe")
        }

        ComboBox {
            id: begining
            width: 200
            displayText: model.get(currentIndex) ? model.get(currentIndex).text : qsTr("Wybierz miasto")
            textRole: "text"
            model: citiesModel
        }


        Text {
            text: qsTr("Wybierz miasto docelowe")
        }

        ComboBox {
            displayText: model.get(currentIndex) ? model.get(currentIndex).text : qsTr("Wybierz miasto")
            id: end
            width: 200
            model: citiesModel
            textRole: "text"
        }

        Text {
            text: qsTr("Podaj ilość towaru do przewiezienia w kilogramach")
        }

        TextField {
            id: totalWeight
            validator: DoubleValidator {bottom: 0; top: 100000}
        }

        StyledButton {
            text: editedAgent !== 0 ? "Zapisz" : "Dodaj"
            onClicked: {
                if( !parent.validate() ) return;
                if( editedAgent === 0 ) {
                    agents.addAgent(citiesModel.get(begining.currentIndex).city, citiesModel.get(end.currentIndex).city, totalWeight.text.replace(',', '.'));
                } else {
                    editedAgent.update(citiesModel.get(begining.currentIndex).city, citiesModel.get(end.currentIndex).city, totalWeight.text.replace(',', '.'));
                }
                agentPopup.visible = false;
            }
            onDoubleClicked: ;
        }
    }
}
