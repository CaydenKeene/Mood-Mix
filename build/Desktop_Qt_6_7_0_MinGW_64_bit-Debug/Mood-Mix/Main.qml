import QtQuick
//import QtQuick.Controls
import QtQuick.Controls.Material

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
        text: "Mood Mix"
        font.pointSize: 50
        color: "white"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 55
    }

    TextField {
        id: searchField
        width: 450
        placeholderText: "Search song"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 150
        font.pointSize: 20
        onTextChanged: {
            listView.model = songManager.searchSongs(text)
        }
    }

    ListView {
        id: listView
        visible: true
        anchors.top: searchField.bottom
        anchors.topMargin: -2
        anchors.horizontalCenter: searchField.horizontalCenter
        width: searchField.width
        height: parent.height - searchField.height - 20
        spacing: -2
        interactive: false

        //model: ListModel {}

        delegate: Item {
            width: listView.width
            height: 56

            Rectangle {
                width: parent.width
                height: parent.height
                color: mouseArea.containsMouse ? "#455A64" : "#313338"
                border.color: "#90CAF9"
                border.width: 2
                radius: 5

                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                }

                Rectangle {
                    width: 2
                    height: 15
                    anchors.left: parent.left
                    anchors.bottom: parent.top
                    anchors.bottomMargin: -8
                    color: "#90CAF9"
                }
                Rectangle {
                    width: 2
                    height: 15
                    anchors.right: parent.right
                    anchors.bottom: parent.top
                    anchors.bottomMargin: -8
                    color: "#90CAF9"
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: 2
                    text: modelData.name
                    font.pointSize: 25
                    color: "#EEEEEE"
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.top: parent.top
                    anchors.topMargin: 30
                    text: modelData.artist
                    font.pointSize: 15
                    color: "#EEEEEE"
                }
            }
        }

        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: searchField.bottom
            width: listView.width
            height: 56
            color: "#313338"
            border.color: "#90CAF9"
            border.width: 2
            radius: 5
            visible: listView.count === 0 && searchField.text.length > 0

            Rectangle {
                width: 2
                height: 15
                anchors.left: parent.left
                anchors.bottom: parent.top
                anchors.bottomMargin: -8
                color: "#90CAF9"
            }
            Rectangle {
                width: 2
                height: 15
                anchors.right: parent.right
                anchors.bottom: parent.top
                anchors.bottomMargin: -8
                color: "#90CAF9"
            }

            Text {
                text: "No Results"
                color: "#ff4f4f"
                font.pointSize: 25
                font.weight: Font.DemiBold
                anchors.centerIn: parent
            }
        }

    }
}
