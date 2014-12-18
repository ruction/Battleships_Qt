import QtQuick 2.0
import QtQuick.Controls 1.2
import Battleships 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: app

    width: 500
    height: 600
    visible: true

    Battleships {
        id: battleships
//        playerName: "testhans"
//        shotsFired:
//        availableShips:
    }

    Ship {
        id: ship
//        length:
//        name:
//        positions:
    }

//    Board {
//        id: board
////        width:
////        height:
////        shipPositions:
////        shots:
//    }


    Item {
        id: gameLogic
        state: "SplashScreen"
        states: [
            State {
                name: "SplashScreen"
                PropertyChanges {
                    target: splashScreen
                    visible: true
                }
            },
            State {
                name: "HomeScreen"
                PropertyChanges {
                    target: homeScreen
                    visible: true
                }
            },
            State {
                name: "SettingsScreen"
                PropertyChanges {
                    target: settingsScreen
                    visible: true
                }
            },
            State {
                name: "NewGameScreen"
                PropertyChanges {
                    target: newGameScreen
                    visible: true
                }
            },
            State {
                name: "PlaceShipsScreen"
                PropertyChanges {
                    target: placeShipsScreen
                    visible: true
                }
            },
            State {
                name: "GameScreen"
                PropertyChanges {
                    target: gameScreen
                    visible: true
                }
            }
        ]

        transitions: [
            GameTransition {
                id: gameTransition

                oldItem: splashScreen
                newItem: homeScreen

                from: "SplashScreen"
                to: "HomeScreen"

                NumberAnimation {
                    target: gameTransition.newItem
                    properties: "x"
                    from: app.width
                    to: 0
                    easing.type: Easing.Linear
                    duration: 400
                }
            },
            GameTransition {
                id: gameTransition2

                oldItem: homeScreen
                newItem: settingsScreen

                from: "HomeScreen"
                to: "SettingsScreen"

                NumberAnimation {
                    target: gameTransition2.newItem
                    properties: "x"
                    from: app.width
                    to: 0
                    easing.type: Easing.Linear
                    duration: 400
                }
            },
            GameTransition {
                id: gameTransition3

                oldItem: settingsScreen
                newItem: homeScreen

                from: "SettingsScreen"
                to: "HomeScreen"

                NumberAnimation {
                    target: gameTransition3.oldItem
                    properties: "x"
                    from: 0
                    to: app.width
                    easing.type: Easing.Linear
                    duration: 400
                }
            },
            GameTransition {
                id: gameTransition4

                oldItem: newGameScreen
                newItem: homeScreen

                from: "NewGameScreen"
                to: "HomeScreen"

                NumberAnimation {
                    target: gameTransition4.oldItem
                    properties: "x"
                    from: 0
                    to: app.width
                    easing.type: Easing.Linear
                    duration: 400
                }
            },
            GameTransition {
                id: gameTransition5

                oldItem: homeScreen
                newItem: newGameScreen

                from: "HomeScreen"
                to: "NewGameScreen"

                NumberAnimation {
                    target: gameTransition5.newItem
                    properties: "x"
                    from: app.width
                    to: 0
                    easing.type: Easing.Linear
                    duration: 400
                }
            },
            GameTransition {
                id: gameTransition6

                oldItem: newGameScreen
                newItem: placeShipsScreen

                from: "NewGameScreen"
                to: "PlaceShipsScreen"

                NumberAnimation {
                    target: gameTransition6.newItem
                    properties: "x"
                    from: app.width
                    to: 0
                    easing.type: Easing.Linear
                    duration: 400
                }
            }
        ]
    }

    SplashScreen {
        id: splashScreen
        width: app.width
        height: app.height

        onSkip: gameLogic.state = "HomeScreen"
    }

    HomeScreen {
        id: homeScreen
        width: app.width
        height: app.height

        onSettings: gameLogic.state = "SettingsScreen"
        onNew_game: gameLogic.state = "NewGameScreen"
    }

    SettingsScreen {
        id: settingsScreen
        width: app.width
        height: app.height

        onCancel: gameLogic.state = "HomeScreen"
    }

    NewGameScreen {
        id: newGameScreen
        width: app.width
        height: app.height

        onCancel: gameLogic.state = "HomeScreen"
        onNext: {
            if (mode == "single") {
                battleships.playerName = single.playerName
                battleships.board.width = single.boardWidth
                battleships.board.height = single.boardHeight
            } else {
//                coming soon...
            }

            gameLogic.state = "PlaceShipsScreen"

        }
    }

    PlaceShipsScreen {
        id: placeShipsScreen
        width: app.width
        height: app.height

        onStartGame: {
            gameLogic.state = "GameScreen"
        }
    }

    GameScreen {
        id: gameScreen
        width: app.width
        height: app.height

        MessageDialog {
            id: destroyed_dialog
            title: "YOU WON!"
            text: "YOU WON!"
            visible: false
            onAccepted: {
                gameLogic.state = "HomeScreen"
                battleships.board.reset();
            }
        }

        onFinishedGame: {
            destroyed_dialog.visible = true;
        }
    }
}
