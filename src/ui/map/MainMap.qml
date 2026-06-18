import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning
import QtLocation

Item {
    anchors.fill: parent

    property alias map: map

    enum SelectionType { Rect = 0, Polygon = 1 }

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
            enabled: !rectSelectionHandler.enabled && !polygonSelectionHandler.enabled
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
            enabled: !rectSelectionHandler.enabled && !polygonSelectionHandler.enabled
        }

        MapShipView {
            map: map
        }

        MapRectSelectionHandler {
            id: rectSelectionHandler
            z: 1
        }

        MapPolygonSelectionHandler {
            id: polygonSelectionHandler
            z: 1
        }

        Component.onCompleted: {
            zoomLevelChanged(zoomLevel)
        }

        Rectangle {
            width: childrenRect.width
            height: childrenRect.height
            visible: !rectSelectionHandler.enabled && !polygonSelectionHandler.enabled

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

    }

    function zoomIn() {
        map.zoomLevel += 0.5
    }

    function zoomOut() {
        map.zoomLevel -= 0.5
    }

    function setSelectionEnabled(enabled: bool, type: int) {
        var selectionList = [rectSelectionHandler, polygonSelectionHandler]
        for (var i=0; i<selectionList.length; i++) {
            if (i === type) selectionList[i].enabled = enabled;
            else {
                // If enable a selection, set others to false
                // Otherwise, don't change because the ToolButton uncheck signal may come after another ToolButton checked signal
                // thus disable the newly selected tool
                if (enabled) selectionList[i].enabled = false;
            }
        }
    }
}
