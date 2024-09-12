#include "LFUCache.h"
#include <algorithm>

LFUCache::LFUCache(int capacity) : capacity(capacity), minFreq(0), hits(0) {}

void LFUCache::get(int value) {
    if (cache.find(value) != cache.end()){
        hits++; 
        incFreq(value);
    } else {
        put(value);
    }
}

void LFUCache::put(int value) {
    if (capacity == 0){
        return;
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

int LFUCache::hitsRet() {
    return hits;
}

void LFUCache::incFreq(int value) {
    int currentFreq = freq[value];
    freq[value]++;

    map_of_nums_freq[currentFreq].erase(std::remove(map_of_nums_freq[currentFreq].begin(),
                                                    map_of_nums_freq[currentFreq].end(), value),
                                                    map_of_nums_freq[currentFreq].end());

    map_of_nums_freq[currentFreq + 1].push_back(value);

    if(map_of_nums_freq[currentFreq].empty() && currentFreq == minFreq) {
        minFreq++;
    }
}

void LFUCache::removeElm() {
    if (!map_of_nums_freq[minFreq].empty()) {
        int remEl = map_of_nums_freq[minFreq].front();
        map_of_nums_freq[minFreq].erase(map_of_nums_freq[minFreq].begin());
        cache.erase(remEl);
        freq.erase(remEl);
    }
}
