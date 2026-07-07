import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning

ToolBar {
    property int shipCount : 0
    property real zoomLevel : 0
    property geoCoordinate currentMouseCoord

    anchors.right: parent.right
    anchors.left: parent.left

    RowLayout {
        anchors.fill: parent

        Text {
            text: "Displaying %1 ship%2".arg(shipCount).arg(shipCount > 1 ? "s" : "")
        }

        ToolSeparator {}

        Item { Layout.fillWidth: true }

        ToolSeparator {}

        Text {
            text: "%1".arg(currentMouseCoord)
        }

        ToolSeparator {}

        Text {
            text: "Zoom: %1x".arg(zoomLevel)
        }
    }
}
