import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal cancel
    property string playerName: playerName_input.text
    property string boardWidth: boardWidth_input.text
    property string boardHeight: boardHeight_input.text
    property bool autoPlaceShips

    NavigationBar {
        id: navigationBar

        title: "NEW GAME"
    }

    TabView {
        width: parent.width
        anchors.top: navigationBar.bottom
        anchors.bottom: parent.bottom

        Tab {
            title: "Single Player"

            SinglePlayerScreen {

            }
        }
        Tab {
            title: "Multi Player"

            MultiPlayerScreen {

            }
        }
    }


}
