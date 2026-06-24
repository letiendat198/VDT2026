import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    property alias selection: selectionBtn
    property alias refresh: refreshBtn
    property alias deleteSelection: deleteSelectionBtn

    RowLayout {
        ButtonGroup {
            buttons: toolButtons.children
        }

        RowLayout {
            id: toolButtons

            ToolButton {
                id: panBtn
                text: qsTr("Pan")
                checkable: true
                checked: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Pan view")
            }

            ToolButton {
                id: selectionBtn
                text: qsTr("Select")
                checkable: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Select a polygonal region")
            }

            ToolButton {
                id: deleteSelectionBtn
                text: qsTr("Delete")
                checkable: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Delete a selection region")
            }

            ToolButton {
                id: refreshBtn
                text: qsTr("Refresh")

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Refresh all data")
            }
        }
    }

    function reset() {
        console.log("Toolbar reset")
        panBtn.checked = true
    }
}
