import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Input 2.0
import Qt3D.Extras 2.0

import QtQuick 2.0

import own.classes.ctrl_points 1.0
import own.classes.stl_mesh 1.0


Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 60
        nearPlane : 0.001
        farPlane : 100.0
        position: Qt.vector3d( 0.0, 5.0, 0.0 )
        upVector: Qt.vector3d( 0.0, 0.0, 1.0 )
        viewCenter: Qt.vector3d( 0.5, 0.5, 0.5 )
    }

    OrbitCameraController {
         camera: camera
     }

    Entity {
        components: [
            PointLight {
                color: "white"
                intensity: 1
            },
            Transform {
                translation: camera.position
            }
        ]
    }

    components: [
        RenderSettings {
            activeFrameGraph: ForwardRenderer {
                camera: camera
                clearColor: "transparent"
            }
        },
        InputSettings { }
    ]

    PhongMaterial {
        id: material
    }

    CtrlPoints {
        id: ctrlPoints
        radius: 0.05

        onEntityPressed: {
            console.log(ctrl_point, entity_position.x, entity_position.y, entity_position.z)

            coord_inp.set_ctrl_pt_position(entity_position.x, entity_position.y, entity_position.z)
            coord_inp.set_dial_position(mouse_position.x, mouse_position.y)
            coord_inp.set_entities(ctrlPoints, ctrl_point)
        }

        onPositionChanged: {
            sceneRoot.updateMesh();
        }
    }

    Entity {
        id: mesh_entity
        PhongMaterial {
            id: mesh_mat
        }

        Transform {
            id: transl
        }

        StlMesh {
            id: mesh
        }

        components: [ mesh, mesh_mat, transl ]
    }

    function loadMesh(filename) {
        ctrlPoints.sl_resetCtrlPoints()
        mesh.sl_load(filename);
    }

    function updateMesh() {
        mesh.sl_performFFD(ctrlPoints);
    }
}
