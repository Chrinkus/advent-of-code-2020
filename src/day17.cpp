#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>

#include "Read_input.hpp"       // simple, handy reader
#include "Timer.hpp"            // for timing solution
#include "Matrix11.hpp"
#include "MatrixIO11.hpp"
constexpr int WIDTH = 6;        // for output alignment

using namespace Numeric_lib;
using Index = std::size_t;

constexpr int PART_1_CYCLES = 6;

constexpr std::array<std::tuple<int,int,int>,26> dirs_3d { {
    {-1,-1,-1}, {0,-1,-1},  {1,-1,-1},  //
    {-1,0,-1},  {0,0,-1},   {1,0,-1},   // front layer
    {-1,1,-1},  {0,1,-1},   {1,1,-1},   // 

    {-1,-1,0},  {0,-1,0},   {1,-1,0},   //
    {-1,0,0},   /*0,0,0*/   {1,0,0},    // middle layer
    {-1,1,0},   {0,1,0},    {1,1,0},    //

    {-1,-1,1},  {0,-1,1},   {1,-1,1},   //
    {-1,0,1},   {0,0,1},    {1,0,1},    // back layer
    {-1,1,1},   {0,1,1},    {1,1,1}     //
} };

/*
constexpr std::array<std::tuple<int,int,int,int>,80> dirs_4d { {
    // is this really necessary?
} };
*/

auto parse_2d_input(const std::vector<std::string>& input)
{
    Matrix<char,2> mx (input.front().size(), input.size());
    for (::Index i = 0; i < input.size(); ++i) {
        for (::Index j = 0; j < input.front().size(); ++j) {
            mx(i,j) = input[i][j];
        }
    }
    return mx;
}

auto convert_to_3d(const Matrix<char,2>& mx2, const char fill, Index z = 0)
{
    if (z == 0 && mx2.dim1() != mx2.dim2()) {
        std::cerr << "Error: if not square, please specify z size\n";
        throw;
    } else {
        z = mx2.dim1();
    }
    Matrix<char,3> mx3 (mx2.dim1(), mx2.dim2(), z);
    mx3 = fill;
    for (Index i = 0, k = z / 2; i < mx2.dim1(); ++i) {
        for (Index j = 0; j < mx2.dim2(); ++j) {
            mx3(k,i,j) = mx2(i,j);
        }
    }
    return mx3;
}

/*
auto grow_grid(const Matrix<char,2>& mx_old, const char fill, Index delta = 0)
{
    if (delta == 0) delta = mx_old.dim1() / 2;  // default growth is by half
    Matrix<char,2> mx_new (mx_old.dim1() + delta, mx_old.dim2() + delta);
    mx_new = fill;

    for (Index i = 0, pad = delta / 2; i < mx_old.dim1(); ++i) {
        for (Index j = 0; j < mx_old.dim2(); ++j) {
            mx_new(i+pad,j+pad) = mx_old(i,j);
        }
    }
    return mx_new;
}
*/
auto grow_cube(const Matrix<char,3>& mx_old, const char fill, Index delta = 0)
{
    if (delta == 0) delta = mx_old.dim1() / 2;  // default growth is by half
    Matrix<char,3> mx_new (mx_old.dim1() + delta,
                           mx_old.dim2() + delta,
                           mx_old.dim3() + delta);
    mx_new = fill;
    for (Index i = 0, pad = delta / 2; i < mx_old.dim1(); ++i) {
        for (Index j = 0; j < mx_old.dim2(); ++j) {
            for (Index k = 0; k < mx_old.dim3(); ++k) {
                mx_new(i+pad,j+pad,k+pad) = mx_old(i,j,k);
            }
        }
    }
    return mx_new;
}

auto count_adjacents(const Matrix<char,3>& mx, const Index& x, const Index& y,
        const Index & z)
{
    auto count = 0;
    for (const auto& [dx, dy, dz] : dirs_3d) {
        Index xx = x + dx, yy = y + dy, zz = z + dz;
        if (0 <= xx && xx < mx.dim2() &&
            0 <= yy && yy < mx.dim1() &&
            0 <= zz && zz < mx.dim3()) {
            if (mx(yy,xx,zz) == '#')
                ++count;
        }
    }
    return count;
}

auto advance_cycle(const Matrix<char,3>& mx)
{
    auto mnext = mx;        // should do copy
    for (Index y = 0; y < mx.dim1(); ++y) {
        for (Index x = 0; x < mx.dim2(); ++x) {
            for (Index z = 0; z < mx.dim3(); ++z) {
                const auto ch = mx(y,x,z);
                switch (ch) {
                case '.':
                    if (count_adjacents(mx, x, y, z) == 3) {
                        mnext(y,x,z) = '#';
                    }
                    break;
                case '#':
                    {
                        auto res = count_adjacents(mx, x, y, z);
                        if (res < 2 || 3 < res) {
                            mnext(y,x,z) = '.';
                        }
                        break;
                    }
                }
            }
        }
    }
    return mnext;
}

auto count_active(const Matrix<char,3>& mx)
{
    return std::count(mx.data(), mx.data()+ mx.size(), '#');
}

int main()
try {
    Timer t {};         // start of timing
    std::cout << "Advent of Code 2020\n"
              << "Day 17 - Conway's Cubes\n\n";

    const auto input = read_input_lines();
    Matrix<char,2> mx2 = parse_2d_input(input);
    Matrix<char,3> mx3 = convert_to_3d(mx2, '.');
    auto mx3_big = grow_cube(mx3, '.', 12);
    /*
    std::cout << "Before..\n";
    for (Index i = 0; i < mx3_big.dim1(); ++i)
        std::cout << mx3_big[i] << '\n';
    */

    for (Index i = 0; i < PART_1_CYCLES; ++i)
        mx3_big = advance_cycle(mx3_big);

    /*
    std::cout << "After..\n";
    for (Index i = 0; i < mx3_big.dim1(); ++i)
        std::cout << mx3_big[i] << '\n';
    */

    const auto part1 = count_active(mx3_big);
    const auto part2 = 0;
    std::cout << std::setw(WIDTH) << "Part 1: " << part1 << '\n';
    std::cout << std::setw(WIDTH) << "Part 2: " << part2 << '\n';

    t.end(WIDTH);       // end of timing, print report
}
catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << '\n';
    return 1;
}
