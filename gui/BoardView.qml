import QtQuick 2.0


Grid {
    x: 5; y: 5
    rows: board.height; columns: board.width; spacing: 5

    Repeater {
        model: board.width*board.height

        delegate: Rectangle {
            id: grid_element

            width: 40
            height: 40

            readonly property int row: model.index / board.width
            readonly property int column: model.index % board.width

            property bool isShip: board.shipOnPosition(row, column)

            Image {
                 id: img
                 anchors.fill: parent
                 source: grid_element.isShip ? "ship.png" : "water.png"
             }

            Connections {
                target: board

                onBoardReset: {
                    grid_element.isShip = false
                }

                onShipAdded: {
                    if (y === grid_element.row && x === grid_element.column) {
                        grid_element.isShip = true;
                        console.log("sadlfkj");
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log(grid_element.column + " : " + grid_element.row)
                    grid_element.isShip = true
                }

            }
        }
    }
}
