cmake_minimum_required(VERSION 3.10)
project(LFUCache)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(tests)

add_executable(ideal_cache src/main_ideal_cache.cpp src/LFUCache.h)
add_executable(lfu_cache src/main_lfu.cpp src/IdealCache.h)
