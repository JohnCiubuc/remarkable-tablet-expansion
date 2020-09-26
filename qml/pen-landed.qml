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
        x: -5
        y: -13
        width: 1406
        height: 1895
        source: "../images/spiral.jpg"
        fillMode: Image.PreserveAspectFit
    }


}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.33000001311302185}
}
##^##*/
