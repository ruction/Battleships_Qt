import QtQuick 2.0
import Battleships 1.0

Grid {
    x: 5; y: 5

    property Board board

    rows: board.height; columns: board.width;

        Repeater {
            model: board.width*board.height

            DropArea {
                id: dragTarget

                property alias dropProxy: dragTarget

                width: 40; height: 40

                 Rectangle {
                    id: grid_element

                    anchors.fill: parent

                    states: [
                        State {
                            when: dragTarget.containsDrag
                            PropertyChanges {
                                target: img
                                source: {
                                    return "images/hover.png"
                                }
                            }
                        }
                    ]

                    width: 40
                    height: 40

                    readonly property int row: model.index / board.width
                    readonly property int column: model.index % board.width

                    property bool isShip: board.shipOnPosition(row, column)

                    Image {
                         id: img
                         anchors.fill: parent
                         source: {
                             if (grid_element.isShip) {
                                 return "images/ship.png";
                             } else {
                                 return "images/water.png";
                             }
                          }
                     }

                    Connections {
                        target: board

                        onBoardReset: {
                            grid_element.isShip = false
                        }
                        onShipAdded: {
                            if (y === grid_element.row && x === grid_element.column) {
                                grid_element.isShip = true;
                            }
                        }
                    }
                }
        }
    }
}
