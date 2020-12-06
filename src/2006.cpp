#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> read_and_sort_input()
{
    std::vector<std::string> d (1);     // start building from first
    for (std::string line; std::getline(std::cin, line); ) {
        if (line.empty()) {
            d.push_back(line);
        } else {
            d.back() += line + ':';     // subtract ':' from counts later
        }
    }
    for (auto& g : d)
        std::sort(std::begin(g), std::end(g));
    return d;
}

std::pair<std::size_t, std::size_t> do_work(const std::vector<std::string>& d)
{
    std::size_t count1 = 0, count2 = 0;
    for (const auto& g : d) {
        // part 1
        std::string buff;
        std::unique_copy(std::begin(g), std::end(g), std::back_inserter(buff));
        count1 += buff.size() - 1;

        // part 2
        std::vector<std::size_t> cc;
        for (const auto c : buff) {
            cc.push_back(std::count(std::begin(g), std::end(g), c));
        }
        count2 += std::count(std::begin(cc), std::end(cc), cc.front()) - 1;
    }
    return std::make_pair(count1, count2);
}

int main()
{
    std::vector<std::string> d = read_and_sort_input();

    auto [ part1, part2 ] = do_work(d);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';
}