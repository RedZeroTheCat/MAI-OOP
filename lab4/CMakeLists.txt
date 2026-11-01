cmake_minimum_required(VERSION 3.10)
project(gtest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(lab4 main.cpp)

enable_testing()

add_executable(tests4 tests4.cpp)
target_link_libraries(tests4 PRIVATE ${GTEST_LIBRARIES})