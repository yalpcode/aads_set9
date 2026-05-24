#include "quicksort.hpp"

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int partition(std::vector<std::string>& a, int l, int r,
              const std::string& pivot, SortStats& stats) {
    int i = l, j = r - 1;
    while (i <= j) {
        while (stringLess(a[i], pivot, stats)) {
            ++i;
        }
        while (stringLess(pivot, a[j], stats)) {
            --j;
        }
        if (i <= j) {
            std::swap(a[i], a[j]);
            ++i;
            --j;
        }
    }

    return i;
}

void quickSort(std::vector<std::string>& a, int l, int r, SortStats& stats) {
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

    std::uniform_int_distribution<int> i_dist(l, r - 1);

    std::string pivot = a[i_dist(rng)];
    int p = partition(a, l, r, pivot, stats);
    quickSort(a, l, p, stats);
    quickSort(a, p, r, stats);
}

void quickSort(std::vector<std::string>& a, SortStats& stats) {
    quickSort(a, 0, a.size(), stats);
}

void quickSort(std::vector<std::string>& a) {
    SortStats stats;
    quickSort(a, stats);
}
