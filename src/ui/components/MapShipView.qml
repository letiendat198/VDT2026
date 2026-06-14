import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item {
    required property Map map
    property var listShip

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
            required property geoCoordinate coord
            required property real angle
            required property real speed
            required property date timestamp
            required property int shipId

            coordinate: coord
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

                            text: qsTr("Ship ID: ") + shipId
                            wrapMode: Text.Wrap
                        }
                    }
                }
            }
        }
    }

    MapItemView {
        id: mapShipView
        model: listShip
        delegate: mapShipDelegate

        anchors.fill: parent
    }

    Connections {
        target: ShipRadarInfoProvider
        function onDataReady(data) {
            console.log("Data ready")
            console.log(data[0].shipId)
            console.log(data[0].coord)
            listShip = data
        }
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)

        ShipRadarInfoProvider.requestAllLastest()
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
