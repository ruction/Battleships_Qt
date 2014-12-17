import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1


BaseScreen {
    id: placeShipsScreen

    NavigationBar {
        id: navigationBar

        title: "PLACESHIPS"
    }

    ColumnLayout {
        anchors.centerIn: parent

        Board {
            id: board_me
        }

        Text {
            text: battleships.playerName
        }

        ListView {
            model: battleships.availableShips

            delegate: Text {
                text: model.name
            }
        }
    }
}


