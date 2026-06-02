import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


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
    }

    footer: AppStatusBar {
        id: statusBar
    }

    MainMap {
        id: mainMap

        Connections {
            target: mainMap.map

            function onZoomLevelChanged(level) {
                statusBar.zoomLevel.text = "Zoom: %1x".arg(level.toFixed(2))
            }
        }
    }
}