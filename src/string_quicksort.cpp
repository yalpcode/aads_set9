#include "string_quicksort.hpp"

namespace {

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::vector<std::string> stringQuickSort(std::vector<std::string> a,
                                         std::size_t pr, SortStats* stats) {
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

    std::uniform_int_distribution<size_t> i_dist(0, r.size() - 1);
    char pivot = r[i_dist(rng)][pr];

    std::vector<std::string> r_less, r_equal, r_great;
    for (auto& s : r) {
        if (stats != nullptr) {
            ++stats->char_comparisons;
        }
        if (s[pr] < pivot) {
            r_less.push_back(std::move(s));
        } else {
            if (stats != nullptr) {
                ++stats->char_comparisons;
            }
            if (s[pr] == pivot) {
                r_equal.push_back(std::move(s));
            } else {
                r_great.push_back(std::move(s));
            }
        }
    }

    r_less = stringQuickSort(std::move(r_less), pr, stats);
    r_equal = stringQuickSort(std::move(r_equal), pr + 1, stats);
    r_great = stringQuickSort(std::move(r_great), pr, stats);

    std::vector<std::string> res;
    res.reserve(r_excl.size() + r_less.size() + r_equal.size() +
                r_great.size());

    res.insert(res.end(), std::make_move_iterator(r_excl.begin()),
               std::make_move_iterator(r_excl.end()));
    res.insert(res.end(), std::make_move_iterator(r_less.begin()),
               std::make_move_iterator(r_less.end()));
    res.insert(res.end(), std::make_move_iterator(r_equal.begin()),
               std::make_move_iterator(r_equal.end()));
    res.insert(res.end(), std::make_move_iterator(r_great.begin()),
               std::make_move_iterator(r_great.end()));

    return res;
}

}  // namespace

void stringQuickSort(std::vector<std::string>& a, std::size_t pr,
                     SortStats& stats) {
    a = stringQuickSort(std::move(a), pr, &stats);
}

void stringQuickSort(std::vector<std::string>& a, std::size_t pr) {
    a = stringQuickSort(std::move(a), pr, nullptr);
}

void stringQuickSort(std::vector<std::string>& a, SortStats& stats) {
    stringQuickSort(a, 0, stats);
}

void stringQuickSort(std::vector<std::string>& a) {
    a = stringQuickSort(std::move(a), 0, nullptr);
}
