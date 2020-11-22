import QtQuick 2.15

Rectangle {
    id: parentItem
    property var cities: 0
    onVisibleChanged: {
        if(visible) {
            var arr = [];
            let currentCities = map.getCities();
            for(var i = 0; i < currentCities.length; ++i) {
                let city = currentCities[i];
                let x = city.x;
                let y = city.y;
                console.debug("name:"+city.name+"x:" + x + ";y:"+y);
                let newX = canvas.x + x*canvas.width;
                let newY = canvas.y + y*canvas.height;
                let obj = Qt.createQmlObject('import QtQuick 2.15; Rectangle {color: "red"; width: 20; height: 20; Text{text: "'+city.name+'" }x: ' + newX + '; y: '+newY +';}', parentItem);
                arr.push(obj);
            }
            cities = arr;
        }
    }

    Image {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width
        source: "../resource/MapOfPoland.png"
    }
    Canvas {
        id:canvas
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.height > parent.width ? parent.width : parent.height
        height: width

        property color strokeStyle:  Qt.darker(fillStyle, 1.4)
        property bool fill: true
        property bool stroke: true
        property real alpha: 1.0
        antialiasing: true
        onPaint: {
//            var ctx = canvas.getContext('2d');
//            var originX = 85
//            var originY = 75
//            ctx.save();
//            ctx.clearRect(0, 0, canvas.width, canvas.height);
//            ctx.translate(originX, originX);
//            ctx.globalAlpha = canvas.alpha;
//            ctx.strokeStyle = canvas.strokeStyle;
//            ctx.fillStyle = canvas.fillStyle;
//            ctx.lineWidth = canvas.lineWidth;
//            ctx.translate(originX, originY)
//            ctx.scale(canvas.scale, canvas.scale);
//            ctx.translate(-originX, -originY)
            //! [0]
//            ctx.beginPath();
//            ctx.moveTo(75,40);
//            ctx.bezierCurveTo(75,37,70,25,50,25);
//            ctx.bezierCurveTo(20,25,20,62.5,20,62.5);
//            ctx.bezierCurveTo(20,80,40,102,75,120);
//            ctx.bezierCurveTo(110,102,130,80,130,62.5);
//            ctx.bezierCurveTo(130,62.5,130,25,100,25);
//            ctx.bezierCurveTo(85,25,75,37,75,40);
//            ctx.closePath();
            //! [0]
//            if (canvas.fill)
//                ctx.fill();
//            if (canvas.stroke)
//                ctx.stroke();
//            ctx.restore();
        }

    }
}
