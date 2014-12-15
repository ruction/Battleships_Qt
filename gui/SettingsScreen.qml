import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

BaseScreen {
    id: root

    NavigationBar {
        id: navigationBar
    }

    ColumnLayout {
        anchors.centerIn: parent

        Text {
            text: "Settings"
        }
    }
}
