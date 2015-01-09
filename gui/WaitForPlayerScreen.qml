import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: waitForPlayer

    signal accept

    NavigationBar {
        id: navigationBar

        title: "SERVER - WAIT FOR PLAYER"
    }

    Connections {
        target: newGameScreen.network

        onStartGame: {
            accept_btn.enabled = true
        }
    }

    ColumnLayout {
        anchors {
            top: navigationBar.bottom
            bottom: waitForPlayer.bottom
            horizontalCenter: waitForPlayer.horizontalCenter
        }

        Text {
            text: "WAIT FOR PLAYER"
        }

        Button {
            id: accept_btn

            enabled: false

            text: "accept"

            onClicked: {
                waitForPlayer.accept()
                accept_btn.enabled = false;
            }
        }
    }
}
