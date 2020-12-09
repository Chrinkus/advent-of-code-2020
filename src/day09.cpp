#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Read_input.hpp"

using Index = std::size_t;      // I really dislike typing this

int find_weakness(const std::vector<int>& vi, const int preamble = 25)
{
    bool found_pair = false;
    for (Index i = preamble, j = 0, k = 1; i < vi.size(); ++i) {
        for (j = i - preamble; j < i - 1; ++j) {
            for (k = j + 1; k < i; ++k) {
                if ((found_pair = vi[i] == vi[j] + vi[k]))
                    break;
            }
            if (found_pair)
                break;
        }
        if (!found_pair)
            return vi[i];
    }
}

int break_encryption(const std::vector<int>& vi, const int target)
{
    for (Index gap = 1; gap < vi.size(); ++gap) {
        for (auto it = std::begin(vi), jt = std::next(it, gap);
                jt < std::end(vi); ++it, ++jt) {
                    if (std::accumulate(it, std::next(jt), 0) == target) {
                        auto min = *std::min_element(it, std::next(jt));
                        auto max = *std::max_element(it, std::next(jt));
                        return min + max;
                    }
                }
    }
}

int main()
{
    const auto input = read_input<int>();

    const auto part1 = find_weakness(input, 25);
    const auto part2 = break_encryption(input, part1);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';
}
