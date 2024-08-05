import QtQuick
import QtQuick.Controls.Material

Item {
    Rectangle {
        anchors.fill: parent
        color: "#2b2d31"
        radius: 10

        Text {
            width: 300
            text: "Instructions"
            font.pointSize: 20
            font.underline: true
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            anchors.top: parent.top
            anchors.topMargin: 3
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            width: 330
            text: "Enter a song that you want to find other songs similar to. Then select the mood (song attribute) that you want to sort by."
            font.pointSize: 15
            color: "white"
            wrapMode: Text.Wrap
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Text {
            width: 330
            text: "<b>Note:</b> While the data set has 104k songs you likely won't find very many new songs in it."
            font.pointSize: 15
            color: "white"
            wrapMode: Text.Wrap
            anchors.top: parent.top
            anchors.topMargin: 160
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
