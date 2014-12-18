import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


BaseScreen {
    id: gameScreen

    NavigationBar {
        id: navigationBar

        title: "GAME"
    }

    ColumnLayout {
        anchors.centerIn: parent

//        EnemyBoardView {
//            id: board_enemy

//            scale: 0.93
//            board: battleships.enemyBoard
//        }

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
        Text {
            text: battleships.playerName
        }
        Button {
            text: "QUIT GAME"
        }
    }
}


