import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


BaseScreen {
    id: gameScreenSingle

    signal finishedGame
    signal quitGame

    NavigationBar {
        id: navigationBar

        title: "GAME - SINGLE"
    }

    ColumnLayout {
        anchors.centerIn: parent

        MyBoardView {
            id: board_my

            board: battleships.board

            transform: Rotation {
                origin.x: 100
                origin.y: 100
                axis {
                    x: 1
                    y: 0
                    z: 0
                }
                angle: 50
            }
        }
        Button {
            text: "QUIT GAME"
            onClicked: quitGame()
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}


