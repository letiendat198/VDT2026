import QtQuick
import QtQuick.Controls

// Honestly, maybe consider QtQuick's Notification?
Rectangle {
    width: 400
    height: 150

    anchors.top: parent.top
    anchors.right: parent.right
    anchors.margins: 10

    visible: true

    Text {
        id: notificationTitle

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10

        width: parent.width

        text: "If you're seeing this"

        wrapMode: Text.Wrap
    }

    Text {
        id: notificationBody

        anchors.top: notificationTitle.bottom
        anchors.left: parent.left
        anchors.margins: 10

        width: parent.width

        text: "Then notification is used inapproriately, please call show()"

        wrapMode: Text.Wrap
    }

    ToolButton {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 10

        Text {
            anchors.fill: parent
            horizontalAlignment: Text.AlignHCenter

            text: "X"
        }

        onClicked: parent.visible = false
    }

    Timer {
        id: notificationExpireTimer
        interval: 3
        repeat: false
        running: false
        triggeredOnStart: false

        onTriggered: visible = false
    }

    function show(title: string, body: string) {
        notificationTitle.text = title
        notificationBody.text = body

        visible = true

        notificationExpireTimer.start()
    }
}
