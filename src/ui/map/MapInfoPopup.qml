import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import VDT2026

Popup {
    property shipRadarInfo shipData
    property int margin : 10

    modal: true
    focus: true
    width: 320
    height: 200

    x: 10
    y: 10

    background: Rectangle {
        color: Qt.rgba(1,1,1,0.8)
    }

    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    function openAt(xNew, yNew, d: shipRadarInfo) {
        x = xNew + margin
        y = yNew + margin
        shipData = d

        console.log(xNew + " " + yNew)

        open()
    }

    function openFor(target: Item, d: shipRadarInfo) {
        x = Qt.binding(() => target.x + target.width)
        y = Qt.binding(() => target.y + target.height)

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
