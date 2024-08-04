import QtQuick
import QtQuick.Controls.Material

Item {
    property alias selectedAttribute: comboBox.currentText
    property string newAttribute: ""
    signal attributeChanged(string newAttribute)

    Text {
        id: sortTitle
        text: "Sort By"
        font.pointSize: 20
        font.bold: true
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 108
    }

    ComboBox {
        id: comboBox
        width: 200
        height: 65
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: sortTitle.bottom
        editable: false
        model: ["danceability", "energy", "loudness", "valence", "tempo"]
        font.pointSize: 15

        onCurrentIndexChanged: {
            var selectedAttribute = comboBox.model[comboBox.currentIndex]
            newAttribute = selectedAttribute
            attributeChanged(newAttribute)
        }
    }

    Rectangle {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: comboBox.bottom
            topMargin: 5
        }
        width: 380
        height: 630
        color: "#2b2d31"
        radius: 10

        Column {
            anchors {
                left: parent.left
                leftMargin: 15
                top: parent.top
                topMargin: 5
            }
            spacing: 5
            Text {
                width: 300
                text: "Attribute Definitions"
                font.pointSize: 20
                font.underline: true
                color: "white"
                horizontalAlignment: Text.AlignHCenter
            }
            Text {
                width: 355
                text: "<b>danceability:</b> Danceability describes how suitable a track is for dancing based on a combination of musical elements including tempo, rhythm stability, beat strength, and overall regularity."
                font.pointSize: 13.5
                color: "white"
                wrapMode: Text.Wrap
            }
            Text {
                width: 355
                text: "<b>energy:</b> Energy represents a perceptual measure of intensity and activity. Typically, energetic tracks feel fast, loud, and noisy. For example, death metal has high energy, while a Bach prelude scores low on the scale."
                font.pointSize: 13.5
                color: "white"
                wrapMode: Text.Wrap
            }
            Text {
                width: 355
                text: "<b>loudness:</b> The overall loudness of a track in decibels (dB)."
                font.pointSize: 13.5
                color: "white"
                wrapMode: Text.Wrap
            }
            Text {
                width: 355
                text: "<b>valence:</b> Valence describes the musical positiveness conveyed by a track. Tracks with high valence sound more positive (e.g. happy, cheerful, euphoric), while tracks with low valence sound more negative (e.g. sad, depressed, angry)."
                font.pointSize: 13.5
                color: "white"
                wrapMode: Text.Wrap
            }
            Text {
                width: 355
                text: "<b>tempo:</b> The overall estimated tempo of a track in beats per minute (BPM). In musical terminology, tempo is the speed or pace of a given piece and derives directly from the average beat duration."
                font.pointSize: 13.5
                color: "white"
                wrapMode: Text.Wrap
            }
        }
    }
}
