cmake_minimum_required(VERSION 3.8)

project(maximum-independent-set-parallel)

#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
