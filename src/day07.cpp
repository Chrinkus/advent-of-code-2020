#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <sstream>

using Rules = std::vector<std::pair<int,std::string>>;
using Rulebook = std::unordered_map<std::string,Rules>;

auto build_rulebook()
{
    Rulebook rb;
    for (std::string adj, clr, xx; std::cin >> adj >> clr; ) {
        auto key = adj + ' ' + clr;
        std::vector<std::pair<int,std::string>> contents;
        std::cin >> xx >> xx;               // burn two words

        int qty;
        while (std::cin >> qty >> adj >> clr >> xx) {
            contents.push_back(std::make_pair(qty,adj + ' ' + clr));
            if (xx.back() == '.')
                break;
        }
        if (std::cin.fail()) {
            std::cin.clear();
            std::getline(std::cin, xx);     // discard rest of line
        } 
        rb[key] = contents;
    }
    return rb;
}

void track_carriers(const Rulebook& rb, const std::string& bag_t,
        std::set<std::string>& bags)
{
    for (const auto& [key,vals] : rb) {
        for (const auto& [q,b] : vals) {
            if (b == bag_t) {
                bags.insert(key);
                track_carriers(rb, key, bags);
            }
        }
    }
}

int count_carried(const Rulebook& rb, const std::string& bag_t)
{
    auto count = 0;
    for (const auto& [ q, b ] : rb.at(bag_t)) {
        count += q + q * count_carried(rb, b);
    }
    return count;
}

int main()
{
    const auto my_bag = "shiny gold";
    const auto rulebook = build_rulebook();

    std::set<std::string> bags;
    track_carriers(rulebook, my_bag, bags);
    const auto part1 = bags.size();

    const auto part2 = count_carried(rulebook, my_bag);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';
}
