#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    void put(int value) {
        if (cache.find(value) != cache.end()) {
            hits++;
            cache[value]++;
            incFreq(value);
        } else {
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
    int capacity = 0;
    int minFreq = 0;
    int hits = 0; 

    std::unordered_map<int, int> cache; 
    std::unordered_map<int, int> freq; 
    std::unordered_map<int, std::vector<int>> map_of_nums_freq; 

    void incFreq(int value) {
        int frequence = freq[value];
        freq[value]++;
        
        if (!map_of_nums_freq[frequence].empty()) {
            map_of_nums_freq[frequence].erase(std::remove(map_of_nums_freq[frequence].begin(), map_of_nums_freq[frequence].end(), value), map_of_nums_freq[frequence].end());
        }

        map_of_nums_freq[frequence + 1].push_back(value);

        if (map_of_nums_freq[frequence].empty() && frequence == minFreq) {
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

int main() {
    int size_of_cache, n, temp  = 0;
    std::cin >> size_of_cache >> n;

    std::unordered_map<int, int> perfNums;
    std::vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        perfNums[temp]++;
        nums[i] = temp;
    }
    
    LFUCache lfu(size_of_cache);

    for (int i = 0; i < n; i++) {
        lfu.put(nums[i]);
    }
    
    std::cout << "LFU: " << lfu.hitsRet() << "\n";

    return 0;
}
