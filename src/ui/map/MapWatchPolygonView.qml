import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

import VDT2026

Item {
    required property Map map
    property var listWatchPolygon

    anchors.fill: parent

    Component {
        id: mapWatchDelegate

        MapPolygon {
            color: Qt.rgba(1, 1, 0, 0.3)
            border.color: Qt.rgba(1, 1, 0, 1)
            border.width: 1

            path: modelData.listCoord
        }
    }

    MapItemView {
        id: mapWatchView
        model: listWatchPolygon
        delegate: mapWatchDelegate

        anchors.fill: parent
    }

    Connections {
        target: WatchPolygonProvider
        function onDataReady(data) {
            listWatchPolygon = data
        }
    }

    Component.onCompleted: {
        WatchPolygonProvider.requestAll()

        map.addMapItemView(mapWatchView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapWatchView)
    }
}