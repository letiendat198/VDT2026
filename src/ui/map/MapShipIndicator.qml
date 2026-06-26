import QtQuick

Item {
    required property bool highlighted
    required property real angle

    property alias shipTapHandler: tapHandler

    // Need to explicitly set the width and height so it can be used to anchor the marker
    width: childrenRect.width
    height: childrenRect.height

    Image {
        id: shipMarker
        source: highlighted ? "qrc:/resources/marker_highlighted.svg" : "qrc:/resources/marker.svg"
        width: 25
        height: 25
        sourceSize.width: 25
        sourceSize.height: 25
        asynchronous: true
        transformOrigin: Item.Center
        rotation: angle
    }

    TapHandler {
        id: tapHandler
        parent: shipMarker
        acceptedButtons: Qt.LeftButton
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad | PointerDevice.Stylus
    }
}