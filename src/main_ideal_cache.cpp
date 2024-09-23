#include <iostream>
#include "IdealCache.h"

int main(int argc, char **argv) {
    int size, n;
    std::cin >> size >> n;
    std::vector<int> nums(n);

    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }

    IdealCache<int> idc(size, nums); 

    idc.processStream();

    std::cout << idc.hitret() << "\n";

    return 0;
}
