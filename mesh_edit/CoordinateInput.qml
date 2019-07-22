import QtQuick 2.12

import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

import own.classes.ctrl_points 1.0


Item {
    id: root
    property string label: "Custom Input"
    property CtrlPoints ctrl_points
    property Entity ctrl_point

    signal clicked()
    signal pressed()
    signal released()

    Keys.onReturnPressed:  {
        root.apply()
    }
    Keys.onEscapePressed: {
        root.cancel()
    }

    Rectangle {
        id:rect
        color: Qt.rgba(1.0, 1.0, 1.0, 0.5) // transparent white
        width: parent.width
        height: inp_label.contentHeight*1.25 + inp_x_lab.contentHeight + inp_y_lab.contentHeight + inp_z_lab.contentHeight + 5 + ok_but.height + 5

        border {
            width: 1
            color: "black"
        }

        Text {
            id: inp_label
            text: root.label
            x: rect.x + 10
            y: rect.y
            font.pointSize: 12
        }

        Text {
            id: inp_x_lab
            text: qsTr("[x]=")
            x: rect.x + 5
            y: rect.y + inp_label.contentHeight*1.25
            font.pointSize: 10
        }
        Text {
            id: inp_y_lab
            text: qsTr("[y]=")
            x: rect.x + 5
            y: rect.y + inp_label.contentHeight*1.25 + inp_x_lab.contentHeight
            font.pointSize: 10
        }
        Text {
            id: inp_z_lab
            text: qsTr("[z]=")
            x: rect.x + 5
            y: rect.y + inp_label.contentHeight*1.25 + inp_x_lab.contentHeight + inp_y_lab.contentHeight
            font.pointSize: 10
        }

        Rectangle {
            x: inp_x_lab.contentWidth + 5
            y: inp_x_lab.y
            width: rect.width - (inp_x_lab.contentWidth + 10)
            height: inp_x_lab.contentHeight

            border {
                color: "black"
                width: 1
            }

            TextInput {
                id: inp_x
                x: rect.x+5
                y: rect.y
                width: rect.width-5
                height: rect.height
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
        }

        Rectangle {
            x: inp_x_lab.contentWidth + 5
            y: inp_y_lab.y
            width: rect.width - (inp_x_lab.contentWidth + 10)
            height: inp_y_lab.contentHeight

            border {
                color: "black"
                width: 1
            }

            TextInput {
                id: inp_y
                x: rect.x+5
                y: rect.y
                width: rect.width-5
                height: rect.height
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
        }

        Rectangle {
            x: inp_x_lab.contentWidth + 5
            y: inp_z_lab.y
            width: rect.width - (inp_x_lab.contentWidth + 10)
            height: inp_z_lab.contentHeight

            border {
                color: "black"
                width: 1
            }

            TextInput {
                id: inp_z
                x: rect.x+5
                y: rect.y
                width: rect.width-5
                height: rect.height
                inputMethodHints: Qt.ImhFormattedNumbersOnly
            }
        }

        Button {
            id: ok_but
            label: "OK"
            width: 60
            height: 25

            x: inp_x_lab.x + 5
            y: rect.height - 30

            onPressed: {
                root.apply()
            }
        }

        Button {
            id: cancel_but
            label: "Cancel"
            width: 60
            height: 25

            x: rect.width - width - 5
            y: rect.height - 30

            onPressed: {
                root.cancel()
            }
        }
    }

    function apply() {
        x = parseFloat(inp_x.text)
        y = parseFloat(inp_y.text)
        z = parseFloat(inp_z.text)
        var v3d = Qt.vector3d(x,y,z)

        root.ctrl_points.sl_changePosition(root.ctrl_point, v3d)
        root.visible = false
        root.focus = false
    }

    function cancel() {
        root.visible = false
        root.focus = false
    }

    function set_entities(ctrl_points, ctrl_point) {
        root.ctrl_points = ctrl_points
        root.ctrl_point = ctrl_point
    }

    function set_dial_position(x, y) {
        root.x = x
        root.y = y
        coord_inp.visible = true
        root.focus = true
    }

    function set_ctrl_pt_position(x, y, z) {
        inp_x.text = x
        inp_y.text = y
        inp_z.text = z
    }
}
