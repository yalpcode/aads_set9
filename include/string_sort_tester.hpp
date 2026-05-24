#pragma once

#include <cstdint>
#include <string>
#include <vector>

class StringSortTester {
 public:
    struct Metrics {
        long long micros = 0;
        std::uint64_t char_comparisons = 0;
    };

    using Result = std::pair<std::string, Metrics>;

    std::vector<Result> runAll(const std::vector<std::string>& source) const;

    Metrics testQuickSort(const std::vector<std::string>& source) const;
    Metrics testMergeSort(const std::vector<std::string>& source) const;
    Metrics testStringQuickSort(const std::vector<std::string>& source) const;
    Metrics testStringMergeSort(const std::vector<std::string>& source) const;
    Metrics testMSDRadixSort(const std::vector<std::string>& source) const;
    Metrics testMSDRadixSortWithQuick(
        const std::vector<std::string>& source) const;
};
