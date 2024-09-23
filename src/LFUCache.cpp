#include "LFUCache.h"

template <typename T>
LFUCache<T>::LFUCache(int capacity) : capacity(capacity), minFreq(0), hits(0), map_of_nums_freq({{}}), num_elements(0) {}

template <typename T>
void LFUCache<T>::get(T value) {
    if (cache.find(value) != cache.end()){
        hits++; 
        incFreq(value);
    } else {
        put(value);
    }
}

template <typename T>
void LFUCache<T>::put(T value) {
    if (capacity == 0){
        return;
    }
    cache[value].first = value;
    incFreq(value);

    if(num_elements == cache.size()){
        removeElm();
    }

    cache[value] = std::make_pair(value, 0);
    map_of_nums_freq[0].push_back(value);
    num_elements++;
}

template <typename T>
int LFUCache<T>::hitsRet() {
    return hits;
}

template <typename T>
void LFUCache<T>::incFreq(T value) {
    cache[value].second++;

    while(map_of_nums_freq.size() <= cache[value].second){
        map_of_nums_freq.push_back(std::deque<T>());
    }

    map_of_nums_freq[cache[value].second].push_back(value);
}

template <typename T>
void LFUCache<T>::removeElm() {
    bool success = false;

    for (int i = 0; i < map_of_nums_freq.size() && !success; i++) {
        while (!map_of_nums_freq[i].empty() && !success) {
            if(cache[map_of_nums_freq[i].front()].second == i){
                success = true;
                cache.erase(map_of_nums_freq[i].front());
                num_elements--;
            }
            map_of_nums_freq[i].pop_front();
        }     
    }  
}

template class LFUCache<int>;  
