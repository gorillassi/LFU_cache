cmake_minimum_required(VERSION 3.10)
project(LFUCache)

set(CMAKE_CXX_STANDARD 20)

# Добавляем исполняемый файл для IdealCache
add_executable(ideal_cache src/main_ideal_cache.cpp src/IdealCache.cpp)  # Добавьте IdealCache.cpp

# Если у вас есть еще один исполняемый файл, добавьте нужные компоненты
add_executable(lfu_cache src/main_lfu.cpp src/LFUCache.cpp)  # Предполагая, что LFUCache тоже имеет реализацию
