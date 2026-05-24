#pragma once

#include <algorithm>
#include <cstdint>
#include <string>

struct SortStats {
    std::uint64_t char_comparisons = 0;
};

inline int compareStrings(const std::string& lhs, const std::string& rhs,
                          SortStats& stats, std::size_t start = 0) {
    std::size_t n = std::min(lhs.size(), rhs.size());
    for (std::size_t i = start; i < n; ++i) {
        ++stats.char_comparisons;
        if (lhs[i] < rhs[i]) {
            return -1;
        }
        if (lhs[i] > rhs[i]) {
            return 1;
        }
    }
    if (lhs.size() < rhs.size()) {
        return -1;
    }
    if (lhs.size() > rhs.size()) {
        return 1;
    }
    return 0;
}

inline bool stringLess(const std::string& lhs, const std::string& rhs,
                       SortStats& stats) {
    return compareStrings(lhs, rhs, stats) < 0;
}

inline bool stringLessOrEqual(const std::string& lhs, const std::string& rhs,
                              SortStats& stats) {
    return compareStrings(lhs, rhs, stats) <= 0;
}

inline bool countedCharLess(char lhs, char rhs, SortStats& stats) {
    ++stats.char_comparisons;
    return lhs < rhs;
}

inline bool countedCharGreater(char lhs, char rhs, SortStats& stats) {
    ++stats.char_comparisons;
    return lhs > rhs;
}
