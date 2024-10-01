#pragma once

#include <unordered_map>
#include <list>

template <typename T>
struct Node {
public:
    Node(T value, int freq) : value(value), freq(freq) {}

    T value;
    int freq;
};

template <typename T>
class LFUCache {
public:
    LFUCache(int capacity);
    void get(T value);
    void put(T value);
    int hitsRet();

private:
    int capacity;
    int min_freq;
    int hits;

    std::unordered_map<T, typename std::list<Node<T>>::iterator> cache; 
    std::unordered_map<int, std::list<Node<T>>> map_of_nums_freq;

    void incFreq(typename std::list<Node<T>>::iterator node);
    void delFreqList(int freq);
    void removeElm();
};
