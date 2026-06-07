import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "components"

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title: qsTr("VDT2026")

    menuBar: AppMenuBar {
        id: menuBar
    }

    header: AppToolBar {
        id: toolBar

        // Connections {
        //     target: mainMap.selectionHandler
        //     function onEnabledChanged() {
        //         toolBar.selectionRect.checked = mainMap.selectionHandler.enabled
        //     }
        // }
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
            target: toolBar.zoomIn
            function onPressed() { mainMap.zoomIn() }
        }

        Connections {
            target: toolBar.zoomOut
            function onPressed() { mainMap.zoomOut() }
        }

        Connections {
            target: toolBar.selectionRect
            function onCheckedChanged() { mainMap.setSelectionEnabled(toolBar.selectionRect.checked) }
        }
    }
}