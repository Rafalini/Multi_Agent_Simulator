import QtQuick 2.0
import QtQuick.Controls 2.15

Page {

    StyledButton {
        text: "Wyślij"
        anchors.centerIn: parent
        function activate() {
            remoteConnector.submit();
        }
    }
}
