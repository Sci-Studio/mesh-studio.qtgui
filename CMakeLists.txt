cmake_minimum_required(VERSION 3.14)
project(MeshGenQtApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets)

qt_standard_project_setup()

qt_add_executable(MeshGenQtApp
    src/Main.cpp
    src/MainWindow.cpp
    src/MainWindow.hpp
)

target_link_libraries(MeshGenQtApp
    PRIVATE 
        Qt6::Widgets)