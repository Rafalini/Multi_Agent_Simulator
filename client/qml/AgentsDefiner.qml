import QtQuick 2.15
import QtQuick.Controls 2.15
Item {

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        spacing: 10

        ListModel {
            id: citiesModel
            Component.onCompleted: {
                let cities = ["Warszawa", "Kraków", "Poznań", "Wrocław", "Katowice", "Rzeszów", "Toruń", "Łódź", "Gdańsk", "Białystok", "Opole", "Zielona Góra", "Szczecin", "Suwałki"]
                for(let i = 0; i < cities.length; i++) {
                    citiesModel.append({
                                        text: cities[i]
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
        }
    }
}
