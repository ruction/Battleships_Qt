import QtQuick 2.0
import QtQuick.Controls 1.2


Rectangle {
    id: root

    width: parent.width
    height: 40

    signal back;

    anchors {
        top: parent.top
    }

    Button {
        id: back_btn
        text: "< "

        onClicked: root.back()
    }

    color: "grey"
}
