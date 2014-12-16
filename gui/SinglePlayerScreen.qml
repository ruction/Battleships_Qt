import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    anchors.centerIn: parent

    TextField {
        id: playerName_input
        placeholderText: "testhans"
    }
    TextField {
        id: boardWidth_input
        placeholderText: "10"
    }
    TextField {
        id: boardHeight_input
        placeholderText: "10"
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
    }
    Button {
        id: cancel_btn
        text: "cancel"

        onClicked: root.cancel();
    }
}
