import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    property alias selection: selectionBtn
    property alias refresh: refreshBtn
    property alias deleteSelection: deleteSelectionBtn
    property alias preferences: preferencesBtn

    RowLayout {
        anchors.fill: parent

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

            Item { Layout.fillWidth: true }

            ToolButton {
                id: preferencesBtn
                text: qsTr("Preferences")

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Change preferences")
            }
        }
    }

    function reset() {
        console.log("Toolbar reset")
        panBtn.checked = true
    }
}
