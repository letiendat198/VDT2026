import QtQuick
import QtQuick.Controls
import QtPositioning
import QtLocation

Item {
    anchors.fill: parent

    property alias map: map

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://api.thunderforest.com/atlas/%z/%x/%y.png?apikey=%1".arg(THUNDERFOREST_API_KEY) // Provided by rootContext
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(15.53, 114.97)
        zoomLevel: 5.2
        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                                         ? PointerDevice.Mouse | PointerDevice.TouchPad
                                         : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }

        Component.onCompleted: {
            zoomLevelChanged(zoomLevel)
        }
    }
}
