import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VDT2026

import "map"

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title: qsTr("VDT2026")

    header: AppToolBar {
        id: toolBar

        // Sync selection button on toolbar with selection handler state
        Connections {
            target: toolBar.selection
            function onCheckedChanged() { mainMap.setSelectionMode(toolBar.selection.checked) }
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


        // Sync delete button to map selection delete
        // But sync delete mode won't deactivate itself, no need to wire back
        Connections {
            target: toolBar.deleteSelection
            function onCheckedChanged() { mainMap.setWatchDeleteMode(toolBar.deleteSelection.checked) }
        }


        Connections {
            target: toolBar.refresh
            function onClicked() {
                mainMap.refresh()
            }
        }


        Connections {
            target: toolBar.preferences
            function onClicked() {
                preferences.open()
            }
        }
    }

    footer: AppStatusBar {
        id: statusBar
        zoomLevel: mainMap.zoomLevel
        shipCount: mainMap.shipCount
        currentMouseCoord: mainMap.currentMouseCoord
    }

    MainMap {
        id: mainMap
    }

    Preferences {
        id: preferences
    }

    AppDialog {
        id: dialog

        Connections {
            target: DialogProvider
            function onDialogRequested(level, body) {
                dialog.show(level, body)
            }
        }
    }
}