import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VDT2026

Popup {
    property shipRadarInfo shipData
    property Item target

    modal: true
    focus: true
    width: 320
    height: 200

    x: target ? target.x + target.width : 10
    y: target ? target.y + target.height : 10

    background: Rectangle {
        color: Qt.rgba(1,1,1,0.8)
    }

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    function openFor(t: Item, d: shipRadarInfo) {
        target = t
        shipData = d

        open()
    }

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
