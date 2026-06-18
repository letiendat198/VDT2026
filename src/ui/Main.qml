import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "map"

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title: qsTr("VDT2026")

    header: AppToolBar {
        id: toolBar
    }

    footer: AppStatusBar {
        id: statusBar

        Connections {
            target: mainMap.map
            function onZoomLevelChanged(level) { statusBar.setZoomLevel(level) }
        }
    }

    MainMap {
        id: mainMap

        Connections {
            target: toolBar.selectionRect
            function onCheckedChanged() { mainMap.setSelectionEnabled(toolBar.selectionRect.checked, MainMap.SelectionType.Rect) }
        }

        Connections {
            target: toolBar.selectionPolygon
            function onCheckedChanged() { mainMap.setSelectionEnabled(toolBar.selectionPolygon.checked, MainMap.SelectionType.Polygon) }
        }
    }
}