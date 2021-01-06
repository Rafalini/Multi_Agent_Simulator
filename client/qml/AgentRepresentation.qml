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
        animationDuration = current["duration"] * 10;
        if(current["state"] === "moving") {
            agentText.text = "";
            let point = map.getPointById(current["locationid"]);
            xAnimation.to = point.x*parent.width;
            yAnimation.to = point.y*parent.height;
        } else if(current["state"] === "loading"){
            agentText.text = "Trwa załadunek...";
            xAnimation.to = x+1;
            yAnimation.to = y+1;
        } else {
            agentText.text = "Trwa rozładunek...";
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
