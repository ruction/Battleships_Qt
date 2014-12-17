import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal cancel

    NavigationBar {
        id: navigationBar

        title: "Settings"
    }

    ColumnLayout {
        anchors.centerIn: parent

        Button {
            text: "cancel"
            onClicked: {
                console.log(battleships.playerName)
                root.cancel()}
        }
    }
}
