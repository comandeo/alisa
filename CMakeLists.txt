cmake_minimum_required(VERSION 2.8)
project(alisa)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")

add_subdirectory(${alisa_SOURCE_DIR}/ext/gtest)

include_directories(${alisa_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})

file(GLOB SRC_FILES ${alisa_SOURCE_DIR}/src/*.cpp)
add_executable(
	alisac
	${SRC_FILES}
)

install(TARGETS alisac DESTINATION bin)

enable_testing()

file(GLOB TEST_SRC_FILES ${alisa_SOURCE_DIR}/test/*.cpp)
add_executable(run_unit_tests
	${TEST_SRC_FILES}
	)

target_link_libraries(run_unit_tests
	${GTEST_LIBS_DIR}/libgtest.a
	${GTEST_LIBS_DIR}/libgtest_main.a
	)

add_test(
	NAME run_unit_tests
	COMMAND run_unit_tests
)


