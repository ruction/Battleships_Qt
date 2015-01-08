import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: waitForPlayer

    signal cancel
    signal accept

    NavigationBar {
        id: navigationBar

        title: "SERVER - WAIT FOR PLAYER"
    }

    ColumnLayout {
        anchors {
            top: navigationBar.bottom
            bottom: waitForPlayer.bottom
            horizontalCenter: waitForPlayer.horizontalCenter
        }

        Text {
            text: "SERVER: " + battleships.playerName
        }
        Text {
            text: "PORT: "
        }
        Text {
            text: "MESSAGE: "
        }
        Button {
            id: cancel_btn
            text: "cancel"

            onClicked: waitForPlayer.cancel()
        }
        Button {
            id: accept_btn
            text: "accept"

            onClicked: waitForPlayer.accept()
        }
    }
}
