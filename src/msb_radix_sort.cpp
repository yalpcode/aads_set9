#include "msb_radix_sort.hpp"

#include "random_stream_gen.hpp"

namespace {

const std::string alphabet = RandomStreamGen::sortedAlphabet();

std::unordered_map<char, size_t> makeConv() {
    std::unordered_map<char, size_t> conv;
    for (size_t i = 0; i < alphabet.size(); ++i) {
        conv[alphabet[i]] = i;
    }
    return conv;
}

const std::unordered_map<char, size_t> conv2al = makeConv();

std::vector<std::string> MSBRadixSort(std::vector<std::string> a, size_t pr,
                                      bool withQuick, SortStats* stats) {
    if (withQuick && a.size() < alphabet.size()) {
        if (stats == nullptr) {
            stringQuickSort(a, pr);
        } else {
            stringQuickSort(a, pr, *stats);
        }
        return a;
    }

    if (a.size() <= 1) {
        return a;
    }

    std::vector<std::string> r, r_excl;
    r.reserve(a.size());
    r_excl.reserve(a.size());

    for (auto& s : a) {
        if (s.size() == pr) {
            r_excl.push_back(std::move(s));
        } else {
            r.push_back(std::move(s));
        }
    }

    if (r.empty()) {
        return r_excl;
    }

    std::vector<std::vector<std::string>> ri(alphabet.size());
    for (auto& s : r) {
        ri[conv2al.at(s[pr])].push_back(std::move(s));
    }

    for (size_t i = 0; i < alphabet.size(); ++i) {
        ri[i] = MSBRadixSort(std::move(ri[i]), pr + 1, withQuick, stats);
    }

    std::vector<std::string> res;
    res.reserve(r_excl.size() + r.size());

    res.insert(res.end(), std::make_move_iterator(r_excl.begin()),
               std::make_move_iterator(r_excl.end()));
    for (auto& el : ri) {
        res.insert(res.end(), std::make_move_iterator(el.begin()),
                   std::make_move_iterator(el.end()));
    }

    return res;
}

}  // namespace

void MSBRadixSort(std::vector<std::string>& a, bool withQuick,
                  SortStats& stats) {
    a = MSBRadixSort(std::move(a), 0, withQuick, &stats);
}

void MSBRadixSort(std::vector<std::string>& a, bool withQuick) {
    a = MSBRadixSort(std::move(a), 0, withQuick, nullptr);
}
