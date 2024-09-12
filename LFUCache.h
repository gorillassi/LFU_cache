#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <vector>

class LFUCache {
public:
    LFUCache(int capacity);
    void get(int value);
    void put(int value);
    int hitsRet();

private:
    int capacity;
    int minFreq;
    int hits;

    std::unordered_map<int, int> cache; 
    std::unordered_map<int, int> freq;  
    std::unordered_map<int, std::vector<int>> map_of_nums_freq; 

    void incFreq(int value);
    void removeElm();
};

#endif // LFUCACHE_H
