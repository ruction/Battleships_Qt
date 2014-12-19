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
        anchors {
            horizontalCenter: parent.horizontalCenter
        }

        Item {
            height: 80
        }

        RowLayout {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            Button {
                id: autoPlace
                text: "AUTOPLACE"

                onClicked: {
                    for (var i=0;i<ships_list.count;i++) {
                        ships_list.itemAt(i).visible = false
                    }
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
                    for (var i=0;i<ships_list.count;i++) {
                        ships_list.itemAt(i).visible = true
                    }
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

        Item {
            height: 10
        }

        Repeater {
            id: ships_list
            model: battleships.availableShips

            delegate: Rectangle {
                id: rootDel
                property int length: model.length

                width: ship_element.width
                height: ship_element.height
                color: "#c0d3d3"

                Column {
                    id: ship_element

                    Text {
                        id: ship_meta
                        text: model.name + " : " + model.length
                    }
                    Item {
                        id: root

                        width: rootDel.length*40; height: 40

                        MouseArea {
                            id: mouseArea

                            onDoubleClicked: tile.rotation += 90

                            width: rootDel.length*40; height: 40
                            anchors.centerIn: root

                            drag.target: tile

                            onReleased: parent = tile.Drag.target !== null ? tile.Drag.target : root

                            Rectangle {
                                id: tile
                                width: rootDel.length*40
                                height: 40
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter

                                Row {
                                    Repeater {
                                        model: rootDel.length
                                        delegate: Image {
                                            source: "images/ship.png"
                                        }
                                    }
                                }

                                Drag.active: mouseArea.drag.active
                                Drag.hotSpot.x: 20
                                Drag.hotSpot.y: 20
                                states: State {
                                    when: mouseArea.drag.active
                                    ParentChange { target: tile; parent: root }
                                    AnchorChanges { target: tile; anchors.verticalCenter: undefined; anchors.horizontalCenter: undefined }
                                }

                            }
                        }
                    }
                }
            }
        }
    }
}


