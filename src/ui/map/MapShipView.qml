import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

Item {
    required property Map map
    property var listShip

    anchors.fill: parent

    MapInfoPopup {
        id: infoPopup
    }

    Component {
        id: mapShipDelegate

        MapQuickItem {
            id: mapItem
            coordinate: modelData.coord

            sourceItem: MapShipIndicator {
                id: shipIndicator
            }

            Connections {
                target: shipIndicator.shipTapHandler
                function onTapped() {
                    infoPopup.shipData = modelData
                    infoPopup.open()
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
            listShip = data
        }
    }

    Component.onCompleted: {
        map.addMapItemView(mapShipView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapShipView)
    }
}
