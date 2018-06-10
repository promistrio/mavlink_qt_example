import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtLocation 5.5
import QtPositioning 5.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    /*Label{
        text: "pitch: " + mavModel.pitch + " roll: " + mavModel.roll
        anchors.centerIn: parent
    }*/

    Rectangle{

        id: horizon

        width: parent.width * 4
        height: parent.height * 4

        x : 0 + parent.width / 2 - width / 2    // по ширине
        y : 0 + (parent.height / 2 - height / 2) + mavModel.pitch * (parent.height / 90)  // по высоте

        Rectangle{
            id: sky
            color: "blue"
            width: parent.width
            height: parent.height / 2
            anchors.top: parent.top
        }
        Rectangle{
            id: ground
            color: "#663500"
            width: parent.width
            height: parent.height / 2
            anchors.bottom: parent.bottom
        }
        rotation: mavModel.roll // крен

    }

    /*Plugin {
        id: osmPlugin
        name: "osm"

    }

    Map{
        anchors.fill: parent
        plugin: osmPlugin


        MapQuickItem {
            id: marker
            coordinate {
                    latitude: mavModel.lat
                    longitude: mavModel.lon
                }
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height

            sourceItem: Image {
                id: image
                source: "qrc:/img/pointer.png"
            }
        }
    }*/

}
