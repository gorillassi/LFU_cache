#include "LFUCache.h"

template <typename T>
LFUCache<T>::LFUCache(int capacity) : capacity(capacity), min_freq(1), hits(0) {}

template <typename T>
void LFUCache<T>::get(T value) {
    auto it = cache.find(value);
    if (it != cache.end()) {
        hits++;
        incFreq(it->second); 
    } else {
        put(value);
    }
}

template <typename T>
void LFUCache<T>::put(T value) {
    if (capacity == 0) return;

    auto it = cache.find(value);
    if (it != cache.end()) {
        incFreq(it->second); 
        return;
    }

    if (cache.size() >= capacity) {
        removeElm(); 
    }

    Node<T> newNode(value, 1);
    map_of_nums_freq[1].push_front(newNode);
    cache[value] = map_of_nums_freq[1].begin();
    min_freq = 1; 
}

template <typename T>
void LFUCache<T>::incFreq(typename std::list<Node<T>>::iterator node) {
    int freq = node->freq;
    T value = node->value;

    auto& old_freq_list = map_of_nums_freq[freq];
    old_freq_list.erase(node);

    if (old_freq_list.empty()) {
        delFreqList(freq);
    }

    int new_freq = freq + 1;
    map_of_nums_freq[new_freq].emplace_front(value, new_freq);
    cache[value] = map_of_nums_freq[new_freq].begin();
}

template <typename T>
void LFUCache<T>::delFreqList(int freq) {
    map_of_nums_freq.erase(freq);
    if (min_freq == freq) {
        min_freq++;
    }
}

template <typename T>
void LFUCache<T>::removeElm() {
    auto& least_freq_list = map_of_nums_freq[min_freq];
    auto node_del = least_freq_list.back();
    cache.erase(node_del.value);

    least_freq_list.pop_back();

    if (least_freq_list.empty()) {
        delFreqList(min_freq);
    }
}

template <typename T>
int LFUCache<T>::hitsRet() {
    return hits; 
}

template class LFUCache<int>;
