import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtPositioning
import QtLocation

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("VDT2026")

    menuBar: AppMenuBar {}

    header: ToolBar {
        RowLayout {
            Label {
                text: "Hello"
            }
        }
    }


    footer: ToolBar {

    }

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75) // Oslo
        zoomLevel: 14
        property geoCoordinate startCentroid
    }
}
