import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCore

import VDT2026

Dialog {
    title: qsTr("Preferences")
    standardButtons: Dialog.Save | Dialog.Cancel
    modal: true
    popupType: Popup.Window

    width: 400

    anchors.centerIn: Overlay.overlay

    signal preferencesChanged()

    contentItem: GridLayout {
        columns: 2
        columnSpacing: 5

        Label {
            Layout.columnSpan: 2
            text: "Postgres Database"
            font.bold: true
        }

        Label { text: "Host" }
        TextField {
            id: inputDbHost
            Layout.fillWidth: true

            text: settings.dbHost
        }

        Label { text: "Port" }
        TextField {
            id: inputDbPort
            Layout.fillWidth: true
            validator: IntValidator { bottom: 0; top: 65535 }

            text: settings.dbPort
        }

        Label { text: "Database" }
        TextField {
            id: inputDbName
            Layout.fillWidth: true

            text: settings.dbName
        }

        Label { text: "Username" }
        TextField {
            id: inputDbUsername
            Layout.fillWidth: true

            text: settings.dbUsername
        }

        Label { text: "Password" }
        TextField {
            id: inputDbPassword
            Layout.fillWidth: true
            echoMode: TextField.Password
            passwordMaskDelay: 1000

            text: settings.dbPassword
        }

        Label {
            Layout.columnSpan: 2
            text: "Socket"
            font.bold: true
        }

        Label { text: "Port" }
        TextField {
            id: inputSocketPort
            Layout.fillWidth: true
            validator: IntValidator { bottom: 0; top: 65535 }

            text: settings.socketPort
        }

        Label {
            Layout.columnSpan: 2
            text: "API keys"
            font.bold: true
        }

        Label { text: "Thunderforest" }
        TextField {
            id: inputKeyThunderforest
            Layout.fillWidth: true
            echoMode: TextField.Password
            passwordMaskDelay: 1000

            text: settings.keyThunderforest
        }
    }

    Settings {
        id: settings
        property string dbHost
        property int dbPort
        property string dbName
        property string dbUsername
        property string dbPassword

        property int socketPort

        property string keyThunderforest
    }

    onAccepted: {
        settings.dbHost = inputDbHost.text
        settings.dbPort = inputDbPort.text
        settings.dbName = inputDbName.text
        settings.dbUsername = inputDbUsername.text
        settings.dbPassword = inputDbPassword.text

        settings.socketPort = inputSocketPort.text

        settings.keyThunderforest = inputKeyThunderforest.text

        DialogProvider.requestDialog(AppDialog.Level.Notice, "Please restart the app for new settings to take effect")

        preferencesChanged()
    }

    onRejected: {
        this.close()
    }
}
