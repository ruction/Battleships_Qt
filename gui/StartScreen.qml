import QtQuick 2.0
import QtQuick.Controls 1.2

ApplicationWindow {
    id: window

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
            }

        ]
    }

    SplashScreen {
        id: splashScreen
        anchors.fill: parent

        visible: true
        color: "red"

        onFinished: gameLogic.state = "HomeScreen"
    }

    HomeScreen {
        id: homeScreen
        anchors.fill: parent
    }
}
