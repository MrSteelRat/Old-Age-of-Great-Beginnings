cmake_minimum_required(VERSION 3.18)

option(LEARNING_USE_SANITIZERS "" ON)

project(learning CXX)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CONFIGURATION_TYPES Debug Release)
foreach(config ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${config} config)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${config} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${config} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${config} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endforeach()

add_library(learning_compile_options INTERFACE)
target_compile_features(learning_compile_options INTERFACE cxx_std_20)
target_compile_options(learning_compile_options
  INTERFACE
    $<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/W4 >
    $<$<COMPILE_LANG_AND_ID:CXX,Clang,GNU>:-Wall -Wextra -pedantic >)
    #$<$<COMPILE_LANG_AND_ID:C,MSVC>:/W4 /WX>
    #$<$<COMPILE_LANG_AND_ID:C,Clang,GNU>:-Wall -Werror -Wextra -pedantic -pedantic-errors>)
if(MSVC)
  target_compile_definitions(learning_compile_options INTERFACE _CRT_SECURE_NO_WARNINGS)
endif()

add_library(learning_dependencies INTERFACE)

#add_subdirectory(src)
add_subdirectory(src1)