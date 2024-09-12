#include <iostream>
#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <algorithm>


class LFUCache {
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0), hits(0) {}

    void get(int value) {
        if (cache.find(value) != cache.end()){
            hits++; 
            incFreq(value);
        } else{
            put(value);
        }
    }

    void put(int value) {
        if (capacity == 0){
            
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

    int hitsRet() {
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

        map_of_nums_freq[currentFreq].erase(std::remove(map_of_nums_freq[currentFreq].begin(),
                                                        map_of_nums_freq[currentFreq].end(), value), 
                                                        map_of_nums_freq[currentFreq].end());

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

class IdealCache{
public:
    IdealCache(int capacity, std::vector<int>& futureNums) : capacity(capacity), futureNums(futureNums) {}

    void get(int value){
        if(cache.find(value) != cache.end()){
            hits++;
        }else{
            if(capacity == 0){

            }else{
                if(cache.size() >= capacity){
                    removeElm(cache, map_of_freq);
                }
                cache[value]++;
            }
        }
    }

    int hitsRet(){
        return hits;
    }
private:
    int capacity  = 0;
    int hits = 0;

    std::unordered_map<int, int> cache;
    std::unordered_map<int, int> map_of_freq;
    std::vector<int> futureNums;

    void rateFreq(std::unordered_map<int, int> map_of_freq, std::vector<int> futureNums){
        for(const auto num: futureNums){
            map_of_freq[num]++;
        }
    }

    void removeElm(std::unordered_map<int, int> cache, std::unordered_map<int, int> map_of_freq){
        int minFreq = 1000;
        int minNum = 0;

        for(const auto cell: cache){
            int curFreq = map_of_freq[cell.second];
            if(curFreq < minFreq){
                minFreq = curFreq;
                minNum = cell.first;
            }
        }

        cache.erase(minNum);
    }
};

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
    std::vector<int> nums = {5, 5, 5, 5, 5};
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
