cmake_minimum_required(VERSION 2.8)
project(alisa)
set(CMAKE_CXX_FLAGS "-std=c++11")
include_directories(${alisa_SOURCE_DIR}/include)

add_executable(
	alisac
	${alisa_SOURCE_DIR}/src/alisac.cpp
	${alisa_SOURCE_DIR}/src/tokenizer.cpp
	${alisa_SOURCE_DIR}/src/parser.cpp
	${alisa_SOURCE_DIR}/src/ast.cpp
	${alisa_SOURCE_DIR}/src/compiler.cpp
)

install(TARGETS alisac DESTINATION bin)
