import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning
import QtLocation

// Handle polyhon selection on map
// It only needs to show selection preview, so just use normal canvas overlay
// No need to use MapItem
Item {
    required property Map map
    property bool enabled: false

    property list<point> listPoint

    signal selectionFinished(listCoordinate: list<geoCoordinate>)

    id: selectionHandler
    anchors.fill: parent

    Canvas {
        id: selectionPreview
        anchors.fill: parent
        z: 1

        onPaint: {
            var ctx = getContext("2d");
            ctx.reset();

            if (listPoint.length === 0) return;

            ctx.fillStyle = Qt.rgba(1, 1, 0, 0.3);
            ctx.lineWidth = 1;
            ctx.strokeStyle = Qt.rgba(1, 1, 0, 1);
            ctx.textAlign = "end"
            ctx.textBaseline = "bottom"
            ctx.font = "20px sans-serif"

            var count = 0
            ctx.beginPath();

            for(var p of listPoint) {
                ctx.save();
                ctx.fillStyle = Qt.rgba(1, 1, 1, 1);
                ctx.fillText(count + 1, p.x, p.y);
                ctx.restore();

                if (count == 0) {
                    // console.log("Move to " + p.x + " " + p.y)
                    ctx.moveTo(p.x, p.y);
                }
                else {
                    // console.log("Line to " + p.x + " " + p.y)
                    ctx.lineTo(p.x, p.y);
                }

                count++;
            }
            ctx.closePath();
            ctx.fill();
            ctx.stroke();
        }
    }

    Rectangle {
        width: childrenRect.width
        height: childrenRect.height
        visible: parent.enabled

        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        z: 2

        RowLayout {
            width: childrenRect.width
            height: childrenRect.height

            ToolButton {
                text: "Cancel"
                onClicked: selectionHandler.enabled = false;
            }

            ToolButton {
                text: "Save"
                onClicked: {
                    // Convert to geoCoordinate before emitting
                    var listCoordinate = []
                    for(var p of listPoint) {
                        listCoordinate.push(map.toCoordinate(p))
                    }

                    selectionFinished(listCoordinate)

                    selectionHandler.enabled = false;
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 0.1)
        visible: parent.enabled
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        enabled: parent.enabled

        onPressed: (e) => {
            listPoint.push(Qt.point(e.x, e.y))

            // console.log(listPoint)

            selectionPreview.requestPaint()
        }
    }

    onEnabledChanged: {
        if (!enabled) {
            listPoint = []
            selectionPreview.requestPaint();
        }
    }
}


