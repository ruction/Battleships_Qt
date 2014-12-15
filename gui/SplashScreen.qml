import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal finished

    ColumnLayout {
        anchors.centerIn: parent

        Text {
            text: "Hallo Welt!"
        }

        Button {
            text: "Skip"
            onClicked: root.finished()
        }
    }
}
