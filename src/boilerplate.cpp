#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "Read_input.hpp"       // simple, handy reader
#include "Timer.hpp"            // for timing solution
constexpr int WIDTH = 5;        // for output alignment

// placeholder function to allow boilerplate.cpp to compile
auto solve_problem()
{
    auto count = 0;

    return count;
}

int main()
{
    Timer t {};         // start of timing

    const auto input = read_input_lines();
    std::cout << "Size of input: " << input.size() << '\n'
              << "Front: " << input.front() << '\n'
              << "Back: " << input.back() << '\n';

    const auto part1 = input.size();            // handy
    const auto part2 = solve_problem();
    std::cout << std::setw(WIDTH) << "Part 1: " << part1 << '\n';
    std::cout << std::setw(WIDTH) << "Part 2: " << part2 << '\n';

    t.end(WIDTH);       // end of timing, print report
}