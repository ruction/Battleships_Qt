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

        RowLayout {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            Button {
                text: "save"
            }
            Button {
                text: "cancel"

                onClicked: {
                    root.cancel()
                }
            }
        }


    }
}
