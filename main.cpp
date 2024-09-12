#include <iostream>
#include <gtest/gtest.h>
#include "LFUCache.h"
#include "IdealCache.h"

TEST(LFUTest, Test1) {
    std::vector<int> nums = {1, 2, 1, 2, 1, 2};
    LFUCache lfu(2);
    IdealCache idc(2, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";
}


TEST(LFUTest, Test2) {
    std::vector<int> nums = {1, 2, 3, 1, 2};
    LFUCache lfu(3);
    IdealCache idc(3, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";
}

TEST(LFUTest, Test3) {
    std::vector<int> nums = {1, 1, 2, 3, 1, 2, 1};
    LFUCache lfu(2);
    IdealCache idc(2, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";

}

TEST(LFUTest, Test4) {
    std::vector<int> nums = {5, 5, 5, 5, 5, 5};
    LFUCache lfu(1);
    IdealCache idc(1, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";
}

TEST(LFUTest, Test5) {
    std::vector<int> nums = {1, 2, 3, 2, 2, 1, 1};
    LFUCache lfu(3);
    IdealCache idc(3, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";
}

TEST(LFUTest, Test6) {
    std::vector<int> nums = {1, 1, 2, 3};
    LFUCache lfu(0);
    IdealCache idc(0, nums);

    for (int num : nums) {
        lfu.get(num);
        idc.get(num);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n" << "Ideal cache: " << idc.hitsRet() << "\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
