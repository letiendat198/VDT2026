import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

import VDT2026

Item {
    required property Map map

    property list<shipRadarInfo> listShipData

    signal shipEnteredWatchZone(shipId: int, watchId: int)

    anchors.fill: parent

    MapInfoPopup {
        id: infoPopup
    }

    ShipRadarInfoItemModel {
        id: shipModel
    }

    Component {
        id: mapShipDelegate

        MapQuickItem {
            required property shipRadarInfo shipData

            property bool ready: false

            id: mapItem
            coordinate: shipData.coord
            anchorPoint.x: shipIndicator.width / 2
            anchorPoint.y: shipIndicator.height / 2

            sourceItem: MapShipIndicator {
                id: shipIndicator
                color: shipData.listCrossedWatchPolygonId.length === 0 ? "green" : "yellow"
            }

            Component.onCompleted: {
                ready = true
            }

            Connections {
                target: shipIndicator
                function onColorChanged() {
                    if (ready && shipData.listCrossedWatchPolygonId.length > 0) {
                        shipEnteredWatchZone(shipData.shipId, shipData.listCrossedWatchPolygonId[0])
                    }
                }
            }

            Connections {
                target: shipIndicator.shipTapHandler
                function onTapped() {
                    infoPopup.shipData = shipData
                    infoPopup.open()
                }
            }
        }
    }

    MapItemView {
        id: mapShipView
        model: shipModel
        delegate: mapShipDelegate

        anchors.fill: parent
    }

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            ShipRadarInfoProvider.requestAllLatest()
        }
    }

    Connections {
        target: ShipRadarInfoProvider
        function onDataReady(data) {
            // console.log("Data ready")
            shipModel.update(data)
            // console.log(data)
        }
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
