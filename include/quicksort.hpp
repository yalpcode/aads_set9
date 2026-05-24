#pragma once

#include <random>
#include <string>
#include <vector>

#include "sort_metrics.hpp"

void quickSort(std::vector<std::string>& a, SortStats& stats);
void quickSort(std::vector<std::string>& a);
