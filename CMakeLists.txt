cmake_minimum_required(VERSION 3.8)

project(maximum-independent-set-parallel)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Boost 1.36.0 COMPONENTS date_time filesystem system ...)
find_package(Boost COMPONENTS thread graph)

include_directories(${Boost_INCLUDE_DIRS})

set(SRCS main.cpp
         graph.cpp
         finder.cpp
         finder_greedy.cpp
         finder_brute.cpp)

add_executable(${PROJECT_NAME} ${SRCS})

#Treat warnings as errors
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#target_link_libraries(${PROJECT_NAME}   Boost::thread
#                                        Boost::graph
#)
