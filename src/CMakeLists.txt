find_package(Boost COMPONENTS thread graph)

include_directories(${Boost_INCLUDE_DIRS})

add_library(MISLib finder.h
                   graph.cpp
                   finder_greedy.cpp
                   finder_brute.cpp
                   graph.h
                   finder_greedy.h
                   finder_brute.h)

target_link_libraries(MISLib ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp)

#Treat warnings as errors
if (MSVC)
    target_compile_options(MISLib PRIVATE /W4 /WX)
else()
    target_compile_options(MISLib PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

set_target_properties(${PROJECT_NAME} MISLib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME} PRIVATE MISLib)
