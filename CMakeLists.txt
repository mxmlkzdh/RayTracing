cmake_minimum_required(VERSION 3.0.0)
project(RayTracing VERSION 0.1.0)

set(GTEST_CMAKE_TESTING ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CONFIG:Debug>:-Wsign-conversion>)
add_compile_options($<$<CONFIG:Debug>:-Wall>)
add_compile_options($<$<CONFIG:Debug>:-Wextra>)
add_compile_options($<$<CONFIG:Debug>:-Wpedantic>)

add_executable(main src/main.cpp)

include_directories("include")
include_directories("external")


if (GTEST_CMAKE_TESTING) 
    include(CTest)
    enable_testing()
    add_subdirectory("tests")
endif()
