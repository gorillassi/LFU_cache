#pragma once

#include <unordered_map>
#include <deque>
#include <vector>

template <typename T>
class LFUCache {
public:
    LFUCache(int capacity);
    void get(T value);
    void put(T value);
    int hitsRet();

private:
    int capacity;
    int num_elements;
    int minFreq;
    int hits;

    std::unordered_map<T, std::pair<T, int>> cache; 
    std::vector<std::deque<T>> map_of_nums_freq;

    void incFreq(T value);
    void removeElm();
};

template <typename T>
void incFreq(LFUCache<T>& cache, T value);

template <typename T>
void removeElm(LFUCache<T>& cache);
