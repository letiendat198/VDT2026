import QtQuick
import QtQuick.Controls
import QtLocation
import QtPositioning

// Handle selection on map
// It only needs to show selection preview, so just use normal rectangle/circle or canvas overlay
// No need to use MapItem
Item {
    required property DragHandler dragHandler

    property bool enabled: false

    property point startPoint
    property point endPoint

    signal selectionStarted(start: point)
    signal selectionFinished(start: point, end: point)

    anchors.fill: parent

    Canvas {
        id: selectionPreview
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();
            ctx.fillStyle = Qt.rgba(0, 0, 1, 0.2);
            ctx.fillRect(startPoint.x, startPoint.y, Math.abs(endPoint.x - startPoint.x), Math.abs(endPoint.y - startPoint.y));
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: false

        onPressed: (e) => {
            startPoint = Qt.point(e.x, e.y)
        }

        onPositionChanged: (e) => {
            endPoint = Qt.point(e.x, e.y)
            selectionPreview.requestPaint()
        }

        onReleased: (e) => {
            selectionFinished(startPoint, endPoint)

            startPoint = null // This actually put it to point(0,0)
            endPoint = null
            selectionPreview.requestPaint()
        }
    }

    onEnabledChanged: {
        if (enabled) {
            mouseArea.enabled = true
            dragHandler.enabled = false
        }
        else {
            mouseArea.enabled = false
            dragHandler.enabled = true
        }
    }
}

