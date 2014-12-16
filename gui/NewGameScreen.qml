import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal cancel

    NavigationBar {
        id: navigationBar

        title: "NEW GAME"
    }

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
}
