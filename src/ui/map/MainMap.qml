import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning
import QtLocation

import VDT2026

Item {
    anchors.fill: parent

    property alias zoomLevel: map.zoomLevel
    property alias shipCount: shipView.shipCount

    property alias selectionHandler: selectionHandler

    // Any item inside refreshable should implement function refresh()
    property var refreshable: [shipView, watchView]

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

        MapNotification {
            id: notification

            z: 99
        }

        MapShipView {
            id: shipView
            map: map

            onShipEnteredWatchZone: (shipId, listWatchId) => {
                var title = "Watch zone alert"
                var body = "Ship ID %1 has enterred watch zone%2 ID %3".arg(shipId).arg(listWatchId.length > 1 ? "s" : "").arg(listWatchId.join(", "))
                notification.show(title, body)
            }
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

                watchView.refresh()

                this.enabled = false
            }

            onSelectionCanceled: () => {
                this.enabled = false
            }
        }

        // Zoom control
        Rectangle {
            width: 30
            height: 65
            visible: !selectionHandler.enabled

            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10

            z: 1

            ColumnLayout {
                anchors.fill: parent

                ToolButton {
                    Layout.fillWidth: parent

                    text: "+"
                    onClicked: map.zoomLevel += 0.5
                }

                ToolButton {
                    Layout.fillWidth: parent

                    text: "-"
                    onClicked: map.zoomLevel -= 0.5
                }
            }
        }

        Component.onCompleted: {
            zoomLevelChanged(zoomLevel)
        }
    }

    function setSelectionEnabled(enabled: bool) {
        console.log("Selection enable:" + enabled)

        if (selectionHandler.enabled !== enabled) {
            selectionHandler.enabled = enabled
        }
    }

    function refresh() {
        for(var item of refreshable) {
            item.refresh()
        }
    }
}
