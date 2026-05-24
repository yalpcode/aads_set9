#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "sort_metrics.hpp"
#include "string_quicksort.hpp"

void MSBRadixSort(std::vector<std::string>& a, bool withQuick,
                  SortStats& stats);
void MSBRadixSort(std::vector<std::string>& a, bool withQuick = false);
