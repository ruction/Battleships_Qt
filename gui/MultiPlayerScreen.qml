import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


ColumnLayout {
    id: multiPlayer
    anchors.centerIn: parent

    signal next
    signal cancel
    signal server_signal
    signal client_signal

    property string playerName: playerName_input.text
    property int boardWidth: boardWidth_slider.value
    property int boardHeight: boardHeight_slider.value

    RowLayout {
        anchors {
            horizontalCenter: parent.horizontalCenter
        }

        RowLayout {
            ExclusiveGroup {
                id: tabPositionGroup
            }
            RadioButton {
                text: "server"
                checked: true
                exclusiveGroup: tabPositionGroup
                onClicked: {
                    address_input.visible = false;
                    address_txt.visible = false;
                    multiPlayer.server_signal();
                }
            }
            RadioButton {
                text: "client"
                exclusiveGroup: tabPositionGroup
                onClicked: {
                    address_input.visible = true;
                    address_txt.visible = true;
                    multiPlayer.client_signal();
                }
            }
        }
    }
    Text {
        text: "Your IP: " + server.ip;

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
    }

    Text {
        text: "What is your name?"

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        visible: true
    }
    TextField {
        id: playerName_input
        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        visible: true

        placeholderText: "name"
    }
    Text {
        text: "Board width: " + boardWidth_slider.value
        anchors {
            horizontalCenter: multiPlayer.horizontalCenter
        }
    }
    Slider {
        id: boardWidth_slider

        anchors {
            horizontalCenter: multiPlayer.horizontalCenter
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
            horizontalCenter: multiPlayer.horizontalCenter
        }
    }
    Slider {
        id: boardHeight_slider

        anchors {
            horizontalCenter: multiPlayer.horizontalCenter
        }
        maximumValue: 10.0
        minimumValue: 7.0
        tickmarksEnabled: true
        updateValueWhileDragging: true
        stepSize: 1.0
    }
    Text {
        id: address_txt

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        text: "address:"
        visible: false
    }
    TextField {
        id: address_input

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        placeholderText: "127.0.0.1"
        visible: false
    }
    Text {
        id: port_txt

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        text: "port:"
        visible: true
    }
    TextField {
        id: port_input

        anchors {
            horizontalCenter: parent.horizontalCenter
        }
        placeholderText: "8888"
        visible: true
    }

    RowLayout {
        anchors {
            horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: start_btn
            text: "start game"
            onClicked: multiPlayer.next()
        }
        Button {
            id: cancel_btn
            text: "cancel"

            onClicked: multiPlayer.cancel()
        }
    }
}
