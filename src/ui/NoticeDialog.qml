import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

Dialog {
    enum Level {
        Notice = 0,
        Warn = 1,
        Error = 2,
        Fatal = 3
    }
    property Level level
    property string message

    title: Qt.enumValueToString(NoticeDialog.Level, level)
    standardButtons: Dialog.OK
    modal: true
    popupType: Popup.Window

    width: contentItem.childrenRect.width

    anchors.centerIn: Overlay.overlay

    contentItem: Label {
        anchors.fill: parent

        horizontalAlignment: Label.AlignHCenter
        wrapMode: Label.Wrap
        text: message
    }

    function show(lv, msg) {
        level = lv
        message = msg

        open()
    }
}
