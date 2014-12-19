import QtQuick 2.0
import Battleships 1.0

Grid {
    x: 5; y: 5
    rows:  board.height; columns:  board.width;

    property Board board

    Repeater {
        model:  board.width* board.height

        delegate: Rectangle {
            id: grid_element

            width: 40
            height: 40

            Image {
                 id: img
                 anchors.fill: parent
                 source: "images/water.png"
            }
        }
    }
}
