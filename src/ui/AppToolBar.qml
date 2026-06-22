import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    property alias selectionPolygon: selectionPolygonBtn

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
                id: selectionPolygonBtn
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
        }
    }

    function setSelectionRectBtnChecked(checked: bool) {
        selectionRectBtn.checked = checked
    }

    function setSelectionPolygonBtnChecked(checked: bool) {
        selectionPolygonBtn.checked = checked
    }
}
