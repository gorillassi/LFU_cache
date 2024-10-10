project(Test)

include(GoogleTest)

add_executable(lfu_test  ../src/LFUCache.h lfu_test.cpp)
add_executable(ideal_test ideal_cache_test.cpp ../src/IdealCache.h)
target_link_libraries(lfu_test gtest gtest_main)
target_link_libraries(ideal_test gtest gtest_main)
