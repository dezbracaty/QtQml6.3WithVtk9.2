cmake_minimum_required(VERSION 3.16)
project(fboitem LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(QTDIR "/Users/allen/Soft/Qt/6.3.1/macos/lib/cmake/Qt6")
set(Qt6_DIR "/Users/allen/Soft/Qt/6.3.1/macos/")
set(VTK_DIR "/Users/allen/Soft/Vtk/VTK_GitMaster/VTK/Dbuild")
if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}/quick/scenegraph/fboitem")
set(CMAKE_PREFIX_PATH ${Qt6_DIR} ${VTK_DIR})

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

find_package(VTK CONFIG REQUIRED)
include(${VTK_USE_FILE})

qt_add_executable(fboitem
    logorenderer.cpp logorenderer.h
    fboinsgrenderer.cpp fboinsgrenderer.h
    main.cpp
    myFboRenderer.h myFboRenderer.cpp
    FboOffscreenWindow.h FboOffscreenWindow.cpp
)

set_target_properties(fboitem PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_include_directories(fboitem PUBLIC
    ../shared
)

target_link_libraries(fboitem PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    ${VTK_LIBRARIES}
)

qt_add_qml_module(fboitem
    URI SceneGraphRendering
    VERSION 1.0
    QML_FILES main.qml
    RESOURCES shaders/checker.frag.qsb
    RESOURCE_PREFIX /scenegraph/fboitem
    NO_RESOURCE_TARGET_PATH
)

install(TARGETS fboitem
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
