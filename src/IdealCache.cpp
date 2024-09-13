#include "IdealCache.h"

IdealCache::IdealCache(int capacity, std::vector<int>& futureNums) : capacity(capacity), futureNums(futureNums), hits(0) {}

void IdealCache::get(int value) {
    if (cache.find(value) != cache.end()) {
        hits++;
    } else {
        if (capacity == 0) {
            return;
        } else {
            if (cache.size() >= capacity) {
                removeElm(cache, map_of_freq);
            }
            cache[value]++;
        }
    }
}

int IdealCache::hitsRet() {
    return hits;
}

void IdealCache::rateFreq(std::unordered_map<int, int>& map_of_freq, const std::vector<int>& futureNums) {
    for (const auto num : futureNums) {
        map_of_freq[num]++;
    }
}

void IdealCache::removeElm(std::unordered_map<int, int>& cache, std::unordered_map<int, int>& map_of_freq) {
    int minFreq = 1000;
    int minNum = 0;

    for (const auto& cell : cache) {
        int curFreq = map_of_freq[cell.second];
        if (curFreq < minFreq) {
            minFreq = curFreq;
            minNum = cell.first;
        }
    }

    cache.erase(minNum);
}
