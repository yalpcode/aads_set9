#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "random_stream_gen.hpp"
#include "string_sort_tester.hpp"

namespace {

constexpr std::size_t kMaxSize = 3000;

std::string csvEscape(const std::string& value) {
    std::string escaped = "\"";
    for (char ch : value) {
        if (ch == '"') {
            escaped += "\"\"";
        } else {
            escaped += ch;
        }
    }
    escaped += '"';
    return escaped;
}

}  // namespace

int main() {
    std::filesystem::create_directories("data");

    RandomStreamGen generator(10, 200, 20260524);
    StringSortTester tester;
    std::vector<std::pair<std::string, std::vector<std::string>>> datasets = {
        {"random", generator.randomArray(kMaxSize)},
        {"reverse_sorted", generator.reverseSortedArray(kMaxSize)},
        {"almost_sorted", generator.almostSortedArray(kMaxSize)},
    };

    std::ofstream csv("data/results.csv");
    csv << "dataset,size,algorithm,time_us,char_comparisons\n";

    for (const auto& [dataset_name, full_data] : datasets) {
        for (std::size_t size = 100; size <= kMaxSize; size += 100) {
            std::vector<std::string> sample(full_data.begin(),
                                            full_data.begin() + size);
            auto results = tester.runAll(sample);

            for (const auto& [algorithm, metrics] : results) {
                csv << csvEscape(dataset_name) << ',' << size << ','
                    << csvEscape(algorithm) << ',' << metrics.micros << ','
                    << metrics.char_comparisons << '\n';
            }

            std::cout << "done: " << dataset_name << " size=" << size << '\n';
        }
    }

    std::cout << "Saved data/results.csv\n";
    return 0;
}
