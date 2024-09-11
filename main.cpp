#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0), hits(0) {}

    /*void cachePrint(std::unordered_map<int, int> cache){
        std::cout << "Cache contents:\n";
        for (const auto& item : cache) {
            std::cout << "Value: " << item.first << ", Frequency: " << item.second << "\n";
        }
    }*/

    void get(int value) {
        if (cache.find(value) != cache.end()){
            hits++; 
            incFreq(value);
            //cachePrint(cache);
        } else{
            put(value);
        }
    }

    void put(int value) {
        if (capacity == 0){
            //std::cout << "Cache is empty!\n";
        }
        else {
            if (cache.size() >= capacity) {
                removeElm();
            }
            cache[value] = 1;
            freq[value] = 1;
            map_of_nums_freq[1].push_back(value);
            minFreq = 1;
        }
    }

    int hitsRet() const {
        return hits;
    }

private:
    int capacity;
    int minFreq;
    int hits;

    std::unordered_map<int, int> cache; 
    std::unordered_map<int, int> freq;  
    std::unordered_map<int, std::vector<int>> map_of_nums_freq; 

    void incFreq(int value) {
        int currentFreq = freq[value];
        freq[value]++;

        map_of_nums_freq[currentFreq].erase(std::remove(map_of_nums_freq[currentFreq].begin(), map_of_nums_freq[currentFreq].end(), value), map_of_nums_freq[currentFreq].end());
        map_of_nums_freq[currentFreq+1].push_back(currentFreq);

        if(map_of_nums_freq[currentFreq].empty() && currentFreq == minFreq){
            minFreq++;
        }
    }

    void removeElm() {
        if (!map_of_nums_freq[minFreq].empty()) {
            int remEl = map_of_nums_freq[minFreq].front();
            map_of_nums_freq[minFreq].erase(map_of_nums_freq[minFreq].begin());
            cache.erase(remEl);
            freq.erase(remEl);
        }
    }
};

TEST(LFUTest, Test1) {
    LFUCache lfu(2);
    std::vector<int> nums = {1, 2, 1, 2, 1, 2};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 4);
}

TEST(LFUTest, Test2) {
    LFUCache lfu(3);
    std::vector<int> nums = {1, 2, 3, 1, 2};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 2); 
}

TEST(LFUTest, Test3) {
    LFUCache lfu(2);
    std::vector<int> nums = {1, 1, 2, 3, 1, 2, 1};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 3);
}

TEST(LFUTest, Test4) {
    LFUCache lfu(1);
    std::vector<int> nums = {5, 5, 5, 5, 5};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 4);
}

TEST(LFUTest, Test5) {
    LFUCache lfu(3);
    std::vector<int> nums = {1, 2, 3, 2, 2, 1, 1};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 4);
}

TEST(LFUTest, Test6) {
    LFUCache lfu(0);
    std::vector<int> nums = {1, 1, 2, 3};
    for (int num : nums) {
        lfu.get(num);
    }
    EXPECT_EQ(lfu.hitsRet(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
    /*LFUCache lfu(2);
    std::vector<int> nums = {1, 1, 2, 3, 1, 2, 1};
    for (int num : nums) {
        lfu.get(num);
    }
    std::cout << "LFU: " << lfu.hitsRet() << "\n";*/
}
