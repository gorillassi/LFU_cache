cmake_minimum_required(VERSION 3.10)
project(LFUCacheExample)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests src/main.cpp src/LFUCache.cpp src/IdealCache.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
