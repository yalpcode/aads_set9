#include "random_stream_gen.hpp"

RandomStreamGen::RandomStreamGen(std::size_t min_len, std::size_t max_len,
                                 std::uint64_t seed, std::string alphabet)
    : min_len(min_len),
      max_len(max_len),
      rng(seed),
      alphabet(alphabet),
      len_dist(min_len, max_len),
      char_dist(0, alphabet.size() - 1) {
}

std::string RandomStreamGen::next() {
    std::size_t n = len_dist(rng);
    std::string res;
    for (std::size_t i = 0; i < n; ++i) {
        res.push_back(alphabet[char_dist(rng)]);
    }

    return res;
}

RandomStreamGen::Chunk RandomStreamGen::operator()(std::size_t total,
                                                   double step) {
    Chunk chunk;
    if (step <= 0.0 || total == 0) {
        return chunk;
    }

    std::size_t cnt_step =
        static_cast<std::size_t>(std::ceil(static_cast<double>(total) * step));
    if (cnt_step == 0) {
        cnt_step = 1;
    }
    while (total != 0) {
        chunk.items.push_back(std::vector<std::string>());
        for (size_t i = 0; i < std::min(total, cnt_step); ++i) {
            chunk.items.back().push_back(next());
        }
        total -= std::min(total, cnt_step);
    }

    return chunk;
}

RandomStreamGen::Chunk& RandomStreamGen::Chunk::operator>>(
    std::vector<std::string>& words) {
    if (items.empty()) {
        words = std::vector<std::string>();
    } else {
        words = items.back();
        items.pop_back();
    }

    return *this;
}

RandomStreamGen::Chunk::operator bool() const {
    return !items.empty();
}

std::vector<std::string> RandomStreamGen::randomArray(std::size_t total) {
    std::vector<std::string> words;
    words.reserve(total);
    for (std::size_t i = 0; i < total; ++i) {
        words.push_back(next());
    }
    return words;
}

std::vector<std::string> RandomStreamGen::reverseSortedArray(
    std::size_t total) {
    auto words = randomArray(total);
    std::sort(words.begin(), words.end(), std::greater<std::string>());
    return words;
}

std::vector<std::string> RandomStreamGen::almostSortedArray(std::size_t total) {
    auto words = randomArray(total);
    std::sort(words.begin(), words.end());

    std::uniform_int_distribution<std::size_t> index_dist(0, total - 1);
    std::size_t swaps = std::max<std::size_t>(1, total / 20);
    for (std::size_t i = 0; i < swaps; ++i) {
        std::swap(words[index_dist(rng)], words[index_dist(rng)]);
    }

    return words;
}
