cmake_minimum_required(VERSION 3.1)
project(stl_lib)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(stl_format stl_import.cpp)

add_library(stl_format ${stl_format})
install(TARGETS stl_format RUNTIME DESTINATION bin)
