cmake_minimum_required(VERSION 3.29)
project(MyTorch)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug)

# Add directories for header files
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Disable pthreads for Google Test on Windows
set(gtest_disable_pthreads ON)

# Add Google Test
add_subdirectory(googletest EXCLUDE_FROM_ALL)

# Add source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(mytorch_lib ${SOURCES})

# Add test files
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
add_executable(tests ${TEST_SOURCES}
        tests/test_main.cpp
        tests/test_shape.cpp)

# Link libraries
target_link_libraries(tests PRIVATE mytorch_lib gtest gtest_main)
