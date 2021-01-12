import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    ColumnLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        Text{
           text: "Witaj w Symulatorze Wieloagentowym"
           font.pixelSize: 30
        }

        StyledButton {
            text: "Wczytaj mapę z pliku"
            Layout.alignment: Qt.AlignHCenter
            function activate() {
                map.readMapFromJsonFile();
            }
        }

        StyledButton {
            text: "Zapisz mapę do pliku"
            Layout.alignment: Qt.AlignHCenter
            function activate() {
                map.saveMapToJson();
            }
        }

        StyledButton {
            text: "Wczytaj agentów z pliku"
            Layout.alignment: Qt.AlignHCenter
            function activate() {
                agents.readFromJsonFile();
            }
        }

        StyledButton {
            text: "Zapisz agentów do pliku"
            Layout.alignment: Qt.AlignHCenter
            function activate() {
                agents.saveToJson();
            }
        }
    }
}
