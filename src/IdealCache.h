#ifndef IDEALCACHE_H
#define IDEALLCACHE_H

#include <vector>
#include <unordered_map>
#include <cstddef>

class IdealCache {
public:
    IdealCache(size_t capacity, const std::vector<int>& elements);
    
    void put(int key);
    int get(int key);
    void processStream();
    int hitret() const;

private:
    size_t capacity;
    std::unordered_map<int, bool> cache; 
    const std::vector<int>& elements;  
    size_t index;              
    int hits = 0;

    void removeLeastLikely();
    size_t findNextIndex(int key);
};

#endif // IDEALCACHE_H
