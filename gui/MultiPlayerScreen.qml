import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    anchors.centerIn: parent

    Button {
        id: start_btn
        text: "start game"
    }
    Button {
        id: cancel_btn
        text: "cancel"

        onClicked: root.cancel();
    }
}
