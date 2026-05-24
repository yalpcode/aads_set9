#include "string_sort_tester.hpp"

#include <algorithm>
#include <chrono>
#include <stdexcept>

#include "mergesort.hpp"
#include "msb_radix_sort.hpp"
#include "quicksort.hpp"
#include "sort_metrics.hpp"
#include "string_mergesort.hpp"
#include "string_quicksort.hpp"

namespace {

template <class Sorter>
StringSortTester::Metrics measure(const std::vector<std::string>& source,
                                  const std::string& name, Sorter sorter) {
    auto data = source;
    SortStats stats;

    auto started = std::chrono::steady_clock::now();
    sorter(data, stats);
    auto finished = std::chrono::steady_clock::now();

    if (!std::is_sorted(data.begin(), data.end())) {
        throw std::runtime_error(name + " result is not sorted");
    }

    return {std::chrono::duration_cast<std::chrono::microseconds>(finished -
                                                                  started)
                .count(),
            stats.char_comparisons};
}

}  // namespace

std::vector<StringSortTester::Result> StringSortTester::runAll(
    const std::vector<std::string>& source) const {
    return {
        {"standard_quicksort", testQuickSort(source)},
        {"standard_mergesort", testMergeSort(source)},
        {"string_quicksort", testStringQuickSort(source)},
        {"string_mergesort", testStringMergeSort(source)},
        {"msd_radix_sort", testMSDRadixSort(source)},
        {"msd_radix_sort_with_quick", testMSDRadixSortWithQuick(source)},
    };
}

StringSortTester::Metrics StringSortTester::testQuickSort(
    const std::vector<std::string>& source) const {
    return measure(source, "standard_quicksort",
                   [](auto& a, auto& s) { quickSort(a, s); });
}

StringSortTester::Metrics StringSortTester::testMergeSort(
    const std::vector<std::string>& source) const {
    return measure(source, "standard_mergesort",
                   [](auto& a, auto& s) { mergeSort(a, s); });
}

StringSortTester::Metrics StringSortTester::testStringQuickSort(
    const std::vector<std::string>& source) const {
    return measure(source, "string_quicksort",
                   [](auto& a, auto& s) { stringQuickSort(a, s); });
}

StringSortTester::Metrics StringSortTester::testStringMergeSort(
    const std::vector<std::string>& source) const {
    return measure(source, "string_mergesort",
                   [](auto& a, auto& s) { stringMergeSort(a, s); });
}

StringSortTester::Metrics StringSortTester::testMSDRadixSort(
    const std::vector<std::string>& source) const {
    return measure(source, "msd_radix_sort",
                   [](auto& a, auto& s) { MSBRadixSort(a, false, s); });
}

StringSortTester::Metrics StringSortTester::testMSDRadixSortWithQuick(
    const std::vector<std::string>& source) const {
    return measure(source, "msd_radix_sort_with_quick",
                   [](auto& a, auto& s) { MSBRadixSort(a, true, s); });
}
