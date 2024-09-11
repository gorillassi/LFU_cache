#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>

class LFUCache {
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if(cache.find(key) != cache.end()){
            incFreq(key);
            return cache[key];
        } else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end()){
            cache[key] = value;
            hits++;
            incFreq(key);
        } else{
            if(cache.size() >= capacity){
                removeElm();
            } 
            cache[key] = value;
            freq[key] = 1;
            map_of_nums_freq[1].push_back(key);
            minFreq = 1;
        }
    }

private:
    int capacity = 0;
    int minFreq = 0;
    int hits = 0; 
    std::unordered_map<int, int> cache;
    std::unordered_map<int, int> freq;
    std::unordered_map<int, std::vector<int>> map_of_nums_freq;

    void incFreq(int key){
        int frequence = freq[key];
        freq[key]++;
        map_of_nums_freq[frequence].erase(std::remove(map_of_nums_freq[frequence].begin(), map_of_nums_freq[frequence].end(), key), map_of_nums_freq[frequence].end());
        map_of_nums_freq[frequence+1].push_back(key);
        if(map_of_nums_freq[frequence].empty() && frequence == minFreq){
            minFreq++;
        }
    }

    void removeElm(){
        int remEl = map_of_nums_freq[minFreq].front();
        map_of_nums_freq[minFreq].erase(map_of_nums_freq[minFreq].begin());
        cache.erase(remEl);
        freq.erase(remEl);
    }

    int hitsRet(){
        return hits;
    }
};

int main(){
    int size_of_cache, n, temp  = 0;
    std::cin >> size_of_cache >> n;

    std::unordered_map<int, int> nums;

    for (int i = 0; i < n; i++)
    {
        std::cin >> temp;
        nums[temp]++;     
    }
    
    LFUCache lfu (size_of_cache);
    
    return 0;
}