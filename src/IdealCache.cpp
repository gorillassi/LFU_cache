#include "IdealCache.h"

IdealCache::IdealCache(size_t capacity, const std::vector<int>& elements) 
    : capacity(capacity), elements(elements), index(0) {
    while (index < elements.size() && cache.size() < capacity) {
        put(elements[index++]);
    }
}

void IdealCache::put(int key) {
    if (cache.find(key) != cache.end()) {
        hits++;
    }

    if (cache.size() == capacity) {
        removeLeastLikely();
    }

    cache[key] = true; 
}

int IdealCache::get(int key) {
    return cache.find(key) != cache.end() ? key : -1;
}

void IdealCache::processStream() {
    while (index < elements.size()) {
        put(elements[index++]); 
    }
}

int IdealCache::hitret() const {
    return hits;
}

void IdealCache::removeLeastLikely() {
    int furthestKey = -1;
    size_t furthestIndex = -1;

    for (const auto& entry : cache) {
        int key = entry.first;

        size_t nextIndex = findNextIndex(key);
        if (nextIndex > furthestIndex) {
            furthestIndex = nextIndex;
            furthestKey = key;
        }
    }

    cache.erase(furthestKey);
}

size_t IdealCache::findNextIndex(int key) {

    for (size_t i = index; i < elements.size(); ++i) {
        if (elements[i] == key) {
            return i;
        }
    }
    return elements.size(); 
}
