#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>               // for timing solution

#include "Read_input.hpp"       // simple, handy reader
#include "Timer.hpp"            // for timing solution

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

    const auto part1 = input.size();            // handy
    const auto part2 = solve_problem();
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    t.end();            // end of timing and report
}