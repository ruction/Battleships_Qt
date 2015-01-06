import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


BaseScreen {
    id: gameScreenMulti

    signal finishedGame
    signal quitGame

    NavigationBar {
        id: navigationBar

        title: "GAME - MULTI"
    }

    ColumnLayout {
        anchors.centerIn: parent

        EnemyBoardView {
            id: board_enemy

            scale: 0.93
            board: battleships.enemyBoard
        }

        MyBoardViewMulti {
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


