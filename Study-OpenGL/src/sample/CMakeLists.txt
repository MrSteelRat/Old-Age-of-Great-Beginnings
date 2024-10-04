file(GLOB SOURCE *.cpp)

foreach(target IN LISTS SOURCE)
  string(REGEX MATCH "([A-Za-z0-9_.]+).cpp$" _ "${target}")
  add_executable(${CMAKE_MATCH_1} ${CMAKE_MATCH_1}.cpp)
  target_link_libraries(${CMAKE_MATCH_1} PRIVATE
    study_compile_options
    study_dependencies
    study_include_directories
  )
  set_property(TARGET ${CMAKE_MATCH_1} PROPERTY FOLDER 1)
endforeach()
