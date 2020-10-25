import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    width: 200
    height: 200
    x: root.width/2 - width/2
    y: root.height/2 - height/2
    id: popup
    closePolicy: Popup.CloseOnEscape
    contentItem: Text {
            id: popupText

            text: ""
            anchors.fill: parent
    }
    Connections {
        target: remoteConnector
        function onAnswerReceived(text) {
            popupText.text = "<html>" + text + "<br><br>Nacisnij escape aby włączyć popup</html>";
            popup.open();
        }
    }
}

