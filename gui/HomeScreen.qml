import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    signal settings
    signal new_game

    ColumnLayout {
        anchors.centerIn: parent

        Button {
            id: new_game_btn
            text: "NEW GAME"

            onClicked: root.new_game()
        }

        Button {
            id: settings_btn
            text: "SETTINGS"

            onClicked: root.settings()
        }

        Button {
            id: exit_btn
            text: "EXIT"

            onClicked: Qt.quit();
        }
    }
}
