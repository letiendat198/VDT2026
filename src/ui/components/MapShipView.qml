import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item {
    required property Map map

    anchors.fill: parent
    ListModel {
        id: mapShipModel

        ListElement {
            latitude: 15
            longitude: 114
        }
    }

    Component {
        id: mapShipDelegate

        MapQuickItem {
            required property real latitude
            required property real longitude

            coordinate {
                latitude: latitude
                longitude: longitude
            }
            anchorPoint: shipMarker.Center

            sourceItem: Item {
                Rectangle {
                    id: shipMarker
                    width: 10
                    height: 10
                    color: 'green'
                    radius: 180
                }

                HoverHandler {
                    id: hoverHandler
                    acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                    parent: shipMarker
                }

                Rectangle {
                    id: infoRect
                    anchors.bottom: shipMarker.top
                    anchors.horizontalCenter: shipMarker.horizontalCenter
                    anchors.bottomMargin: 10

                    width: 200
                    height: 100
                    color: Qt.rgba(1, 1, 1, 0.5)
                    visible: hoverHandler.hovered ? true : false

                    ColumnLayout {
                        anchors.fill: parent

                        Text {
                            Layout.fillWidth: true
                            Layout.alignment: Qt.AlignTop

                            text: "Hello from the other sidee"
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }
        }
    }

    MapItemView {
        id: mapShipView
        model: mapShipModel
        delegate: mapShipDelegate

        anchors.fill: parent
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
