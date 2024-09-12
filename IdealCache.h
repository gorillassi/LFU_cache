#ifndef IDEALCACHE_H
#define IDEALCACHE_H

#include <unordered_map>
#include <vector>

class IdealCache {
public:
    IdealCache(int capacity, std::vector<int>& futureNums);
    void get(int value);
    int hitsRet();

private:
    int capacity;
    int hits;

    std::unordered_map<int, int> cache;
    std::unordered_map<int, int> map_of_freq;
    std::vector<int> futureNums;

    void rateFreq(std::unordered_map<int, int>& map_of_freq, const std::vector<int>& futureNums);
    void removeElm(std::unordered_map<int, int>& cache, std::unordered_map<int, int>& map_of_freq);
};

#endif // IDEALCACHE_H
