#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>               // for timing solution

#include "Read_input.hpp"       // simple lib for reading input from istreams

// placeholder function to allow boilerplate.cpp to compile
auto solve_problem()
{
    auto count1 = 0, count2 = 0;

    return std::make_pair(count1, count2);
}

int main()
{
    // start of timing
    auto start = std::chrono::steady_clock::now();

    const auto input = read_input_lines();

    const auto [ part1, part2 ] = solve_problem();
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    // end of timing and report
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << "Time: " << time.count() << '\n';
}