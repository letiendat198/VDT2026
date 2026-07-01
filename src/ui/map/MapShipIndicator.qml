import QtQuick

Item {
    required property real angle

    property bool highlighted : false

    property alias shipTapHandler: tapHandler

    // Need to explicitly set the width and height so it can be used to anchor the marker
    width: 25
    height: 25

    Image {
        id: shipMarker
        source: highlighted ? "qrc:/resources/marker_highlighted.svg" : "qrc:/resources/marker.svg"
        width: parent.width
        height: parent.height
        sourceSize.width: 25
        sourceSize.height: 25
        asynchronous: true
        transformOrigin: Item.Center
        rotation: angle
    }

    // Rectangle {
    //     anchors.centerIn: shipMarker

    //     width: 5
    //     height: 5
    // }

    TapHandler {
        id: tapHandler
        parent: shipMarker
        acceptedButtons: Qt.LeftButton
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad | PointerDevice.Stylus
    }
}