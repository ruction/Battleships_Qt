import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: connectToServer

    signal cancel
    signal accept

    NavigationBar {
        id: navigationBar

        title: "CLIENT - CONNECT TO SERVER"
    }

    ColumnLayout {
        anchors {
            top: navigationBar.bottom
            bottom: connectToServer.bottom
            horizontalCenter: connectToServer.horizontalCenter
        }

        Text {
            text: "CLIENT: " + battleships.playerName
        }
        Text {
            text: "PORT: "
        }

        Button {
            id: cancel_btn
            text: "cancel"

            onClicked: connectToServer.cancel()
        }

        Button {
            id: accept_btn
            text: "accept"

            onClicked: connectToServer.accept()
        }

    }
}
