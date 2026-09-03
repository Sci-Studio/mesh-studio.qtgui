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
    src/view/MainWindow.cpp
    src/view/MainWindow.hpp
    src/view/MenuBar.cpp
    src/view/MenuBar.hpp
    src/view/PreferencesPopup.cpp
    src/view/PreferencesPopup.hpp
    src/view/MeshRenderer.cpp
    src/view/MeshRenderer.hpp
    src/view/ViewPort.cpp
    src/view/ViewPort.hpp
    src/view/MeshExplorer.cpp
    src/view/MeshExplorer.hpp
    src/view/ToolBox.cpp
    src/view/ToolBox.hpp
    src/utils/Theme.cpp
    src/utils/Theme.hpp
    src/utils/Shader.cpp
    src/utils/Shader.hpp
    src/controller/MeshController.cpp
    src/controller/MeshController.hpp
    src/model/UIMesh.cpp
    src/model/UIMesh.hpp
)

qt_add_resources(MeshGenQtApp shader_resources
    PREFIX "/"
    BASE res
    FILES
        res/shaders/mesh.vertex
        res/shaders/mesh.fragment
)

qt_add_resources(MeshGenQtApp style_resources
    PREFIX "/"
    BASE res
    FILES
        res/styles/tokens.qss
        res/styles/app.qss
        res/styles/ToolBox.qss
        res/styles/FloatingPanel.qss
        res/styles/MeshExplorer.qss
)

qt_add_resources(MeshGenQtApp "icons"
    PREFIX "/"
    BASE res
    FILES
        res/svg/File_24.svg
        res/svg/Grid_24.svg
        res/svg/Triangulate_24.svg
        res/svg/Rotate_CCW_24.svg
        res/svg/Rotate_CW_24.svg
        res/svg/Chevron_24.svg
)

target_link_libraries(MeshGenQtApp
    PRIVATE 
        Qt6::Widgets
        Qt6::OpenGL
        Qt6::OpenGLWidgets
        MeshGen)