import QtQuick 2.0
import QtQuick.Controls 2.15

Page {

    StyledButton {
        text: "Wyślij"
        anchors.topMargin: 30
        function activate() {
            remoteConnector.submit();
        }
    }
}
