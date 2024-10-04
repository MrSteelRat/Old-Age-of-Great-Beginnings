cmake_minimum_required(VERSION 3.25)


project(hge-openal CXX)

include(cmake/setup.cmake)

add_library(app_compile_options INTERFACE)
target_compile_features(app_compile_options INTERFACE cxx_std_20)
target_compile_options(app_compile_options INTERFACE /W4)

add_library(app_dependencies INTERFACE)

add_subdirectory(deps/openal EXCLUDE_FROM_ALL)

add_library(app_include_directories INTERFACE)
target_include_directories(app_include_directories INTERFACE src)

file(GLOB data data/*)
file(COPY ${data} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(src)