import QtQuick 2.0
import QtQuick.Controls 1.2
import Battleships 1.0
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id: app

    width: 600
    height: 900
    visible: true

    Battleships {
        id: battleships
    }

    Ship {
        id: ship
    }

    Server {
        id: server
        battleships: battleships
    }

    Client {
        id: client
        battleships: battleships
    }

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
                name: "GameScreenSingle"
                PropertyChanges {
                    target: gameScreenSingle
                    visible: true
                }
            },
            State {
                name: "GameScreenMulti"
                PropertyChanges {
                    target: gameScreenMulti
                    visible: true
                }
            },
            State {
                name: "WaitForPlayerScreen"
                PropertyChanges {
                    target: waitForPlayerScreen
                    visible: true
                }
            },
            State {
                name: "ConnectToServerScreen"
                PropertyChanges {
                    target: connectToServerScreen
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

    property string mode
    property string kind

    NewGameScreen {
        id: newGameScreen
        width: app.width
        height: app.height

        onCancel: gameLogic.state = "HomeScreen"
        onNext: {
            app.mode = mode;
            app.kind = kind;

            if (mode == "single") {
                battleships.playerName = single.playerName;
                battleships.board.width = single.boardWidth;
                battleships.board.height = single.boardHeight;

                gameLogic.state = "PlaceShipsScreen"
            } else {
                if (kind == "server") {
                    battleships.playerName = multi.playerName;
                    battleships.board.width = multi.boardWidth;
                    battleships.board.height = multi.boardHeight;
                    battleships.enemyBoard.width = multi.boardWidth;
                    battleships.enemyBoard.height = multi.boardHeight;

                    gameLogic.state = "PlaceShipsScreen";
                } else {
                    battleships.playerName = multi.playerName;
                    battleships.board.width = multi.boardWidth;
                    battleships.board.height = multi.boardHeight;
                    battleships.enemyBoard.width = multi.boardWidth;
                    battleships.enemyBoard.height = multi.boardHeight;

                    gameLogic.state = "PlaceShipsScreen"
                }
            }
        }
    }

    PlaceShipsScreen {
        id: placeShipsScreen
        width: app.width
        height: app.height

        onStartGame: {
            if (mode == "single") {
                gameLogic.state = "GameScreenSingle"
            } else {
                if (kind == "server") {
                    server.start(8888);
//                    gameLogic.state = "WaitForPlayerScreen"
                    gameLogic.state = "GameScreenMulti";
                } else if (kind == "client") {
                    client.start("141.82.163.215", 8888);
//                    gameLogic.state = "ConnectToServerScreen"
                    gameLogic.state = "GameScreenMulti";
                }
            }
        }
    }



    WaitForPlayerScreen {
        id: waitForPlayerScreen
        width: app.width
        height: app.height

        onCancel: gameLogic.state = "NewGameScreen"
    }

    ConnectToServerScreen {
        id: connectToServerScreen
        width: app.width
        height: app.height

        onCancel: gameLogic.state = "NewGameScreen"
    }

    MessageDialog {
        id: quitGame_dialog
        title: "Are you sure?"
        text: "Are you sure?"
        visible: false
        onAccepted: {
            battleships.board.reset();
            battleships.enemyBoard.reset();
            battleships.reset();
            gameLogic.state = "HomeScreen"
        }
    }

    GameScreenSingle {
        id: gameScreenSingle
        width: app.width
        height: app.height

        MessageDialog {
            id: won_dialog
            title: "YOU WON!"
            text: battleships.playerName + " you won!! <br> Shots: " + battleships.shotsFired
            visible: false
            onAccepted: {
                battleships.board.reset();
                battleships.enemyBoard.reset();
                battleships.reset();
                gameLogic.state = "HomeScreen"
            }
        }

        onQuitGame: {
            quitGame_dialog.visible = true;
        }

        onFinishedGame: {
            won_dialog.visible = true;
        }
    }

    GameScreenMulti {
        id: gameScreenMulti
        width: app.width
        height: app.height 

        onQuitGame: {
            quitGame_dialog.visible = true
        }

        onFinishedGame: {
        }
    }
}
