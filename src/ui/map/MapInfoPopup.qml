import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Popup {
    property shipRadarInfo shipData

    modal: true
    focus: true
    width: 320
    height: 200
    x: 10
    y: 10
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    ColumnLayout {
        anchors.fill: parent

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            font.bold: true

            text: qsTr("Ship information")
        }

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            text: qsTr("Ship ID: ") + shipData.shipId
            wrapMode: Text.Wrap
        }

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            text: qsTr("Coordinate: ") + shipData.coord
            wrapMode: Text.Wrap
        }

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            text: qsTr("Bearing: ") + shipData.angle + "°"
            wrapMode: Text.Wrap
        }

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            text: qsTr("Speed: ") + shipData.speed + " m/s"
            wrapMode: Text.Wrap
        }

        Text {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignTop

            text: qsTr("Last updated: ") + Qt.formatDateTime(shipData.timestamp, "dd/MM/yyyy - hh:mm:ss zzz")
            wrapMode: Text.Wrap
        }
    }
}
