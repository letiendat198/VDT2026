import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    property alias selectionRect: selectionRectBtn
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
                id: selectionRectBtn
                text: qsTr("Rect")
                checkable: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Select a rectangular region")
            }

            ToolButton {
                id: selectionPolygonBtn
                text: qsTr("Polygon")
                checkable: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Select a polygonal region")
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
