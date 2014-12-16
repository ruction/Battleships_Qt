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

                oldItem: homeScreen
                newItem: newGameScreen

                from: "HomeScreen"
                to: "NewGameScreen"

                NumberAnimation {
                    target: gameTransition4.newItem
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
    }
}
