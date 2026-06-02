import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    anchors.right: parent.right
    anchors.left: parent.left

    property alias zoomLevel: zoomLevelLbl

    RowLayout {
        anchors.fill: parent

        Text {
            id: ipAddrLbl
            text: "0.0.0.0:0000"
        }

        ToolSeparator {}

        Text {
            id: clientsConnectedLbl
            text: "No client"
        }

        Item {
            Layout.fillWidth: true
        }

        Text {
            id: pointerCoordLbl
            text: "0.00, 0.00"
        }

        ToolSeparator {}

        Text {
            id: zoomLevelLbl
            text: "Zoom: "
        }
    }
}
