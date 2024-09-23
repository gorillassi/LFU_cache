#include "IdealCache.h"

template<typename T>
IdealCache<T>::IdealCache(size_t capacity, const std::vector<T>& elements) 
    : capacity(capacity), elements(elements), index(0) {
    while (index < elements.size() && cache.size() < capacity) {
        put(elements[index++]);
    }
}

template<typename T>
void IdealCache<T>::put(T key) {
    if (cache.find(key) != cache.end()) {
        hits++;
    }

    if (cache.size() == capacity) {
        removeLeastLikely();
    }

    cache[key] = true; 
}

template<typename T>
T IdealCache<T>::get(T key) {
    return cache.find(key) != cache.end() ? key : T(); // Возвращаем T(), если не найден
}

template<typename T>
void IdealCache<T>::processStream() {
    while (index < elements.size()) {
        put(elements[index++]); 
    }
}

template<typename T>
int IdealCache<T>::hitret() const {
    return hits;
}

template<typename T>
void IdealCache<T>::removeLeastLikely() {
    T furthestKey;
    size_t furthestIndex = -1;

    for (const auto& entry : cache) {
        T key = entry.first;

        size_t nextIndex = findNextIndex(key);
        if (nextIndex > furthestIndex) {
            furthestIndex = nextIndex;
            furthestKey = key;
        }
    }

    cache.erase(furthestKey);
}

template<typename T>
size_t IdealCache<T>::findNextIndex(T key) {
    for (size_t i = index; i < elements.size(); ++i) {
        if (elements[i] == key) {
            return i;
        }
    }
    return elements.size(); 
}
