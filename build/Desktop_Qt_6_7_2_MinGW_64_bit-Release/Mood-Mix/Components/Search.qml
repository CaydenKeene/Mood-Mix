import QtQuick
import QtQuick.Controls.Material

Item {
    property alias searching: searchField.focus
    property string selectedSongName: ""
    property string selectedSongArtist: ""
    property string selectedSongTrackID: ""
    property bool songSelected: false
    property string selectedAttribute: ""
    signal songSelectionChanged(bool songSelected)

    TextField {
        id: searchField
        width: 450
        placeholderText: "Search Song Name"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 150
        font.pointSize: 20
        focus: false
        visible: !songSelected
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
        Keys.onReleased: function (event) {
            if (event.key === Qt.Key_Escape) {
                searchField.focus = false
            }
        }
        Keys.onPressed: function (event) {
            if (event.key === Qt.Key_Return) {
                searchButton.clicked()
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
        visible: !songSelected
        onClicked: {
            if (songManager.searchSongs(searchField.text).length > 0) {
                var item = songManager.searchSongs(searchField.text)[0]
                selectedSongName = item.name
                selectedSongArtist = item.artist
                selectedSongTrackID = item.trackID
                songSelected = true
                resultList.model = songManager.mergeSort(selectedSongTrackID,
                                                         selectedAttribute)
                songManager.shellSort(selectedSongTrackID, selectedAttribute)
                songSelectionChanged(songSelected)
            }
        }
    }

    ListView {
        id: listView
        visible: !songSelected
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
                    onClicked: {
                        selectedSongName = modelData.name
                        selectedSongArtist = modelData.artist
                        selectedSongTrackID = modelData.trackID
                        songSelected = true
                        resultList.model = songManager.mergeSort(
                                    selectedSongTrackID, selectedAttribute)
                        songManager.shellSort(selectedSongTrackID,
                                              selectedAttribute)
                        songSelectionChanged(songSelected)
                    }
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

    Column {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 140
        }
        visible: songSelected

        Text {
            width: 450
            elide: Text.ElideRight
            text: "Songs similar to <b>" + selectedSongName + "</b>"
            font.pointSize: 20
            color: "white"
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            width: 450
            elide: Text.ElideRight
            text: "by <b>" + selectedSongArtist + "</b>"
            font.pointSize: 20
            color: "white"
            horizontalAlignment: Text.AlignHCenter
        }
    }
    ListView {
        id: resultList
        visible: songSelected
        width: searchField.width
        height: 542
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 230
        }
        spacing: -2
        interactive: true
        snapMode: ListView.SnapToItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        boundsBehavior: Flickable.StopAtBounds
        clip: true

        delegate: Item {
            width: listView.width
            height: 56

            Rectangle {
                width: parent.width
                height: parent.height
                color: mouseAreaResult.containsMouse ? "#55834f" : "#313338"
                border.color: "#90CAF9"
                border.width: 2
                radius: 5

                MouseArea {
                    id: mouseAreaResult
                    anchors.fill: parent
                    hoverEnabled: true
                    onClicked: {
                        songManager.spotify(modelData.trackID)
                    }
                }

                Image {
                    anchors {
                        left: parent.left
                        leftMargin: 10
                        top: parent.top
                        topMargin: 15
                    }
                    width: 25
                    height: 25
                    source: "../Icons/spotify.svg"
                    //fillMode: Image.PreserveAspectFit
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
                    anchors.leftMargin: 40
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
                    anchors.leftMargin: 40
                    anchors.top: parent.top
                    anchors.topMargin: 28
                    text: modelData.artist
                    font.pointSize: 14
                    color: "#EEEEEE"
                }
            }
        }
    }
    Button {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: resultList.bottom
            topMargin: 10
        }
        width: 150
        visible: songSelected
        text: "Back"
        font.pointSize: 15
        font.bold: true
        Material.background: Material.LightBlue
        Material.foreground: "#2b2930"
        onClicked: {
            songSelected = false
            searchField.text = ""
            searchField.focus = true
            songSelectionChanged(songSelected)
        }
    }
}
