import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    GridLayout {
        columns: 2
        Label {
            Layout.columnSpan: 2
            text: "Legenda:"
        }

        Label {
            text: "Droga zwykła"
        }
        Rectangle {
            Layout.preferredHeight: 4
            Layout.preferredWidth: 50
            color: "black"
        }
        Label {
            text: "Droga ekspresowa"
        }
        Rectangle {
            Layout.preferredHeight: 6
            Layout.preferredWidth: 50
            color: "darkblue"
        }
        Label {
            text: "Autostrada"
        }
        Rectangle {
            Layout.preferredHeight: 8
            Layout.preferredWidth: 50
            color: "purple"
        }
        Label {
            text: "Korek"
        }
        Rectangle {
            Layout.preferredHeight: 8
            Layout.preferredWidth: 50
            color: "red"
        }
    }
}
