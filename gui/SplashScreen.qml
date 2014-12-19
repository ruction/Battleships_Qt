import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root
    color: "white"

    signal skip

    ColumnLayout {
        anchors.centerIn: parent

        Text {
            text: "<b>Battleships<b>"
            font.family: "Helvetica [Cronyx]"
            font.pixelSize: 40
            color: "blue"
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
        }

        Item {
            height: 50
        }

        Rectangle {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
             width: animation.width; height: animation.height + 8

             AnimatedImage {
                 id: animation

                 source: "images/animation.gif"
             }

             Rectangle {
                 property int frames: animation.frameCount

                 width: 4; height: 8
                 x: (animation.width - width) * animation.currentFrame / frames
                 y: animation.height
                 color: "blue"
             }
         }

        Item {
            height: 200
        }

        Button {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            id: continue_btn
            text: "continue"

            onClicked: root.skip()
        }
    }
}
