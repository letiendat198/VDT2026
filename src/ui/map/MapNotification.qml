import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Honestly, maybe consider QtQuick's Notification?
Rectangle {
    id: notificationRoot
    width: 400
    height: 100

    anchors.top: parent.top
    anchors.right: parent.right
    anchors.margins: 10

    visible: false

    property var listShipId : [] // list<int>
    property var listWatchId : [] // list<list<int>>

    property int index : -1
    property int notificationCount : 0 // Since JS list don't update bindings, we use this
    property bool forceLatest : true

    RowLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10

        id: headerRow
        Text {
            id: notificationTitle

            width: parent.width

            font.bold: true
            text: "Watch zone alert"

            wrapMode: Text.Wrap
        }

        Item { Layout.fillWidth: true }

        ToolButton {
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter

                text: "<"
            }

            onClicked: {
                if (index > 0) --index;
                forceLatest = false
            }
        }

        Text {
            id: pageCounter

            text: "%1/%2".arg(index + 1).arg(notificationCount)
        }

        ToolButton {
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter

                text: ">"
            }

            onClicked: {
                if (index < listShipId.length - 1) ++index
                forceLatest = false
            }
        }

        ToolButton {
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter

                text: "X"
            }

            onClicked: {
                notificationRoot.visible = false
                clear()
            }
        }
    }


    Text {
        id: notificationBody

        anchors.top: headerRow.bottom
        anchors.left: parent.left
        anchors.margins: 10

        width: parent.width

        text: index >= 0 ?
                  "Ship ID %1 has enterred watch zone%2 ID %3".arg(listShipId[index]).arg(listWatchId[index].length > 1 ? "s" : "").arg(listWatchId[index].join(", "))
                : "Invalid index"

        wrapMode: Text.Wrap
    }


    Timer {
        id: notificationExpireTimer
        interval: 3000
        repeat: false
        running: false
        triggeredOnStart: false

        onTriggered: visible = false
    }

    function add(shipId: int, watchIds: list<int>) {
        listShipId.push(shipId)
        listWatchId.push(watchIds)

        notificationCount = listShipId.length;
        if (forceLatest) index = listShipId.length - 1;

        show(true)
    }

    function clear() {
        // Clear index before clearing data, otherwise binding will update to undefined
        index = -1
        notificationCount = 0

        listShipId = []
        listWatchId = [[]]

        forceLatest = true
    }

    function show(timed: bool) {
        visible = true

        // In case multiple notification at the same time
        if (timed) notificationExpireTimer.restart()
        else notificationExpireTimer.stop()
    }
}
