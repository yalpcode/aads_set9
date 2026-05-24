#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include <vector>

#include "sort_metrics.hpp"

void stringQuickSort(std::vector<std::string>& a, std::size_t depth,
                     SortStats& stats);
void stringQuickSort(std::vector<std::string>& a, std::size_t depth);
void stringQuickSort(std::vector<std::string>& a, SortStats& stats);
void stringQuickSort(std::vector<std::string>& a);
