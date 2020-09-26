import QtQuick 2.0

Rectangle {
    id: canvas
    width: 1404
    height: 1872
    signal qmlSignal(int x, int y)


    function getVolBlock() {
       return vol_block
    }

    Image {
        id: image
        x: -132
        y: -7
        width: 1406
        height: 1895
        source: "../images/hex-grid.png"
        scale: 1.3
        rotation: 90
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: text1
        x: 36
        y: 1074
        width: 1979
        height: 624
        text: qsTr("Pen Landing Zones")
        font.pixelSize: 120
        font.family: "Tahoma"
        rotation: 90
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}
}
##^##*/
