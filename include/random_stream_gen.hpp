#pragma once

#include <algorithm>
#include <cmath>
#include <random>
#include <string>
#include <vector>

class RandomStreamGen {
 public:
    struct Chunk {
        std::vector<std::vector<std::string>> items;

        Chunk& operator>>(std::vector<std::string>& words);

        operator bool() const;
    };

    explicit RandomStreamGen(std::size_t min_len = 1, std::size_t max_len = 30,
                             std::uint64_t seed = std::random_device{}(),
                             std::string alphabet = defaultAlphabet());

    std::string next();

    Chunk operator()(std::size_t total, double step = 1.0);

    static std::string defaultAlphabet() {
        const std::string letters =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        const std::string digits = "0123456789";
        const std::string others = "!@#%:;^&*()-.";
        return letters + digits + others;
    }

    static std::string sortedAlphabet() {
        return "!#%&()*-.0123456789:;@ABCDEFGHIJKLMNOPQRSTUVWXYZ^"
               "abcdefghijklmnopqrstuvwxyz";
    }

    std::vector<std::string> randomArray(std::size_t total);
    std::vector<std::string> reverseSortedArray(std::size_t total);
    std::vector<std::string> almostSortedArray(std::size_t total);

 private:
    std::size_t min_len, max_len;
    std::mt19937 rng;
    std::string alphabet;

    std::uniform_int_distribution<std::size_t> len_dist;
    std::uniform_int_distribution<std::size_t> char_dist;
};
