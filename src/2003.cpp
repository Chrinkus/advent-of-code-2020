#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using Hill = std::vector<std::string>;
using Slopes = std::vector<std::pair<int,int>>;

int count_trees(const std::pair<int,int>& slope, const Hill& hill)
{
    auto [ right, down ] = slope;
    int trees = 0, x = 0, y = 0;
    while (y < hill.size()) {
        if (hill[y][x] == '#')
            ++trees;
        x = (x + right) % hill.front().size();
        y += down;
    }
    return trees;
}

int64_t get_tree_sum_prod(const Slopes& slopes, const Hill& hill)
{
    std::vector<int> results (slopes.size());

    for (auto i = 0; i < slopes.size(); ++i) {
        results[i] = count_trees(slopes[i], hill);
    }
    return std::accumulate(std::begin(results), std::end(results), 1,
            std::multiplies<int>());
}

int main()
{
    Hill hill;
    for (std::string line; std::getline(std::cin, line); )
        hill.push_back(line);
    const Slopes slopes { {1,1}, {3,1}, {5,1}, {7,1}, {1,2} };

    auto part1 = count_trees(slopes[1], hill);
    std::cout << "Part 1: " << part1 << '\n';

    auto part2 = get_tree_sum_prod(slopes, hill);
    std::cout << "Part 2: " << part2 << '\n';
}