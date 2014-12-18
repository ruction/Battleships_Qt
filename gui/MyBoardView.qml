import QtQuick 2.0
import QtQuick.Dialogs 1.2
import Battleships 1.0

Grid {
    property Board board

    x: 5; y: 5
    rows: board.height; columns: board.width; spacing: 5

    MessageDialog {
        id: destroyed_dialog
        title: "Ship destroyed!"
        text: "coming soon..."
        visible: false
        onAccepted: {
            Qt.quit()
        }
    }

    Repeater {
        model: board.width*board.height

        delegate: Rectangle {
            id: grid_element

            width: 40
            height: 40

            readonly property int row: model.index / board.width
            readonly property int column: model.index % board.width

            property bool isShip: board.shipOnPosition(row, column)
            property bool isShot: board.shotOnPosition(row, column)

            Image {
                 id: img
                 anchors.fill: parent
                 source: {
                     if (grid_element.isShot && grid_element.isShip) {
                        return "fired_damage.png";
                     } else if (grid_element.isShip) {
                         return "ship.png";
                     } else if (grid_element.isShot) {
                         return "fired.png";
                     } else {
                         return "water.png";
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
                anchors.fill: parent
                onClicked: {
                    board.shoot(grid_element.column, grid_element.row);
                    grid_element.isShot = true
                    if (board.shipDamaged(grid_element.column, grid_element.row)) {
                        console.log("damage");
                    } else {
                        console.log("nothing");
                    }
                    if (board.allShipsDestroyed()) {
                        console.log("FINISH");
                    }
                }
            }
        }
    }
}
