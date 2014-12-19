import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    id: multiPlayer
    anchors.centerIn: parent

    signal next
    signal cancel

    RowLayout {
        anchors {
            horizontalCenter: multiPlayer.horizontalCenter
        }
        Button {
            id: start_btn
            text: "start game"
//            onClicked: multiPlayer.next()
        }
        Button {
            id: cancel_btn
            text: "cancel"

            onClicked: multiPlayer.cancel()
        }
    }
}
