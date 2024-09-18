cmake_minimum_required(VERSION 3.29)
project(MyTorch)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add directories for header files
include_directories(${CMAKE_SOURCE_DIR}/headers)

# Add Google Test
add_subdirectory(${CMAKE_SOURCE_DIR}/googletest)

# Add source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(mytorch_lib ${SOURCES})

# Add test files
file(GLOB TEST_SOURCES ${CMAKE_SOURCE_DIR}/tests/*.cpp)
add_executable(tests ${TEST_SOURCES})

# Link libraries
target_link_libraries(tests mytorch_lib gtest gtest_main pthread)
