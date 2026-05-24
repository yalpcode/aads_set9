#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "sort_metrics.hpp"

void mergeSort(std::vector<std::string>& a, SortStats& stats);
void mergeSort(std::vector<std::string>& a);
