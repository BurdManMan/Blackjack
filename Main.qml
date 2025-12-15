import QtQuick
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 1920
    height: 1080

    StackView {
        id: stack
        anchors.fill: parent
        initialItem: "MainMenu.qml"
    }
}
