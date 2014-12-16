import QtQuick 2.0

Transition {
    id: root

    property Item oldItem
    property Item newItem

    default property alias animation: innerAnimation.animations

    SequentialAnimation {
        PropertyAction {
            targets: root.oldItem
            property: "visible"
            value: true
        }
        PropertyAction {
            targets: root.newItem
            property: "visible"
            value: true
        }
        SequentialAnimation {
            id: innerAnimation
        }
        ScriptAction {
        }
    }
}
