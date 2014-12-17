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


