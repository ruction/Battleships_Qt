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
                id: autoPlace
                text: "AUTOPLACE"

                onClicked: {
                    console.log("AUTOPLACE")

                    autoPlace.enabled = false
                    //outsource later!
                    for (var i = 0; i < battleships.availableShips.length; i++) {
                        var ship = battleships.availableShips[i];
                        var x = Math.random() * board.width + 0;
                        var y = Math.random() * board.height + 0;
                        var direction =  Math.random() * 3 + 0;

                        console.log(x + ", " + y + ", " + direction);
                        if (board.place(ship, x, y, direction)) {}
                        else {
                            --i;
                            continue;
                        }
                    }
                }

                Connections {
                    target: board
                    onBoardReset: autoPlace.enabled = true
                }
            }
            Button {
                text: "CLEAR"
                onClicked: board.reset();
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


