#pragma once

#include <vector>
#include <unordered_map>
#include <cstddef>

template<typename T>
class IdealCache {
public:
    IdealCache(size_t capacity, const std::vector<T>& elements);
    
    void put(T key);
    T get(T key);
    void processStream();
    int hitret() const;

private:
    size_t capacity;
    std::unordered_map<T, bool> cache; 
    const std::vector<T>& elements;  
    size_t index;              
    int hits = 0;

    void removeLeastLikely();
    size_t findNextIndex(T key);
};

#include "IdealCache.tpp" 
