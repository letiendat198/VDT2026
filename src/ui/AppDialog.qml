import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

Dialog {
    enum Level {
        Notice = 0,
        Warning = 1,
        Error = 2,
        Fatal = 3
    }
    property int level : 0
    property string message

    title: Qt.enumValueToString(AppDialog.Level, level)
    standardButtons: Dialog.Ok
    modal: true
    popupType: Popup.Window

    anchors.centerIn: Overlay.overlay

    Label {
        anchors.fill: parent

        horizontalAlignment: Label.AlignHCenter
        wrapMode: Label.Wrap
        text: message
    }

    function show(lv, msg) {
        level = lv
        message = msg

        console.log(Qt.enumValueToString(AppDialog.Level, level))

        open()
    }

    onAccepted: close()
    onDiscarded: close()
    onRejected: close()
}
