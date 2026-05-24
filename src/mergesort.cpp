#include "mergesort.hpp"

void Merge(std::vector<std::string>& a, int l, int mid, int r,
           SortStats& stats) {
    std::vector<std::string> c;
    c.reserve(r - l + 1);
    int i = l;
    int j = mid;
    while (i < mid && j < r) {
        if (stringLess(a[i], a[j], stats)) {
            c.push_back(a[i]);
            ++i;
        } else {
            c.push_back(a[j]);
            ++j;
        }
    }
    for (; i < mid; ++i) {
        c.push_back(a[i]);
    }
    for (; j < r; ++j) {
        c.push_back(a[j]);
    }
    for (int i = l; i < r; ++i) {
        a[i] = c[i - l];
    }
}

void MergeSort(std::vector<std::string>& a, int l, int r, SortStats& stats) {
    if (r - l <= 15) {
        for (int i = l; i < r - 1; ++i) {
            int j = 0;
            while (i - j >= l && stringLess(a[i + 1 - j], a[i - j], stats)) {
                std::swap(a[i - j], a[i + 1 - j]);
                ++j;
            }
        }
        return;
    }

    int mid = l + (r - l) / 2;
    MergeSort(a, l, mid, stats);
    MergeSort(a, mid, r, stats);
    Merge(a, l, mid, r, stats);
}

void mergeSort(std::vector<std::string>& a, SortStats& stats) {
    MergeSort(a, 0, a.size(), stats);
}

void mergeSort(std::vector<std::string>& a) {
    SortStats stats;
    mergeSort(a, stats);
}
