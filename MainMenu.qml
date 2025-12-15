import QtQuick
import QtQuick.Controls

//F7A8B8
Item {
    visible: true

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"
    }

    Text {
        id: title

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 80
        }

        text: "Blackjack"

        color: "white"

        font {
            pixelSize: 30
            bold: true
        }
    }

    Button {
        id: playButton

        background: Rectangle {
            anchors.fill: parent
            color: playButton.down ? Qt.darker("#5BCEFA", 1.2) : "#5BCEFA"
            radius: 20
        }

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: title.bottom
            topMargin: 50
        }

        width: 150
        height: 65

        Text {
            anchors {
                centerIn: parent
            }

            text: "PLAY"

            font {
                pixelSize: 25
                bold: true
            }
        }

        onClicked: stack.push("Blackjack.qml")
    }

    Image {
        source: "qrc:/assets/cards/hearts_8.png"
        anchors {
            top: playButton.bottom
            topMargin: 30
            horizontalCenter: parent.horizontalCenter
        }

        fillMode: Image.PreserveAspectFit

        width: 100
    }
}
