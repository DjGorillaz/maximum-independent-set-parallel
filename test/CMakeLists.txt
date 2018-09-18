find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(test_algo test_algo.cpp)

set_target_properties(test_algo PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARTD_REQUIRED ON
)

target_link_libraries(test_algo PRIVATE MISLib GTest::GTest GTest::Main)

add_test(TestAlgo test_algo)
