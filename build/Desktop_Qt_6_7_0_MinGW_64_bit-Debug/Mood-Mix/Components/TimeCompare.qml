import QtQuick
import QtQuick.Controls.Material

Item {
    Rectangle {
        anchors.fill: parent
        color: "#2b2d31"
        radius: 10

        Text {
            id: timeTitle
            text: "Time Taken By Sorting Algorithms"
            font.pointSize: 20
            color: "white"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 5
            width: parent.width
            wrapMode: Text.Wrap
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            id: seperator
            anchors {
                left: parent.left
                right: parent.right
                top: timeTitle.bottom
                topMargin: 8
            }
            height: 2
            color: "white"
        }

        Text {
            id: mergeSort
            text: "Merge Sort: "
            font.pointSize: 20
            color: "white"
            anchors {
                left: parent.left
                leftMargin: 15
                top: seperator.bottom
                topMargin: 20
            }
        }

        Text {
            id: shellSort
            text: "Shell Sort: "
            font.pointSize: 20
            color: "white"
            anchors {
                left: parent.left
                leftMargin: 35
                top: mergeSort.bottom
                topMargin: 20
            }
        }
    }
}
