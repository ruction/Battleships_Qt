import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: newGame

    signal next
    signal cancel

    readonly property string mode: tabView.currentIndex === 0 ? "single" : "multi"

    property string kind: "server"
    property SinglePlayerScreen single
    property MultiPlayerScreen multi


    NavigationBar {
        id: navigationBar

        title: "NEW GAME"
    }

    TabView {
        id: tabView
        width: parent.width
        anchors.top: navigationBar.bottom
        anchors.bottom: parent.bottom

        Tab {
            title: "Single Player"

            SinglePlayerScreen {
                id: singleScreen

                onNext: newGame.next()
                onCancel: newGame.cancel()

                Component.onCompleted: newGame.single = singleScreen
            }
        }
        Tab {
            title: "Multi Player"

            MultiPlayerScreen {
                id: multiScreen

                onNext: newGame.next()
                onCancel: newGame.cancel()
                onServer: kind = "server"
                onClient: kind = "client"

                Component.onCompleted: newGame.multi = multiScreen
            }
        }
    }
}
