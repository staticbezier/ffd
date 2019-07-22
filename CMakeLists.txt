cmake_minimum_required(VERSION 3.1)
project(simple_ffd)

#C++17 stuff
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_subdirectory(stl)
add_subdirectory(mesh_edit)
add_subdirectory(image)
