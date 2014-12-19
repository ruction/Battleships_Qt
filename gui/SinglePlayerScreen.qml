import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


ColumnLayout {
    id: singlePlayer

    signal next
    signal cancel

    property string playerName: playerName_input.text
    property int boardWidth: boardWidth_slider.value
    property int boardHeight: boardHeight_slider.value

    Text {
        text: "What is your name?"
        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }
    }
    TextField {
        id: playerName_input
        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }

        placeholderText: "name"
    }
    Text {
        text: "Board width: " + boardWidth_slider.value
        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }
    }
    Slider {
        id: boardWidth_slider

        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }

        maximumValue: 10.0
        minimumValue: 7.0
        tickmarksEnabled: true
        updateValueWhileDragging: true
        stepSize: 1.0
    }
    Text {
        text: "Board height: " + boardHeight_slider.value
        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }
    }
    Slider {
        id: boardHeight_slider

        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }
        maximumValue: 10.0
        minimumValue: 7.0
        tickmarksEnabled: true
        updateValueWhileDragging: true
        stepSize: 1.0
    }
    RowLayout {
        anchors {
            horizontalCenter: singlePlayer.horizontalCenter
        }
        Button {
            id: start_btn
            text: "start game"

            onClicked: {
                singlePlayer.next()
            }
        }
        Button {
            id: cancel_btn
            text: "cancel"

            onClicked: singlePlayer.cancel()
        }
    }
}
