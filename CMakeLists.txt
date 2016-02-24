cmake_minimum_required(VERSION 2.8)
project(alisa)
set(CMAKE_CXX_FLAGS "-std=c++11 -g")
include_directories(${alisa_SOURCE_DIR}/include)

add_executable(
	alisac
	${alisa_SOURCE_DIR}/src/tokenizer.cpp
	${alisa_SOURCE_DIR}/src/parser.cpp
	${alisa_SOURCE_DIR}/src/ast.cpp
	${alisa_SOURCE_DIR}/src/compiler.cpp
	${alisa_SOURCE_DIR}/src/module.cpp
	${alisa_SOURCE_DIR}/src/vm.cpp
	${alisa_SOURCE_DIR}/src/alisac.cpp
)

install(TARGETS alisac DESTINATION bin)
