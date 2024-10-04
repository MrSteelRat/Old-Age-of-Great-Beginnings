cmake_minimum_required(VERSION 3.25)

project(study CXX)

include(cmake/setup.cmake)

add_library(study_compile_options INTERFACE)
target_compile_features(study_compile_options INTERFACE cxx_std_20)
target_compile_options(study_compile_options INTERFACE
  $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4>
  $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wall -Wextra -pedantic>
)

option(FREEGLUT_BUILD_DEMOS "Build FreeGLUT demos." OFF)
OPTION(FREEGLUT_BUILD_SHARED_LIBS "Build FreeGLUT shared library." OFF)
add_subdirectory(deps/freeglut-3.4.0 EXCLUDE_FROM_ALL)
set_property(TARGET freeglut_static PROPERTY FOLDER deps)

find_package(OpenGL REQUIRED)

add_library(study_dependencies INTERFACE)
target_link_libraries(study_dependencies INTERFACE freeglut_static OpenGL::GLU)
target_include_directories(study_dependencies INTERFACE deps/freeglut-3.4.0/include)

add_library(study_include_directories INTERFACE)
target_include_directories(study_include_directories INTERFACE src)

file(GLOB data data/*)
file(COPY ${data} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(src)
