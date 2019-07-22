cmake_minimum_required(VERSION 3.1)
project(simple_ffd)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

qt5_add_resources(IMG
    image.qrc
)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(ffd_image ffd_image.cpp)

add_executable(ffd_image ${ffd_image} ${IMG})
target_link_libraries(ffd_image Qt5::Widgets)
install(TARGETS ffd_image RUNTIME DESTINATION bin)
