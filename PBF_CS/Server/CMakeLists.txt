add_executable(Server
  Server.cpp Server.h)

  target_link_libraries(Server PRIVATE pthread)