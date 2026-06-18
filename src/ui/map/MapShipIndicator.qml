import QtQuick

Item {
    property alias shipTapHandler: tapHandler

    Rectangle {
        id: shipMarker
        width: 20
        height: 20
        color: 'green'
        radius: 180
    }

    TapHandler {
        id: tapHandler
        parent: shipMarker
        acceptedButtons: Qt.LeftButton
        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad | PointerDevice.Stylus
    }
}