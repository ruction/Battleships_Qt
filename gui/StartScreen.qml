import QtQuick 2.0
import QtQuick.Controls 1.2

ApplicationWindow {
    id: app

    width: 500
    height: 600
    visible: true

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
            }
        ]

        transitions: [
            GameTransition {
                id: gameTransition

                oldItem: splashScreen
                newItem: homeScreen

                NumberAnimation {
                    target: gameTransition.newItem
                    properties: "x"
                    from: app.width
                    to: 0
                    easing.type: Easing.Linear
                    duration: 500
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
    }

    NewGameScreen {
        id: newGameScreen
        width: app.width
        height: app.height
    }
}
