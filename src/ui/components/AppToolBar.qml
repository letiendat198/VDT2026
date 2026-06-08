import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    property alias zoomIn: zoomInBtn
    property alias zoomOut: zoomOutBtn
    property alias selectionRect: selectionRectBtn
    property alias selectionCircle: selectionCircleBtn
    property alias selectionPolygon: selectionPolygonBtn

    enum SelectionType { Rect = 0, Circle = 1, Polygon = 2 }

    RowLayout {
        ToolButton {
            id: zoomInBtn
            text: "+"

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Zoom in")
        }

        ToolButton {
            id: zoomOutBtn
            text: "-"

            ToolTip.visible: hovered
            ToolTip.text: qsTr("Zoom out")
        }

        ToolSeparator {}

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
                id: selectionCircleBtn
                text: qsTr("Circle")
                checkable: true

                ToolTip.visible: hovered
                ToolTip.text: qsTr("Select a circular region")
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

    function setSelectionCircleBtnChecked(checked: bool) {
        selectionCircleBtn.checked = checked
    }

    function setSelectionPolygonBtnChecked(checked: bool) {
        selectionPolygonBtn.checked = checked
    }
}
