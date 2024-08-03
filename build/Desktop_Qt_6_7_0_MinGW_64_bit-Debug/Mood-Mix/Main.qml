import QtQuick
import QtQuick.Controls.Material
import "./Components"

Window {
    minimumWidth: 1280
    minimumHeight: 850
    maximumWidth: 1280
    maximumHeight: 850
    visible: true
    color: "#313338"
    title: qsTr("Mood Mix")

    Material.theme: Material.Dark
    Material.accent: Material.Blue

    MouseArea {
        id: clickArea
        anchors.fill: parent
        onClicked: search.searching = false
    }

    Text {
        id: title
        text: "Mood Mix"
        font.pointSize: 50
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 30
    }

    Search {
        id: search
        width: 500
        height: parent.height
        anchors.centerIn: parent
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
    }

    TimeCompare {
        anchors {
            top: parent.top
            topMargin: 150
            left: parent.left
            leftMargin: 55
        }
        width: 300
        height: 225
    }
}
