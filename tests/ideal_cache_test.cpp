#include "../src/IdealCache.h"

#include <gtest/gtest.h>
#include <iostream>

TEST(first_id, first_test) {
    int size = 3, hits_expected = 3, hits_result = 0;

    std::vector <int> nums = { 1, 6, 9, 1, 6, 2, 5, 2};

    IdealCache<int> idc(size, nums);  
    idc.processStream(nums);
    hits_result = idc.hitret();

    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}

TEST(second_id, second_test) {
    int size = 4, hits_expected = 7, hits_result = 0;

    std::vector <int> nums = {1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};

    IdealCache<int> idc(size, nums);  
    idc.processStream(nums);
    hits_result = idc.hitret();

    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}

TEST(third_id, third_test) {
    int size = 3, hits_expected = 8, hits_result = 0;

    std::vector <int> nums = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2};

    IdealCache<int> idc(size, nums);
    idc.processStream(nums);
    hits_result = idc.hitret();

    ASSERT_EQ(hits_result, hits_expected) << "Test failed";
}
