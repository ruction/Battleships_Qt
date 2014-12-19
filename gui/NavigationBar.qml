import QtQuick 2.0


Rectangle {
    id: root

    property string title

    width: parent.width
    height: 40

    anchors {
        top: parent.top
    }

    Text {
        text: title
        anchors {
            horizontalCenter: root.horizontalCenter
            verticalCenter: root.verticalCenter
        }
    }

    color: "grey"
}
