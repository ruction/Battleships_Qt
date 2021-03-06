import QtQuick 2.0
import Battleships 1.0
import QtQuick.Dialogs 1.2

Grid {
    id: root
    property Board board
    property Network network


    x: 5; y: 5
    rows: board.height; columns: board.width;

    MessageDialog {
        id: destroyed_dialog
        title: "YOU WON!"
        text: ""
        visible: false
    }

    Repeater {
        model: board.width*board.height

        delegate: Rectangle {
            id: grid_element

            width: 40
            height: 40

            readonly property int row: model.index / board.width
            readonly property int column: model.index % board.width

            property bool isShip: board.shipOnPositionMulti(row, column)
            property bool isShot: board.shotOnPosition(row, column)

            Image {
                 id: img
                 anchors.fill: parent
                 source: {
                     if (grid_element.isShot && grid_element.isShip) {
                        return "images/fired_damage.png";
                     } else if (grid_element.isShip) {
                         return "images/ship.png";
                     } else if (grid_element.isShot) {
                         return "images/fired.png";
                     } else {
                         return "images/water.png";
                     }
                  }
             }

            Connections {
                target: board

                onBoardReset: {
                    grid_element.isShip = false
                    grid_element.isShot = false
                }
                onShotAdded: {
                    if (y === grid_element.row && x === grid_element.column) {
                        grid_element.isShot = true;
                    }
                }
                onShipAdded: {
                    if (y === grid_element.row && x === grid_element.column) {
                        grid_element.isShip = true;
                    }
                }
            }

            MouseArea {
                id: enemyBoardField
                enabled: root.enabled
                anchors.fill: parent
                onClicked: {
                    board.shoot(grid_element.column, grid_element.row);
                    root.network.sendShot(grid_element.column, grid_element.row);

                }
            }
        }
    }
}
