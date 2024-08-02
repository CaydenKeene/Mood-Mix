import QtQuick
import QtQuick.Controls.Material
import "./Components"

Window {
    minimumWidth: 1280
    minimumHeight: 800
    maximumWidth: 1280
    maximumHeight: 800
    visible: true
    color: "#313338"
    title: qsTr("Mood Mix")

    Material.theme: Material.Dark
    Material.accent: Material.Blue

    Text {
        id: title
        text: "Mood Mix"
        font.pointSize: 50
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 35
    }

    Search {
        width: 500
        height: parent.height
        anchors.centerIn: parent
        Rectangle {
            anchors.fill: parent
            visible: false
        }
    }

    Attribute {
        anchors {
            top: parent.top
            topMargin: 75
            right: parent.right
            rightMargin: 60
        }
        width: 300
        height: 300
        Rectangle {
            anchors.fill: parent
            visible: false
        }
    }
}
