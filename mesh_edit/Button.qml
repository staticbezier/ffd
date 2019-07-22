import QtQuick 2.12
import QtQuick.Controls 1.3


Item {
    id: root
    property string label: "Custom Button"

    signal clicked()
    signal pressed()
    signal released()

    signal fileSelected(url file)

    Rectangle {
        color: "white"
        width: parent.width
        height: parent.height

        border {
            width: 1
            color: "black"
        }

        Text {
            anchors.centerIn: parent
            text: root.label
        }

        MouseArea {
            anchors.fill: parent

            onEntered: {
                parent.border.width = 2
                root.clicked()
            }
            onReleased: {
                parent.border.width = 1

                root.pressed()
                root.released()
            }
        }
    }
}
