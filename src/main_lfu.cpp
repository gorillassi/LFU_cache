#include <iostream>
#include "LFUCache.h"


int main(int argc, char **argv) {
    int size, n;
    std::cin >> size >> n;
    std::vector<int> nums(n);

    for (int i = 0; i < n; i++)
    {
        int temp;
        std::cin >> nums[i];
    }

    LFUCache lfu(size);

    for (const auto &num : nums) {
        lfu.get(num);
    }

    std::cout << lfu.hitsRet() << "\n";

    return 0;
}
