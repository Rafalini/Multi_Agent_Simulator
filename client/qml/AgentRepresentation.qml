import QtQuick 2.15

Item {
    id: agentRepresentation
    property var agent_
    property bool isAnimationRunning: false
    property int currentAnimationIndex: -10 //default to anything less than -1
    visible: currentAnimationIndex >= 0 && isAnimationRunning
    Text {
        id: agentText
        anchors.bottom: rec.top
    }

    function animationFinished() {}

    Image {
        id: rec
        width: 15
        height: width
        source: "../resource/truck_icon.png"
    }
    Connections {
        target: agent_
        function onHistoryUpdated() {
            agentText.text = "";
            x = agent_.begining.x*parent.width;
            y = agent_.begining.y*parent.height;
            currentAnimationIndex = 0;
        }
    }
    onCurrentAnimationIndexChanged: {
        if(currentAnimationIndex < 0) return;
        let history = agent_.history;
        if(!history) return;
        if(history.length <= currentAnimationIndex) {
            animationFinished();
            agentText.text = "";
            return;
        }
        let current = history[currentAnimationIndex];
        if(current["state"] === "accident") {
            agentText.text = "Wypadek...";
            animationFinished();
            return;
        }
        animationDuration = current["duration"] * 10;
        if(current["state"] === "moving") {
            agentText.text = "";
            let point = map.getPointById(current["locationid"]);
            let percentage = 1;
            if(current.hasOwnProperty("percentage")) {
                percentage = parseFloat(current["percentage"]);
            }
            xAnimation.to = point.x*percentage*parent.width;
            yAnimation.to = point.y*percentage*parent.height;
        } else {
            if(current["state"] === "loading"){
                agentText.text = "Trwa załadunek...";
            } else if(current["state"] === "unloading") {
                agentText.text = "Trwa rozładunek...";
            } else if(current["state"] === "break") {
                agentText.text = "Przerwa";
            }
            xAnimation.to = x+1;
            yAnimation.to = y+1;
        }
        xAnimation.restart();
        yAnimation.restart();
    }
    property int animationDuration: 0
    NumberAnimation on x {
        id: xAnimation
        duration: agentRepresentation.animationDuration
        onFinished: agentRepresentation.currentAnimationIndex++
    }
    NumberAnimation on y {
        id: yAnimation
        duration: agentRepresentation.animationDuration
    }
}
