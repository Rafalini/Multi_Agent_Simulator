import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Popup {
    id: agentPopup
    anchors.centerIn: parent
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

            if(totalWeight.text === "") {
                windowDialog.showError("Nie podany wagi towaru");
                return false;
            }
            return true;
        }


        Connections {
            target: map
            function onCityAdded(city) {
                citiesModel.append({
                                    text: city.name,
                                    city: city
                                   });
            }
        }

        ListModel {
            id: citiesModel
            Component.onCompleted: {
                let cities = map.cities;
                for(let i = 0; i < cities.length; i++) {
                    citiesModel.append({
                                        text: cities[i].name,
                                        city: cities[i]
                                       });
                }
            }
        }

        Text {
            text: qsTr("Miasto początkowe")
        }

        ComboBox {
            id: begining
            displayText: model.get(currentIndex) ? model.get(currentIndex).text : qsTr("Wybierz miasto")
            textRole: "text"
            Layout.fillWidth: true
            model: citiesModel
        }


        Text {
            text: qsTr("Miasto docelowe")
        }

        ComboBox {
            displayText: model.get(currentIndex) ? model.get(currentIndex).text : qsTr("Wybierz miasto")
            Layout.fillWidth: true
            id: end
            model: citiesModel
            textRole: "text"
        }

        Text {
            text: qsTr("Ilość towaru do przewiezienia [kg]")
        }

        TextField {
            id: totalWeight
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
                agents.addAgent(citiesModel.get(begining.currentIndex).city, citiesModel.get(end.currentIndex).city, totalWeight.text.replace(',', ''));
            } else {
                editedAgent.update(citiesModel.get(begining.currentIndex).city, citiesModel.get(end.currentIndex).city, totalWeight.text.replace(',', ''));
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
