import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


ColumnLayout {
    id: singlePlayer
    anchors.centerIn: parent

    signal startGame
    signal cancel

    property string playerName: playerName_input.text
    property int boardWidth: boardWidth_slider.value
    property int boardHeight: boardHeight_slider.value
    property bool autoPlaceShips

    TextField {
        id: playerName_input
        placeholderText: "testhans"
    }
    Text {
        text: boardWidth_slider.value
    }
    Slider {
        id: boardWidth_slider

        maximumValue: 10.0
        minimumValue: 5.0
        tickmarksEnabled: true
        updateValueWhileDragging: true
        stepSize: 1.0
    }
    Text {
        text: boardHeight_slider.value
    }
    Slider {
        id: boardHeight_slider

        maximumValue: 10.0
        minimumValue: 5.0
        tickmarksEnabled: true
        updateValueWhileDragging: true
        stepSize: 1.0
    }
    GroupBox {
        id: autoPlaceShips_input
        title: "Auto place ships"

        RowLayout {
            ExclusiveGroup { id: autoPlaceShipsGroup }
            RadioButton {
                text: "Yes"
                checked: true
                exclusiveGroup: autoPlaceShipsGroup
                onClicked: {
                    autoPlaceShips = true;
                }
            }
            RadioButton {
                text: "No"
                exclusiveGroup: autoPlaceShipsGroup
                onClicked: {
                    autoPlaceShips = false;
                }
            }
        }
        Layout.columnSpan: 2
    }

    Button {
        id: start_btn
        text: "start game"

        onClicked: {
            singlePlayer.startGame()
        }
    }
    Button {
        id: cancel_btn
        text: "cancel"

        onClicked: singlePlayer.cancel()
    }
}
