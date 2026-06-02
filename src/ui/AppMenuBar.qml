import QtQuick
import QtQuick.Controls

MenuBar {
    Menu {
        title: qsTr("&Options")
        Action { text: qsTr("&Start/Stop server") }
        Action { text: qsTr("&Show details...") }
    }
}
