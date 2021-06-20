cmake_minimum_required(VERSION 3.10)
project(tcp_server)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_subdirectory(src)
# TODO: execute only if TEST is enabled
# add_subdirectory(test)

# enable_testing()

# add_test(test1 ${CMAKE_BINARY_DIR}/test/test1 "[test1]")
# add_test(test2 ${CMAKE_BINARY_DIR}/test/test2 "[test2]")
