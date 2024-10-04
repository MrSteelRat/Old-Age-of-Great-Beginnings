cmake_minimum_required (VERSION 3.8)

project ("CAD_Exchanger_Test")

set(CMAKE_CXX_STANDARD 20)

# Setting compilation flags depending on the operating system
if (WIN32)
    # Adding options for Windows
    add_executable(CAD_Exchanger_Test "deps/Curve3d.h" "deps/Circle.h" "deps/Circle.cpp" "deps/Ellipse.h" "deps/Ellipse.cpp" "main.cpp" "deps/Helix.h" "deps/Helix.cpp" )
elseif(UNIX)
    # Adding options for Linux & enable compiler warnings
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

    add_executable(CAD_Exchanger_Test "deps/Curve3d.h" "deps/Circle.h" "deps/Circle.cpp" "deps/Ellipse.h" "deps/Ellipse.cpp" "main.cpp" "deps/Helix.h" "deps/Helix.cpp" )
endif()

set_property(TARGET CAD_Exchanger_Test PROPERTY CXX_STANDARD 20)
set_property(TARGET CAD_Exchanger_Test PROPERTY CXX_STANDARD_REQUIRED ON)
