import QtQuick
import QtQuick.Controls.Material

Item {
    property alias selectedAttribute: comboBox.currentText
    property string newAttribute: ""
    signal attributeChanged(string newAttribute)

    Text {
        text: "Sort By"
        font.pointSize: 20
        font.bold: true
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 35
    }

    ComboBox {
        id: comboBox
        width: 200
        height: 65
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 70
        editable: false
        model: ["danceability", "energy", "loudness", "valence", "tempo"]
        font.pointSize: 15

        onCurrentIndexChanged: {
            var selectedAttribute = comboBox.model[comboBox.currentIndex]
            newAttribute = selectedAttribute
            attributeChanged(newAttribute)
        }
    }
}
