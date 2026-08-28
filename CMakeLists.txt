cmake_minimum_required(VERSION 3.14)
project(MeshGenQtApp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    meshgen
    GIT_REPOSITORY https://github.com/Sci-Studio/mesh-studio.meshgen.git
    GIT_TAG        6af7faad8c09cbacdd2d95b803aea5e237da73af  # current main tip
)


FetchContent_GetProperties(meshgen)

if(NOT meshgen_POPULATED)
    FetchContent_Populate(meshgen)
    add_subdirectory(
        ${meshgen_SOURCE_DIR}
        ${meshgen_BINARY_DIR}
        EXCLUDE_FROM_ALL
    )
endif()

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    OpenGL
    OpenGLWidgets)

qt_standard_project_setup()

qt_add_executable(MeshGenQtApp
    src/Main.cpp
    src/MainWindow.cpp
    src/MainWindow.hpp
    src/MeshPipeline.cpp
    src/MeshPipeline.hpp
    src/ViewPort.cpp
    src/ViewPort.hpp
    src/renderer/Shader.cpp
    src/renderer/Shader.hpp
    src/renderer/MeshRenderer.cpp
    src/renderer/MeshRenderer.hpp
    src/view/MenuBar.cpp
    src/view/MenuBar.hpp
    src/view/PreferencesPopup.cpp
    src/view/PreferencesPopup.hpp
    src/view/FloatingPanel.cpp
    src/view/FloatingPanel.hpp
    src/view/ToolBox.cpp
    src/view/ToolBox.hpp
    src/utils/Theme.cpp
    src/utils/Theme.hpp
)

qt_add_resources(MeshGenQtApp shader_resources
    PREFIX "/"
    BASE src
    FILES
        src/shaders/mesh.vertex
        src/shaders/mesh.fragment
        src/styles/tokens.qss
        src/styles/app.qss
        src/styles/ToolBox.qss
        src/styles/FloatingPanel.qss
        src/assets/ui/top.png
        src/assets/ui/iso.png
        src/assets/ui/triangulate.png
        src/assets/ui/file-doc.svg
)

target_link_libraries(MeshGenQtApp
    PRIVATE 
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        MeshGen)