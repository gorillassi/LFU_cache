#include "../src/LFUCache.h"

#include <iostream>
#include <vector>
#include <gtest/gtest.h>

TEST(first, first_test) {
    int size = 3, hits_expected = 2, hits_result = 0;

    std::vector <int> nums = { 1, 6, 9, 1, 6, 2, 5, 2};

    LFUCache<int> lfu(size);
    for(const auto &num : nums){
        lfu.get(num);
    }

    hits_result = lfu.hitsRet();

    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}

TEST(second, second_test) {
    int size = 4, hits_expected = 6, hits_result = 0;

    std::vector <int> nums = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};

    LFUCache<int> lfu(size);
    for(const auto &num : nums){
        lfu.get(num);
    }

    hits_result = lfu.hitsRet();
    
    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}

TEST(third, third_test) {
    int size = 3, hits_expected = 6, hits_result = 0;

    std::vector <int> nums = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};

    LFUCache<int> lfu(size);
    for(const auto &num : nums){
        lfu.get(num);
    }

    hits_result = lfu.hitsRet();
    
    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}