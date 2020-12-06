#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using Declarations = std::vector<std::string>;

auto read_and_sort_input()
{
    Declarations d (1);     // start building from first
    for (std::string line; std::getline(std::cin, line); ) {
        if (line.empty()) {
            d.push_back(line);
        } else {
            d.back() += line + ':';     // subtract ':' from counts later
        }
    }
    for (auto& group : d)
        std::sort(std::begin(group), std::end(group));
    return d;
}

auto do_all_the_work(const Declarations& d)
{
    std::size_t count1 = 0, count2 = 0;
    for (const auto& g : d) {
        // part 1 - count any 'yes'
        std::string buff;
        std::unique_copy(std::begin(g), std::end(g), std::back_inserter(buff));
        count1 += buff.size() - 1;

        // part 2 - count consensus 'yes'
        std::vector<std::size_t> cc;
        for (const auto ch : buff) {
            cc.push_back(std::count(std::begin(g), std::end(g), ch));
        }
        count2 += std::count(std::begin(cc), std::end(cc), cc.front()) - 1;
    }
    return std::make_pair(count1, count2);
}

int main()
{
    const Declarations d = read_and_sort_input();

    const auto [ part1, part2 ] = do_all_the_work(d);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';
}