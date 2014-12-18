import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1
import Battleships 1.0


BaseScreen {
    id: placeShipsScreen

    signal startGame

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
                    autoPlace.enabled = false
                    //outsource later!
                    for (var i = 0; i < battleships.board.ships.length; i++) {
                        var ship = battleships.board.ships[i];
                        var x = Math.random() * battleships.board.width + 0;
                        var y = Math.random() * battleships.board.height + 0;
                        var direction =  Math.random() * 3 + 0;

//                        console.log(x + ", " + y + ", " + direction);
                        if (battleships.board.place(ship, x, y, direction)) {}
                        else {
                            --i;
                            continue;
                        }
                    }

                    startGame_btn.enabled = true;
                }

                Connections {
                    target: battleships.board
                    onBoardReset: autoPlace.enabled = true
                }
            }
            Button {
                text: "CLEAR"
                onClicked: {
                    startGame_btn.enabled = false;
                    battleships.board.reset();
                }
            }

            Button {
                id: startGame_btn
                text: "START GAME"
                onClicked: {
                    startGame_btn.enabled = false;
                    startGame();
                }
                enabled: false
            }
        }

        PlaceBoardView {
            id: board_place

            board: battleships.board
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


