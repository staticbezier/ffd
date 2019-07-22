cmake_minimum_required(VERSION 3.1)
project(mesh_gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets 3DCore 3DExtras 3DAnimation 3DRender 3DInput 3DQuick 3DLogic)

qt5_add_resources(QML_RES
    qml.qrc
)

set(MESH_SRC 
    main.cpp 
    ctrl_points.cpp
    stl_mesh_geom.cpp
    stl_mesh.cpp
)

add_executable(mesh_edit ${MESH_SRC} ${QML_RES})
target_link_libraries(mesh_edit stl_format
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::3DCore
    Qt5::3DExtras
    Qt5::3DRender
    Qt5::3DInput
    Qt5::3DAnimation
    Qt5::3DQuick
    Qt5::3DLogic
    )

install(TARGETS mesh_edit RUNTIME DESTINATION bin)
