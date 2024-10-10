#pragma once

#include <vector>
#include <queue>
#include <unordered_map>
#include <cstddef>

template<typename T>
class IdealCache {
public:
    IdealCache(int capacity, const std::vector<T>& elements);
    
    T get(T key);
    int hitret();
    void processStream(std::vector<T>& elements);

private:
    int capacity;
    int hits = 0;

    std::vector<T> elements;
    std::unordered_map<T, std::queue<int>> map_of_indexes;
    std::unordered_map<T, int> cache;

    void fillMapOfUse(std::vector<T>& elements);
    T removeLeastLikely(T value);
    void put(T value);
};
