cmake_minimum_required(VERSION 2.8)
project(java-cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

include_directories(foo)

option(BUILD_TESTS "Build the test suite (requires foo)" ON)
if(BUILD_TESTS)
    enable_testing()
endif()

add_subdirectory(foo)
add_subdirectory(java-jni)
