import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

import VDT2026

Item {
    required property Map map
    property var listWatchPolygon
    property bool deleteMode: false

    anchors.fill: parent

    Component {
        id: mapWatchDelegate

        MapPolygon {
            color: Qt.rgba(1, 1, 0, 0.3)
            border.color: Qt.rgba(1, 1, 0, 1)
            border.width: 1
            referenceSurface: "Globe"

            path: modelData.listCoord
        }
    }

    // Since map polygon can't have children. And MapQuickItem can't be used to position a polygon, i guess this is the last option
    Component {
        id: watchAnoteDelegate

        MapQuickItem {
            coordinate: modelData.listCoord[0]

            anchorPoint.x: watchAnoteItem.x + watchAnoteItem.width / 2
            anchorPoint.y: watchAnoteItem.y + watchAnoteItem.height

            sourceItem: Item {
                id: watchAnoteItem
                width: childrenRect.width
                height: childrenRect.height

                Row {
                    spacing: 2
                    Text {
                        id: watchId
                        text: "ID %1".arg(modelData.id)

                        color: "white"
                    }

                    ToolButton {
                        id: watchDeleteBtn

                        visible: deleteMode ? true : false
                        onClicked: {
                            removeWatch(modelData.id)
                        }

                        background: Rectangle {
                            implicitWidth: 20
                            implicitHeight: 20
                            color: watchDeleteBtn.hovered ? Qt.rgba(0,0,0,0.5) : Qt.rgba(0,0,0,0)
                        }

                        Text {
                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            text: "X"
                            color: "red"
                        }
                    }
                }
            }
        }
    }

    MapItemView {
        id: mapWatchView
        model: listWatchPolygon
        delegate: mapWatchDelegate

        anchors.fill: parent
    }

    MapItemView {
        id: watchAnnoteView
        model: listWatchPolygon
        delegate: watchAnoteDelegate

        anchors.fill: parent
    }

    Connections {
        target: WatchPolygonProvider
        function onDataReady(data) {
            listWatchPolygon = data
        }
    }

    function refresh() {
        WatchPolygonProvider.requestAll()
    }

    function removeWatch(id: int) {
        WatchPolygonProvider.remove(id)
        refresh()
    }

    Component.onCompleted: {
        refresh()

        map.addMapItemView(mapWatchView)
        map.addMapItemView(watchAnnoteView)
    }

    Component.onDestruction: {
        map.removeMapItemView(mapWatchView)
        map.removeMapItemView(watchAnnoteView)
    }
}