cmake_minimum_required(VERSION 2.8)
project(foo)

add_compile_options(-std=c++11)

set(PROJECT_PATH	${CMAKE_CURRENT_SOURCE_DIR})
set(SRCS_PATH		"${PROJECT_PATH}/src")
set(CPPLIB_INCLUDE_DIR	"${PROJECT_PATH}/include" CACHE	INTERNAL "foo include directories")

include_directories(${CPPLIB_INCLUDE_DIR})
	
file(GLOB SRCS "${SRCS_PATH}/*.cpp" "${SRCS_PATH}/*.h")

add_library(${PROJECT_NAME} SHARED ${SRCS})
