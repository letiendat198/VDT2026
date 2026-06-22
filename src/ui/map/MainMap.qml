import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
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
        zoomLevel: 7
        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]

        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                                         ? PointerDevice.Mouse | PointerDevice.TouchPad
                                         : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
            enabled: !selectionHandler.enabled
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
            enabled: !selectionHandler.enabled
        }

        MapShipView {
            id: shipView
            map: map
        }

        MapWatchPolygonView {
            id: watchView
            map: map
        }

        MapSelectionHandler {
            id: selectionHandler
            z: 1
            map: map

            onSelectionFinished: (listCoordinate) => {
                WatchPolygonProvider.add(listCoordinate)
            }
        }

        // Zoom control
        Rectangle {
            width: childrenRect.width
            height: childrenRect.height
            visible: !selectionHandler.enabled

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10

            z: 1

            ColumnLayout {
                width: childrenRect.width
                height: childrenRect.height

                ToolButton {
                    text: "+"
                    onClicked: zoomIn()
                }

                ToolButton {
                    text: "-"
                    onClicked: zoomOut()
                }
            }
        }

        MapNotification {
            id: notification

            z: 99
        }

        Component.onCompleted: {
            zoomLevelChanged(zoomLevel)
        }
    }

    function zoomIn() {
        map.zoomLevel += 0.5
    }

    function zoomOut() {
        map.zoomLevel -= 0.5
    }

    function setSelectionEnabled(enabled: bool) {
        if (selectionHandler.enabled !== enabled) {
            selectionHandler.enabled = enabled
        }
    }
}
