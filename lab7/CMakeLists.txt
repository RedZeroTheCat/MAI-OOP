cmake_minimum_required(VERSION 3.10)
project(gtest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)


add_library(lab7_lib ${SOURCES})

add_executable(lab7 main.cpp)
target_link_libraries(lab7 PRIVATE lab7_lib)

enable_testing()

add_executable(tests7 tests7.cpp)
target_link_libraries(tests7 PRIVATE lab7_lib ${GTEST_LIBRARIES})