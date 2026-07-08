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
    property geoCoordinate currentMouseCoord

    // Any item inside refreshable should implement function refresh()
    property var refreshable: [shipView, watchView]

    Plugin {
        id: mapPlugin
        name: "osm"

        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://mt.google.com/vt/lyrs=m&x=%x&y=%y&z=%z"
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

        PinchHandler {
            target: null
            onScaleChanged: (delta) => {
                map.zoomLevel *= delta
            }
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
            enabled: !selectionHandler.enabled
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onPositionChanged: (e) => {
                currentMouseCoord = map.toCoordinate(Qt.point(e.x, e.y))
            }
        }

        MapNotification {
            id: notification

            z: 99
        }

        MapWatchView {
            id: watchView
            map: map
        }

        MapShipView {
            id: shipView
            map: map

            onShipEnteredWatchZone: (shipId, listWatchId) => {
                notification.add(shipId, listWatchId)
            }
        }

        MapSelectionHandler {
            id: selectionHandler
            z: 1
            map: map

            onSelectionFinished: (listCoordinate) => {
                WatchPolygonProvider.add(listCoordinate)
                this.enabled = false

                watchView.refresh()
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

    function setSelectionMode(enabled: bool) {
        console.log("Selection enable:" + enabled)

        if (selectionHandler.enabled !== enabled) {
            selectionHandler.enabled = enabled
        }
    }

    function setWatchDeleteMode(enabled: bool) {
        if (watchView.deleteMode !== enabled) watchView.deleteMode = enabled
    }

    function refresh() {
        for(var item of refreshable) {
            item.refresh()
        }
    }
}
