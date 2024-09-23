#include <iostream>
#include <chrono>
#include "LFUCache.h"

int main(int argc, char **argv) {
    int size, n;
    std::cin >> size >> n;
    std::vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> nums[i];
    }

    LFUCache<int> lfu(size);  // Используем шаблонный класс
    //auto start = std::chrono::high_resolution_clock::now();

    for (const auto &num : nums) {
        lfu.get(num);
    }

    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << lfu.hitsRet() << "\n";
    //std::cout << "Время выполнения: " << elapsed.count() << " миллисекунд\n";

    return 0;
}
