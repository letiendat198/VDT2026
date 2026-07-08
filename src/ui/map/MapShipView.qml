import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

import VDT2026

Item {
    required property Map map

    property int shipCount : 0

    signal shipEnteredWatchZone(shipId: int, listWatchId: list<int>)

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

            // Zoom level is borked
            // zoomLevel: 8

            sourceItem: MapShipIndicator {
                id: shipIndicator
                angle: shipData.angle
                highlighted: shipData.listCrossedWatchPolygonId.length > 0
                width: (map.zoomLevel * 25) / 16
                height: (map.zoomLevel * 25) / 16
            }

            // Have to define connections outside, cause inside sourceItem don't have shipData context
            Connections {
                target: shipIndicator
                function onHighlightedChanged() {
                    if (shipIndicator.highlighted) {
                        shipEnteredWatchZone(shipData.shipId, shipData.listCrossedWatchPolygonId)
                    }
                }
            }

            Connections {
                target: shipIndicator.shipTapHandler
                function onTapped() {
                    // var p = map.fromCoordinate(shipData.coord)
                    // infoPopup.openAt(p.x, p.y, shipData)
                    infoPopup.openFor(mapItem)
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
            shipCount = shipModel.rowCount()
            // console.log(data)
        }
    }

    function refresh() {
        shipModel.clear();
        // ShipRadarInfoProvider.requestAllLatest()
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
