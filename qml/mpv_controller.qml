//import QtQuick 2.15



import QtQuick 2.6
import QtQuick.Window 2.2

//import Test 1.0


Rectangle {
    id: canvas
    width: 1404
    height: 1872
    signal qmlSignal(int x, int y)

    signal launchSignal(int event, string s)

    function getVolBlock() {
        return mpv_block
    }

    MouseArea {
        anchors.fill: parent
        anchors.rightMargin: -9
        anchors.bottomMargin: -12
        anchors.leftMargin: 9
        anchors.topMargin: 12

        //            onClicked: { parent.color = 'red' }
        onPositionChanged:
        {canvas.qmlSignal(mouse.x,mouse.y)
            //            console.log("Test");
        }

        Text {
            id: text2
            x: -185
            y: 892
            width: 1853
            height: 70
            text: qsTr("MPV Media Controller")
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            rotation: 90
        }

    }

    Image {
        id: image
        x: -904
        y: 836
        width: 1872
        height: 201
        source: "../images/gradient.png"
        rotation: 90
        fillMode: Image.PreserveAspectFit
        transformOrigin: Item.Center
    }


    Rectangle {
        id: mpv_block
        objectName: "mpv_block"
        x: -3
        y: 1872
        width: 83

        height: 1872
        color: "#ffffff"
        layer.smooth: true
        clip: true
    }




    Text {
        id: text1
        x: -863
        y: 884
        width: 1872
        height: 105
        text: qsTr("Timeline Scrubber")
        font.pixelSize: 42
        horizontalAlignment: Text.AlignHCenter
        rotation: 90
        transformOrigin: Item.Center
    }


    Item {
        id: yt
        x: 1252
        y: -140
        width: 428
        height: 348
        visible: false

        Image {
            id: image1
            width: 300
            height: 280
            source: "../images/youtube.png"
            rotation: 90
            fillMode: Image.PreserveAspectFit
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {

                canvas.launchSignal(1, "http://youtube.com");
            }
        }
    }


    Item {
        id: krita
        x: 1262
        y: -145
        width: 428
        height: 348
        visible: false;
        Image {
            id: image2
            width: 300
            height: 280
            source: "../images/photoshop.png"
            rotation: 90
            fillMode: Image.PreserveAspectFit
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                canvas.launchSignal(2, "krita");
            }
        }
    }



    Item {
        id: block
        x: 1252
        y: -121
        width: 296
        height: 300
        property bool radialOpen: false

        //        PropertyAnimation {
        //            id: animMove;
        //            target:block
        //            properties:"x"
        //            from: 0;
        //            to: 200;
        //            duration: 200}
        Image {
            id: pic
            source: "../images/circle.png"
            visible: true //hidden by default
            anchors.centerIn: parent
        }

        ParallelAnimation {
            id: animMoveForward;
            PropertyAnimation{target: yt; property: "x"; from:1252; to: 1064; duration: 1}
            PropertyAnimation{target: yt; property: "y"; from:-140; to: 232; duration: 1}
            PropertyAnimation{target: krita; property: "x"; from:1262; to: 834; duration: 1}
            PropertyAnimation{target: krita; property: "y"; from:-145; to: 3; duration: 1}
        }
        ParallelAnimation {
            id: animMoveBackward;
            PropertyAnimation{target: yt; property: "x"; from:1064; to: 1352; duration: 1}
            PropertyAnimation{target: yt; property: "y"; from:232; to: -240; duration: 1}
            PropertyAnimation{target: krita; property: "x"; from:834; to: 1362; duration: 1}
            PropertyAnimation{target: krita; property: "y"; from:3; to: -245; duration: 1}
        }
        MouseArea {
            anchors.fill: parent

            onClicked: {
                yt.visible = true;
                krita.visible = true;
                if(block.radialOpen)
                {
                    block.radialOpen = false
                    animMoveBackward.start();
                }
                else
                {
                    block.radialOpen = true
                    animMoveForward.start();
                }
            }
        }
    }

    Item {
        id: bat
        x: 1323
        y: 170
        width: 175
        height: 337
        rotation: 0


        Column {
            id: column
            anchors.fill: parent
            spacing: 12

            Image {
                id: bat_image
                objectName: "bat_image"
                width: 77
                height: 107
                source: "qrc:/images/battery/battery_discharging_100.png"
                rotation: 180
                mirror: false
                transformOrigin: Item.Center
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: bat_percent
                objectName: "bat_percent"
                text: qsTr("100%")
                font.pixelSize: 31
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop
                rotation: 90
                minimumPixelSize: 25
            }
        }

    }
}



/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}
}
##^##*/
