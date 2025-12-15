import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtMultimedia
import proj.myproj.blackjackcontroller 1.0

//"#F7A8B8" pink
Item {
    id: root
    visible: true

    property bool gameOver: BlackjackController.playerLose
                        || BlackjackController.playerWin
                        || BlackjackController.draw

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"
    }

    Row {
        id: dealerHand
        spacing: 10
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: 10
        }

        Repeater {
            model: BlackjackController.dealerHand
            delegate: Image {
                width: 100
                fillMode: Image.PreserveAspectFit
                source: model.source
            }
        }
    }

    Text {
        text: "Dealer"
        color: "white"
        anchors {
            horizontalCenter: dealerHand.horizontalCenter
            top: dealerHand.bottom
            topMargin: 10
        }
    }

    Row {
        id: playerHand
        spacing: 10
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 10
        }

        Repeater {
            model: BlackjackController.playerHand
            delegate: Image {
                width: 100
                fillMode: Image.PreserveAspectFit
                source: model.source
            }
        }
    }

    Text {
        text: "Player"
        color: "white"
        anchors {
            horizontalCenter: playerHand.horizontalCenter
            bottom: playerHand.top
            bottomMargin: 10
        }
    }


    Button {
        id: hitButton

        background: Rectangle {
            anchors.fill: parent
            color: hitButton.down ? Qt.darker("#5BCEFA", 1.2) : "#5BCEFA"
            radius: 20
        }

        anchors {
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }

        width: 150
        height: 65

        Text {
            anchors {
                centerIn: parent
            }

            text: "HIT"

            font {
                pixelSize: 25
                bold: true
            }
        }

        onClicked: BlackjackController.hit()
    }

    Button {
        id: standButton

        background: Rectangle {
            anchors.fill: parent
            color: standButton.down ? Qt.darker("#5BCEFA", 1.2) : "#5BCEFA"
            radius: 20
        }

        anchors {
            horizontalCenter: hitButton.horizontalCenter
            bottom: hitButton.top
            bottomMargin: 10
        }

        width: 150
        height: 65

        Text {
            anchors {
                centerIn: parent
            }

            text: "STAND"

            font {
                pixelSize: 25
                bold: true
            }
        }

        onClicked: BlackjackController.stand()
    }

    Text {
        id: playerTotal
        color: "white"
        anchors {
            left: playerHand.right
            leftMargin: 10
            verticalCenter: playerHand.verticalCenter
        }
        text: BlackjackController.playerTotal
    }

    Text {
        id: dealerTotal
        color: "white"
        visible: BlackjackController.revealedDealerHand
        anchors {
            left: dealerHand.right
            leftMargin: 10
            verticalCenter: dealerHand.verticalCenter
        }
        text: BlackjackController.dealerTotal
    }

    MediaPlayer {
        id: gameOverSound
        source: BlackjackController.playerLose ? "qrc:/assets/sounds/wasted.mp3"
              : BlackjackController.playerWin ? "qrc:/assets/sounds/yay.mp3"
              : "qrc:/assets/sounds/boom.mp3"
        audioOutput: AudioOutput {}
    }

    Rectangle {
        id: gameOverLabel
        visible: gameOver
        anchors.fill: parent
        color: "transparent"

        Rectangle {
            color: "#1e1e1e"
            anchors.fill: parent
            opacity: 0.75
        }

        MouseArea {
            anchors.fill: parent
            enabled: gameOverLabel.visible
            onClicked: {} // swallow clicks
        }

        Text {
            id: gameOverText

            property int animFontSize: 40

            text: BlackjackController.playerLose ? "YOU LOSE"
                : BlackjackController.playerWin ? "YOU WIN!"
                : "DRAW"

            color: BlackjackController.playerLose ? "red"
                 : BlackjackController.playerWin ? "blue"
                 : "yellow"

            anchors {
                centerIn: parent
            }

            font {
                pixelSize: animFontSize
                bold: true
            }
        }

        Button {
            id: returnToMainMenuButton

            background: Rectangle {
                anchors.fill: parent
                color: returnToMainMenuButton.down ? Qt.darker("#F7A8B8", 1.2) : "#F7A8B8"
                radius: 20
            }

            anchors {
                horizontalCenter: parent.horizontalCenter
                bottom: parent.bottom
                bottomMargin: parent.height * 0.25
            }

            width: 175
            height: 75

            Text {
                anchors {
                    centerIn: parent
                }

                text: "MAIN MENU"

                font {
                    pixelSize: 25
                    bold: true
                }
            }

            onClicked: {
                BlackjackController.reset()
                stack.push("MainMenu.qml")
            }
        }

        onVisibleChanged: {
            if(gameOver) {
                gameOverSound.stop()
                gameOverSound.play()
                gameOverText.animFontSize = 40

                growAnim.start()
            }
        }

        SequentialAnimation {
            id: growAnim
            NumberAnimation {
                target: gameOverText
                property: "animFontSize"
                from: 40
                to: 200
                duration: 3000
                easing.type: Easing.OutCubic
            }
        }
    }
}
