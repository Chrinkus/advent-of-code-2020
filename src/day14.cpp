#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include <bitset>
#include <variant>
#include <unordered_map>
#include <numeric>

#include "Read_input.hpp"       // simple, handy reader
#include "Timer.hpp"            // for timing solution
constexpr int WIDTH = 5;        // for output alignment

using Index = std::size_t;
using Bigint = std::uint64_t;

enum class Ins { mask, mem };

struct Mask {
    std::string mask;
};

struct Mem {
    std::bitset<36> index = 0;
    std::bitset<36> value = 0;
};

struct Instruction {
    Ins ins;
    std::variant<Mask,Mem> data;
};

auto parse_input(const std::vector<std::string>& vs)
{
    static const std::regex mask_pat {R"(mask = ([X01]{36}))"};
    static const std::regex mem_pat {R"(mem\[(\d+)] = (\d+))"};

    std::vector<Instruction> vins;

    for (const auto& s : vs) {
        Instruction inst{};
        std::smatch match;
        if (std::regex_match(s, match, mem_pat)) {
            inst.ins = Ins::mem;
            auto i = std::stoull(match[1].str());
            auto v = std::stoull(match[2].str());
            Mem mem{i,v};
            inst.data = mem;
        } else if (std::regex_match(s, match, mask_pat)) {
            inst.ins = Ins::mask;
            std::string m = match[1];
            Mask mask{m};
            inst.data = mask;
        } else {
            std::cerr << "No pattern match: " << s << '\n';
        }
        vins.push_back(inst);
    }
    return vins;
}

Bigint memory_sum(const std::vector<Instruction>& vins)
{
    std::string mask;
    std::unordered_map<Index,Bigint> memory;
    for (const auto& ins : vins) {
        if (ins.ins == Ins::mask) {
            mask = std::get<Mask>(ins.data).mask;
        } else {
            const auto& index = std::get<Mem>(ins.data).index;
            std::bitset<36> value = std::get<Mem>(ins.data).value;
            for (Index i = 0, j = mask.size() - 1; i < mask.size(); ++i, --j) {
                switch (mask[i]) {
                case '1':   value[j] = true;    break;
                case '0':   value[j] = false;   break;
                case 'X':                       break;
                }
            }
            memory[index.to_ullong()] = value.to_ullong();
        }
    }

    return std::accumulate(std::begin(memory), std::end(memory), 0,
            [](const auto& a, const auto& b) {
                const auto [i,v] = b;
                return a + v;
            });
}

int main()
{
    Timer t {};         // start of timing

    const auto input = read_input_lines();
    for (const auto& i : input)
        std::cout << i << "END\n";
    const auto program = parse_input(input);
    for (const auto& line : program) {
        if (line.ins == Ins::mask)
            std::cout << std::get<Mask>(line.data).mask << '\n';
        else
            std::cout << std::get<Mem>(line.data).index.to_ullong() << ' '
                      << std::get<Mem>(line.data).value << '\n';
    }

    const auto part1 = memory_sum(program);
    const auto part2 = input.size() << '\n';
    std::cout << std::setw(WIDTH) << "Part 1: " << part1 << '\n';
    std::cout << std::setw(WIDTH) << "Part 2: " << part2 << '\n';

    t.end(WIDTH);       // end of timing, print report
}
