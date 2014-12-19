import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal skip

    ColumnLayout {
        anchors.centerIn: parent

        Text {
            text: "Battleships"
        }

        Rectangle {
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

        Button {
            id: continue_btn
            text: "continue"

            onClicked: root.skip()
        }
    }
}
