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
        anchors.left: rec.left
        font.pixelSize: 10
    }

    Image {
        id: rec
        width: 10
        height: width
        source: "../resource/truck_icon.png"
    }

    Image {
        id: flame
        visible: false
        width: 10
        height: width
        anchors.bottom: rec.top
        anchors.horizontalCenter: rec.horizontalCenter
        source: "../resource/flame.png"
    }

    Connections {
        target: agent_
        function onHistoryUpdated() {
            totalDuration = 0;
            flame.visible = false;
            agentText.text = "";
            x = agent_.begining.x*parent.width;
            y = agent_.begining.y*parent.height;
            currentAnimationIndex = 0;
        }
    }
    property var totalDuration: 0

    onCurrentAnimationIndexChanged: {
        if(currentAnimationIndex < 0) return;
        let history = agent_.history;
        if(!history) return;
        if(history.length <= currentAnimationIndex) {
            agentText.text = "Koniec";
            return;
        }
        let current = history[currentAnimationIndex];
        if(current["state"] === "accident") {
            flame.visible = true;
            return;
        }

        let hour = timeText.hour;
        if(hour > 7) {
            hour = hour - 22;
        }
        let animationTime = hour*60 + timeText.minutes
        console.debug("agent total duration:" + totalDuration + ", mapTime:" + animationTime);

        totalDuration += parseInt(current["duration"]);

        animationDuration = current["duration"] * mapFrame.speed;
        if(current["state"] === "moving") {
            agentText.text = "";
            let point = map.getPointById(current["locationid"]);
            let percentage = 1;
            let newX = point.x*percentage*parent.width;
            let newY = point.y*percentage*parent.height;
            if(current.hasOwnProperty("percentage")) {
                percentage = parseFloat(current["percentage"]);
                newX = x + (newX-x)*percentage;
                newY = y + (newY-y)*percentage;
            }
            xAnimation.to = newX;
            yAnimation.to = newY;
        } else if(current["state"] === "waiting") {
            agentText.text = "oczekuje";
            xAnimation.to = x-5;
            yAnimation.to = y-5;
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
