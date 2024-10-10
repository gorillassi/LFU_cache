#include "IdealCache.h"

template<typename T>
IdealCache<T>::IdealCache(int capacity, const std::vector<T>& elements) : capacity(capacity), elements(elements), hits(0) {}

template<typename T>
void IdealCache<T>::fillMapOfUse(std::vector<T>& elements) {
    for (int i = 0; i < elements.size(); i++) {
        if (map_of_indexes.find(elements[i]) == map_of_indexes.end()) {
            map_of_indexes[elements[i]] = std::queue<int>();
        }
        map_of_indexes[elements[i]].push(i);
    }
}

template<typename T>
T IdealCache<T>::removeLeastLikely(T value) {
    int farthest_ind = -1;
    T farthest_elem;

    for (auto it = cache.begin(); it != cache.end(); it++) {
        T curr_elem = it->first;
        std::queue<int> curr_list = map_of_indexes[it->first];

        if (curr_list.empty()) {
            return curr_elem;
        }

        if (curr_list.front() > farthest_ind) {
            farthest_ind = curr_list.front();
            farthest_elem = curr_elem;
        }
    }
    
    std::queue<int> new_elem_list = map_of_indexes[value];

    if (new_elem_list.empty() || new_elem_list.front() > farthest_ind) {
        return value;
    }

    return farthest_elem;
}

template<typename T>
void IdealCache<T>::processStream(std::vector<T>& elements) {
    fillMapOfUse(elements);

    for (int i = 0; i < elements.size(); i++) {
        T value = elements[i];

        if (!map_of_indexes[value].empty()) {
            map_of_indexes[value].pop();
        }
        if (cache.find(value) != cache.end()) {
            hits++;
            continue;
        }
        if (cache.size() < capacity) {
            put(value);
        } else {
            T curr_elem = removeLeastLikely(value);

            if (curr_elem == value) {
                continue;
            }
            cache.erase(curr_elem);
            put(value);
        }
    }  
}

template<typename T>
void IdealCache<T>::put(T value) {
    cache[value] = 0; 
}

template<typename T>
int IdealCache<T>::hitret() {
    return hits;
}

template class IdealCache<int>;
