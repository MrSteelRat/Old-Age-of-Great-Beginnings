cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(TetrisApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick Widgets OpenGL OpenGLWidgets)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

# Find SFML package
#find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

qt_add_executable(TetrisApp
    src/main.cpp
    gamescreen.h
    gamescreen.cpp
    gamescreen.ui
    mainmenugame.h
    mainmenugame.cpp
    mainmenugame.ui
)

qt_add_resources(TetrisApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(TetrisApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    )

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS TetrisApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
