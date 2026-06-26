import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

import VDT2026

Item {
    required property Map map
    property bool lazyLoading: true

    property int shipCount : 0
    property geoPolygon visiblePolygon

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

            width: shipIndicator.width
            height: shipIndicator.height

            sourceItem: MapShipIndicator {
                id: shipIndicator
                angle: shipData.angle
                highlighted: shipData.listCrossedWatchPolygonId.length > 0
            }

            Component.onCompleted: {
                // console.log("Marker for " + shipData.shipId + " initialized");
                ready = true
            }

            // Have to define connections outside, cause inside sourceItem don't have shipData context
            Connections {
                target: shipIndicator
                function onHighlightedChanged() {
                    // Avoid triggering highlight changed signal when initing
                    if (ready && shipIndicator.highlighted) {
                        shipEnteredWatchZone(shipData.shipId, shipData.listCrossedWatchPolygonId)
                    }
                }
            }

            Connections {
                target: shipIndicator.shipTapHandler
                function onTapped() {
                    infoPopup.openFor(mapItem, shipData)
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
            refresh()
        }
    }

    Connections {
        target: ShipRadarInfoProvider
        function onDataReady(data) {
            // console.log("Data ready")
            shipModel.update(data)
            shipCount = data.length
            // console.log(data)
        }
    }

    function refresh() {
        if (!lazyLoading) ShipRadarInfoProvider.requestAllLatest();
        else {
            var visibleRegion = map.visibleRegion;
            visiblePolygon = QtPositioning.shapeToPolygon(visibleRegion);
            // Qt doc hasn't update yet
            // https://doc.qt.io/qt-6/qml-geoshape.html is outdated
            // https://doc.qt.io/qt-6/qtpositioning-changes-qt6.html this actually show path was renamed perimeter
            ShipRadarInfoProvider.requestAllLatestWithin(visiblePolygon.perimeter);
        }
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
