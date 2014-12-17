import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Battleships 1.0


BaseScreen {
    id: placeShipsScreen


    NavigationBar {
        id: navigationBar

        title: "PLACESHIPS"
    }

    ColumnLayout {
        anchors.centerIn: parent

        RowLayout {
            Button {
                text: "AUTOPLACE"

                onClicked: {
                    console.log("AUTOPLACE")

                    for (var i in battleships.availableShips) {
                        while (!board.place(battleships.availableShips[i], Math.floor((Math.random() * battleships.availableShips[i].length) + 0),
                                    Math.floor((Math.random() * battleships.availableShips[i].length) + 0), Board.EAST)) {
                        }

                    }
                }
            }
            Button {
                text: "SAVE"
            }
        }

        BoardView {
            id: board_me
        }

        Repeater {
            model: battleships.availableShips

            delegate: Rectangle {
                id: rootDel
                property int length: model.length

                width: ship_element.width
                height: ship_element.height

                RowLayout {
                    id: ship_element

                    Text {
                        id: ship_meta
                        text: model.name + " : " + model.length
                    }
                    Repeater {
                        model: rootDel.length

                        delegate: Image {
                            source: "ship.png"
                        }
                    }
                }
            }
        }
    }
}


