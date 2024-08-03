import QtQuick
import QtQuick.Controls.Material

Item {
    property alias searching: searchField.focus

    TextField {
        id: searchField
        width: 450
        placeholderText: "Search Song"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 150
        font.pointSize: 20
        focus: false
        onTextChanged: {
            listView.model = songManager.searchSongs(text)
        }
        onFocusChanged: {
            if (focus) {
                listView.model = songManager.searchSongs(text)
            } else {
                listView.model = songManager.searchSongs("")
            }
        }
    }

    Button {
        id: searchButton
        width: 200
        anchors {
            horizontalCenter: searchField.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 25
        }
        text: qsTr("Search")
        font.pointSize: 15
        font.bold: true
        Material.background: Material.LightBlue
        Material.foreground: "#2b2930"
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
                    width: parent.width - 15
                    elide: Text.ElideRight
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: parent.top
                    anchors.topMargin: -4
                    text: modelData.name
                    font.pointSize: 22.5
                    color: "#EEEEEE"
                }

                Text {
                    width: parent.width - 15
                    elide: Text.ElideRight
                    anchors.left: parent.left
                    anchors.leftMargin: 15
                    anchors.top: parent.top
                    anchors.topMargin: 28
                    text: modelData.artist
                    font.pointSize: 14
                    color: "#EEEEEE"
                }
            }
        }

        Rectangle {
            id: noResults
            anchors.horizontalCenter: parent.horizontalCenter
            width: listView.width
            height: 56
            color: "#313338"
            border.color: "#90CAF9"
            border.width: 2
            radius: 5
            visible: listView.count === 0 && searchField.text.length > 0
                     && searching === true

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
