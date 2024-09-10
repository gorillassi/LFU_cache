#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>

int minIndex(const std::unordered_map<int, int>& cells) {
    int minFreq = std::numeric_limits<int>::max();
    int minKey = -1;
    for (const auto& pair : cells) {
        if (pair.second < minFreq) {
            minFreq = pair.second;
            minKey = pair.first;
        }
    }
    return minKey;
}

void LFU(std::unordered_map<int, int>& cells, const std::vector<int>& nums, int& hits, int size) {
    for (int temp : nums) {
        if (cells.size() < size) {
            if (cells.find(temp) != cells.end()) {
                hits++;                
                cells[temp]++;        
            } else {
                cells[temp] = 1;       
            }
        } else {
            if (cells.find(temp) != cells.end()) {
                hits++;              
                cells[temp]++;     
            } else {
                int minKey = minIndex(cells); 
                cells.erase(minKey);
                cells[temp] = 1; 
            }
        }
    }
}

void perfCache(std::unordered_map<int, int>& cells, const std::unordered_map<int, int>& perfnums, const std::vector<int>& nums, int& perfhits, int size) {
    for (int temp : nums) {
        if (cells.size() < size) {
            cells[temp] = 1;
        } else {
            if (cells.find(temp) != cells.end()) {
                perfhits++;          
                cells[temp]++;
            } else {
                int minKey = minIndex(perfnums);
                cells.erase(minKey);
                cells[temp] = 1;   
            }
        }
    }
}

TEST(LFUComparisonTest, CompareHits) {
    int lfuHits = 0;
    int perfHits = 0;
    int size = 3;
    std::vector<int> nums = {1, 2, 2, 3, 1, 4, 1, 4, 2};

    std::unordered_map<int, int> lfuCells;
    std::unordered_map<int, int> perfCells;
    std::unordered_map<int, int> perfNums;

    // Подсчитываем частоты для идеального кэша
    for (int num : nums) {
        perfNums[num]++;
    }

    // Запускаем оба алгоритма
    LFU(lfuCells, nums, lfuHits, size);
    perfCache(perfCells, perfNums, nums, perfHits, size);

    // Проверяем, что количество попаданий в LFU меньше или равно количеству попаданий в идеальном кэше
    EXPECT_LE(lfuHits, perfHits);  
}

TEST(LFUComparisonTest, DifferentAccessPatterns) {
    int lfuHits = 0;
    int perfHits = 0;
    int size = 4;
    std::vector<int> nums = {1, 2, 3, 4, 5, 1, 2, 3, 1, 4, 2, 1}; 

    std::unordered_map<int, int> lfuCells;
    std::unordered_map<int, int> perfCells;
    std::unordered_map<int, int> perfNums;

    // Подсчитываем частоты для идеального кэша
    for (int num : nums) {
        perfNums[num]++;
    }

    // Запускаем оба алгоритма
    LFU(lfuCells, nums, lfuHits, size);
    perfCache(perfCells, perfNums, nums, perfHits, size);

    // Проверяем, что количество попаданий в LFU меньше или равно количеству попаданий в идеальном кэше
    EXPECT_LE(lfuHits, perfHits); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
