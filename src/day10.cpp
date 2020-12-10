#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>               // for timing solution

#include "Read_input.hpp"       // simple lib for reading input from istreams

auto find_joltage_dist(const std::vector<int>& vi)
{
    auto count1 = 0, count3 = 0, prev = 0;
    for (auto it = std::begin(vi); it != std::end(vi); ++it) {
        switch (*it - prev) {
            case 1:
                ++count1;
                break;
            case 2:
                break;      // don't count 2's
            case 3:
                ++count3;
                break;
        }
        prev = *it;
    }
    ++count3;       // last jump is always a '3'

    return count1 * count3;
}

auto count_combinations(const std::vector<int>& vi)
{
    std::int64_t ways = 1;
    std::vector<int> distances;
    int prev = 0;
    for (const auto& i : vi) {
        distances.push_back(i - prev);
        prev = i;
    }
    int ones = 0;           // consecutive 1's add possible combinations
    for (const auto& d : distances) {
        switch (d) {
        case 1:
            ++ones;
            break;
        case 3:
            if (ones > 1) {
                // combinations seem to increase by a factor of 2
                // minus the amount by which ones exceed jump dist (3)
                ways *= (1 << (ones - 1)) - (ones > 3 ? ones - 3 : 0);
            }
            ones = 0;       // reset ones on any 3
            break;
        }
    }
    if (ones > 0) {         // was missing last batch of combinations
        ways *= (1 << (ones - 1)) - (ones > 3 ? ones - 3 : 0);
    }
    return ways;
}

int main()
{
    // start of timing
    auto start = std::chrono::steady_clock::now();

    const auto input = read_input_and_sort<int>();

    const auto part1 = find_joltage_dist(input);
    const auto part2 = count_combinations(input);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    // end of timing and report
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << "Time: " << time.count() << '\n';
}
