import QtQuick 2.0
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: simulationParametersPage

    Connections {
        target: remoteConnector
        function onAnswerParsed() {
            submitButton.enabled = true;
        }
    }

    function validate() {
        //timeBetweenBreaks breakDuration
        var allFields = [standardRoadMaxSpeed, doubleCarriageWayRoadMaxSpeed, highwayMaxSpeed, accidentProbability, loadSpeed, unloadSpeed, timeBetweenBreaks, breakDuration];
        for(var field in allFields) {
            if(allFields[field].text === "") {
                windowDialog.showError("Wszystkie pola muszą być wypełnione");
                return false;
            }
        }
        if(!isGraphicalButton.checked) {
            if(numberOfSimulations.text === "") {
                windowDialog.showError("Wszystkie pola muszą być wypełnione");
                return false;
            }
            if(parseInt(numberOfSimulations.text)<1) {
                windowDialog.showError("Tryb statystyczny wymaga conajmniej jednego wykonania symulacji");
                return false;
            }
        }
        if(parseInt(standardRoadMaxSpeed.text)<1 || parseInt(doubleCarriageWayRoadMaxSpeed.text)<1 || parseInt(highwayMaxSpeed.text)<1 ) {
            windowDialog.showError("Maxymalna prędkość na każdej z dróg musi być większa od 0");
            return false;
        }
        if( parseFloat(accidentProbability.text)<0 ||  parseFloat(accidentProbability.text)>1) {
            windowDialog.showError("Prawdopodobieństwo wypadku musi znajdować się w przedziale (0, 1)");
            return false;
        }
        if( parseInt(loadSpeed.text)<1 ||  parseInt(unloadSpeed.text)<1) {
            windowDialog.showError("Tempo ładunku i rozładunku musi być większe od 0");
            return false;
        }

        if( parseInt(timeBetweenBreaks.text)<1 ||  parseInt(breakDuration.text)<1) {
            windowDialog.showError("Czas między przerwami oraz przerwa muszą być większe od 0");
            return false;
        }
        return true;
    }


    GridLayout {
        anchors.centerIn: parent
        anchors.topMargin: 20
        columns: 2
        Label {
            text: "Tryb graficzny:"
        }

        CheckBox {
            id: isGraphicalButton
            checked: true
            enabled: submitButton.enabled
        }

        Label {
            text: "Ilość powtórzeń symulacji\n(dla trybu statystycznego):"
        }

        TextField {
            id: numberOfSimulations
            enabled: !isGraphicalButton.checked && submitButton.enabled
            text: "1"
            selectByMouse: true
            validator: IntValidator {
                    bottom: 1
                }
        }

        Label {
            text: "Maksymalna prędkość na drodze zwykłej:"
        }
        TextField {
            id: standardRoadMaxSpeed
            text: "90"
            selectByMouse: true
            enabled: submitButton.enabled
            validator: IntValidator {
                    bottom: 1
                }
        }


        Label {
            text: "Maksymalna prędkość na drodze przyspieszonej:"
        }
        TextField {
            id: doubleCarriageWayRoadMaxSpeed
            text: "110"
            selectByMouse: true
            enabled: submitButton.enabled
            validator: IntValidator {
                    bottom: 1
            }
        }


        Label {
            text: "Maksymalna prędkość na autostradzie:"
        }
        TextField {
            id: highwayMaxSpeed
            text: "140"
            selectByMouse: true
            enabled: submitButton.enabled
            validator: IntValidator {
                    bottom: 1
                }
        }

        Label {
            text: "Prawdopodonieństwo wypadku agenta na odcinku 100km:"
        }
        TextField {
            id: accidentProbability
            enabled: submitButton.enabled
            text: "0.00001"
            selectByMouse: true
            validator: DoubleValidator {
                    bottom: 0
                    top: 1
                }
        }
        Label {
            text: "Średnia liczba minut potrzebna do załadowania 1kg ładunku do pojazdu"
        }
        TextField {
            id: loadSpeed
            enabled: submitButton.enabled
            text: "1"
            selectByMouse: true
            validator: IntValidator {
                    bottom: 1
                }
        }

        Label {
            text: "Średnia liczba minut potrzebna do rozładowania 1kg ładunku z pojazdu"
        }
        TextField {
            id: unloadSpeed
            enabled: submitButton.enabled
            text: "1"
            selectByMouse: true
            validator: IntValidator {
                    bottom: 1
                }
        }

        Label {
            text: "Ilość godzin po której konieczny jest odpoczynek"
        }
        TextField {
            id: timeBetweenBreaks
            enabled: submitButton.enabled
            text: "6"
            selectByMouse: true
            validator: IntValidator {
                    bottom: 1
                }
        }

        Label {
            text: "Czas obowiązkowej przerwy po przejechaniu " + timeBetweenBreaks.text === "" ? 0 : parseInt(timeBetweenBreaks.text) + " godzin (w minutach)"
        }
        TextField {
            id: breakDuration
            enabled: submitButton.enabled
            text: "30"
            selectByMouse: true
            validator: IntValidator {
                    bottom: 1
                }
        }


        StyledButton {
            id: submitButton
            Layout.rowSpan: 2
            text: "Wyślij"
            Layout.alignment: Qt.AlignCenter
            function activate() {
                if(!simulationParametersPage.validate()) return;
                let parameters = {
                    "isGraphical": isGraphicalButton.checked,
                    "max_speed_0": parseInt(standardRoadMaxSpeed.text),
                    "max_speed_1": parseInt(doubleCarriageWayRoadMaxSpeed.text),
                    "max_speed_2": parseInt(highwayMaxSpeed.text),
                    "accident": parseFloat(accidentProbability.text),
                    "load_speed": parseInt(loadSpeed.text),
                    "unload_speed": parseInt(unloadSpeed.text),
                    "time_between_breaks": 60*parseInt(timeBetweenBreaks.text),
                    "break_duration": parseInt(breakDuration.text)
                };
                if(!isGraphicalButton.checked) {
                    parameters["number_of_simulations"] = parseInt(numberOfSimulations.text);
                } else {
                    parameters["number_of_simulations"] = 1;
                }
                tabBar.visible = false;
                remoteConnector.submit(parameters);
                enabled = false;
            }
        }

    }

    property int radius: 100


    Repeater {
        visible: !submitButton.enabled
        id: loadingCircle
        model: 6
        Rectangle {
            visible: !submitButton.enabled
            width: 2*radius
            height: width
            color: "black"
            radius: 10
            property real angle: 0
            x: parent.width/2 + simulationParametersPage.radius * Math.sin((angle + 2*Math.PI*index/loadingCircle.count)%(2*Math.PI)) - width/2
            y: parent.height/2 + simulationParametersPage.radius * Math.cos((angle + 2*Math.PI*index/loadingCircle.count)%(2*Math.PI)) - height/2
            PropertyAnimation on angle {
                running: !submitButton.enabled
                loops: Animation.Infinite
                duration: 1000
                from: 2*Math.PI
                to: 0
            }
        }
    }
}
