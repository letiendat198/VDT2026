import QtQuick
import QtQuick.Effects

Item {
    required property bool highlighted
    required property real angle

    property alias shipTapHandler: tapHandler

    // Need to explicitly set the width and height so it can be used to anchor the marker
    width: childrenRect.width
    height: childrenRect.height

    Image {
        id: shipMarker
        source: "qrc:/resources/marker.svg"
        width: 25
        height: 25
        sourceSize.width: 25
        sourceSize.height: 25
        asynchronous: true
        mipmap: true
        // smooth: true
        // transformOrigin: Item.Center
        // rotation: angle
        // Hide it so it won't be rendered, which cause double rendering
        visible: false
    }

    MultiEffect {
        id: shipMarkerColor
        source: shipMarker
        anchors.fill: shipMarker
        transformOrigin: Item.Center
        rotation: angle
        colorization: 1
        saturation: 0.7
        brightness: 0.7
        colorizationColor: highlighted ? Qt.rgba(1,1,0,1) : Qt.rgba(0,1,0,1)
    }

    TapHandler {
        id: tapHandler
        parent: shipMarkerColor
        // parent: shipMarker
        acceptedButtons: Qt.LeftButton
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad | PointerDevice.Stylus
    }
}