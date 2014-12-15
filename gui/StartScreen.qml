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
                    x: 0
                    visible: true
                }
            },
            State {
                name: "HomeScreen"
                PropertyChanges {
                    target: homeScreen
                    x: 0
                    visible: true
                }
            },
            State {
                name: "SettingsScreen"
                PropertyChanges {
                    target: settingsScreen
                    x: 0
                    visible: true
                }
            },
            State {
                name: "NewGameScreen"
                PropertyChanges {
                    target: newGameScreen
                    x: 0
                    visible: true
                }
            }
        ]

        transitions: [
            Transition {
                from: "*"
                to: "HomeScreen"
                NumberAnimation {
                    properties: "x"
                    from: app.width
                    easing.type: Easing.Linear
                    duration: 500
                }
            },
            Transition {
                from: "HomeScreen"
                to: "SettingsScreen"
                NumberAnimation {
                    properties: "x"
                    from: app.width
                    easing.type: Easing.Linear
                    duration: 500
                }
            },
            Transition {
                from: "HomeScreen"
                to: "NewGameScreen"
                NumberAnimation {
                    properties: "x"
                    from: app.width
                    easing.type: Easing.Linear
                    duration: 500
                }
            }
        ]
    }

    SplashScreen {
        id: splashScreen
        width: parent.width
        height: parent.height

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
