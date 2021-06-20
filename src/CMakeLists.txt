# find dependencies
find_package(Boost REQUIRED COMPONENTS system)

# add target
add_executable(tcp_server "main.cpp"
  "server.cpp")

# for initial tests. It will be replaced
add_executable(tcp_client "main_client.cpp")

# install rules
install(TARGETS tcp_server
  EXPORT tcp_server
  DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
