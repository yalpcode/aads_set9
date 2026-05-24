#include "string_mergesort.hpp"

namespace {

std::pair<int, size_t> lcpCompare(const std::string& a, const std::string& b,
                                  size_t k, SortStats* stats) {
    size_t n = std::min(a.size(), b.size());

    for (size_t i = k; i < n; ++i) {
        if (stats != nullptr) {
            ++stats->char_comparisons;
        }
        if (a[i] > b[i]) {
            return {1, i};
        }
        if (a[i] < b[i]) {
            return {-1, i};
        }
    }

    if (a.size() < b.size()) {
        return {-1, n};
    }
    if (a.size() > b.size()) {
        return {1, n};
    }

    return {0, n};
}

std::vector<std::pair<std::string, size_t>> stringMerge(
    std::vector<std::pair<std::string, size_t>> p,
    std::vector<std::pair<std::string, size_t>> q, SortStats* stats) {
    size_t m = p.size();
    size_t f = q.size();

    std::vector<std::pair<std::string, size_t>> r;
    r.reserve(m + f);
    size_t i = 0;
    size_t j = 0;
    while (i < m && j < f) {
        if (p[i].second > q[j].second) {
            r.push_back(std::move(p[i]));
            ++i;
        } else if (p[i].second < q[j].second) {
            r.push_back(std::move(q[j]));
            ++j;
        } else {
            auto [x, h] =
                lcpCompare(p[i].first, q[j].first, p[i].second, stats);
            if (x == -1) {
                r.push_back(std::move(p[i]));
                q[j].second = h;
                ++i;
            } else {
                r.push_back(std::move(q[j]));
                p[i].second = h;
                ++j;
            }
        }
    }
    for (; i < m; ++i) {
        r.push_back(std::move(p[i]));
    }
    for (; j < f; ++j) {
        r.push_back(std::move(q[j]));
    }

    return r;
}

std::vector<std::pair<std::string, size_t>> stringMergeSort(
    std::vector<std::string>& a, int l, int r, SortStats* stats) {
    if (r - l <= 1) {
        return {{a[l], 0}};
    }

    int mid = l + (r - l) / 2;
    auto p = stringMergeSort(a, l, mid, stats);
    auto q = stringMergeSort(a, mid, r, stats);
    return stringMerge(std::move(p), std::move(q), stats);
}

}  // namespace

void stringMergeSort(std::vector<std::string>& a, SortStats& stats) {
    if (a.empty()) {
        return;
    }

    auto p = stringMergeSort(a, 0, a.size(), &stats);
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = std::move(p[i].first);
    }
}

void stringMergeSort(std::vector<std::string>& a) {
    if (a.empty()) {
        return;
    }

    auto p = stringMergeSort(a, 0, a.size(), nullptr);
    for (size_t i = 0; i < a.size(); ++i) {
        a[i] = std::move(p[i].first);
    }
}
