cmake_minimum_required(VERSION 3.16)
project(alisa)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(CMAKE_CXX_STANDARD 11)

include_directories(${alisa_SOURCE_DIR}/include)

file(GLOB SRC_FILES ${alisa_SOURCE_DIR}/src/*.cpp)
add_executable(
	alisac
	${SRC_FILES}
)

