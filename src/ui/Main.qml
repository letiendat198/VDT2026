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
        zoomLevel: mainMap.zoomLevel
        shipCount: mainMap.shipCount
    }

    MainMap {
        id: mainMap
    }

    // Sync selection button on toolbar with selection handler state
    Connections {
        target: toolBar.selection
        function onCheckedChanged() { mainMap.setSelectionEnabled(toolBar.selection.checked) }
    }

    Connections {
        target: mainMap.selectionHandler
        function onEnabledChanged() {
            var enabled = mainMap.selectionHandler.enabled
            if (enabled == toolBar.selection.checked) return

            // If mainMap selection somehow becomes active, sync the state to button
            if (enabled) toolBar.selection.checked = enabled
            // But if it's disabled, please reset to pan
            else toolBar.reset()
        }
    }

    Connections {
        target: toolBar.refresh
        function onClicked() {
            mainMap.refresh()
        }
    }
}