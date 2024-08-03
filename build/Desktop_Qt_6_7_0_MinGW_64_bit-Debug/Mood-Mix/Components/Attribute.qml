import QtQuick
import QtQuick.Controls.Material

Item {
    Text {
        text: "Select Attribute"
        font.pointSize: 20
        font.bold: true
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 35
    }

    ComboBox {
        width: 200
        height: 65
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 70
        editable: false
        model: ["danceability", "energy", "loudness", "valence", "tempo"]
        font.pointSize: 15
    }
}
