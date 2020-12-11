#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>               // for timing solution
#include <array>

#include "Read_input.hpp"       // simple, handy reader

using Index = std::int64_t;

constexpr std::array<std::pair<int,int>,8> dirs {
    { {-1,-1}, {0,-1}, {1,-1}, {-1,0}, {1,0}, {-1,1}, {0,1}, {1,1} }
};

auto count_adjacents_2(const std::vector<std::string>& vs, const Index x,
        const Index y, const int limit = 4)
{
    auto count = 0;
    for (const auto& [ dx, dy ] : dirs) {
        Index xx = x + dx, yy  = y + dy;
        if (0 <= xx && xx < vs.front().size() && 0 <= yy && yy < vs.size())
            if (vs[yy][xx] == '#')
                ++count;
        if (count == limit)
            break;
    }
    return count;
}

auto count_adjacents(const std::vector<std::string>& vs, const Index x,
        const Index y)
{
    auto count = 0;
    const auto l = x - 1, r = x + 1, u = y - 1, d = y + 1;
    if (l >= 0) {                   // check left side
        if (u >= 0 && vs[u][l] == '#')          ++count;    // top left
        if (vs[y][l] == '#')                    ++count;    // left
        if (d < vs.size() && vs[d][l] == '#')   ++count;    // bottom left
    }
    if (r < vs.front().size()) {    // check right side
        if (u >= 0 && vs[u][r] == '#')          ++count;    // top right
        if (vs[y][r] == '#')                    ++count;    // right
        if (d < vs.size() && vs[d][r] == '#')   ++count;    // bottom right
    }
    if (u >= 0 && vs[u][x] == '#')              ++count;    // top
    if (d < vs.size() && vs[d][x] == '#')       ++count;    // bottom

    return count;
}

auto found_occupied(const std::vector<std::string>& vs,
        Index x, Index y, const int dx, const int dy)
{
    x += dx; y += dy;
    while ((0 <= x && x < vs.front().size()) &&
            (0 <= y && y < vs.size())) {
        auto ch = vs[y][x];
        if (ch == 'L') return 0;
        if (ch == '#') return 1;
        x += dx; y += dy;
    }
    return 0;
}

auto count_extended_adjacents(const std::vector<std::string>& vs,
        const Index x, const Index y)
    // excessively verbose, runs a little quicker
{
    auto count = 0;
    const auto l = x - 1, r = x + 1, u = y - 1, d = y + 1;
    for (auto ll = l; ll >= 0; --ll) {
        auto ch = vs[y][ll];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }       // left
    }
    for (auto rr = r; rr < vs.front().size(); ++rr) {
        auto ch = vs[y][rr];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }       // right
    }
    for (auto uu = u; uu >= 0; --uu) {
        auto ch = vs[uu][x];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }       // up
    }
    for (auto dd = d; dd < vs.size(); ++dd) {
        auto ch = vs[dd][x];
        if (ch == 'L') break;
        if (vs[dd][x] == '#') { ++count; break; }       // down
    }

    for (auto ll = l, uu = u; ll >= 0 && uu >= 0; --ll, --uu) {
        auto ch = vs[uu][ll];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }      // top left
    }
    for (auto ll = l, dd = d; ll >= 0 && dd < vs.size(); --ll, ++dd) {
        auto ch = vs[dd][ll];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }      // bottom left
    }
    for (auto rr = r, uu = u; rr < vs.front().size() && uu >= 0; ++rr, --uu) {
        auto ch = vs[uu][rr];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }      // top right
    }
    for (auto rr = r, dd = d; rr < vs.front().size() && dd < vs.size(); ++rr, ++dd) {
        auto ch = vs[dd][rr];
        if (ch == 'L') break;
        if (ch == '#') { ++count; break; }      // bottom right
    }

    return count;
}

auto count_extended_adjacents_2(const std::vector<std::string>& vs,
        const Index x, const Index y)
    // more concise, runs slower
{
    auto count = 0;
    count += found_occupied(vs, x, y, -1, 0);   // left
    count += found_occupied(vs, x, y, -1, -1);  // top left
    count += found_occupied(vs, x, y, 0, -1);   // up
    count += found_occupied(vs, x, y, 1, -1);   // top right
    count += found_occupied(vs, x, y, 1, 0);    // right
    count += found_occupied(vs, x, y, 1, 1);    // bottom right
    count += found_occupied(vs, x, y, 0, 1);    // bottom
    count += found_occupied(vs, x, y, -1, 1);   // bottom left
    return count;
}

auto count_extended_adjacents_3(const std::vector<std::string>& vs,
        const Index x, const Index y, const int limit = 5)
{
    auto count = 0;
    const auto dimx = vs.front().size();
    const auto dimy = vs.size();
    for (const auto& [ dx, dy ] : dirs) {
        for (Index xx = x + dx, yy = y + dy;
                0 <= xx && xx < dimx && 0 <= yy && yy < dimy;
                xx += dx, yy += dy) {
            auto ch = vs[yy][xx];
            if (ch == 'L')
                break;
            else if (ch == '#') {
                ++count;
                if (count == limit)
                    return count;
                break;
            }
        }
    }
    return count;
}

auto advance_round(const std::vector<std::string>& vs)
{
    std::vector<std::string> vnext;
    std::copy(std::begin(vs), std::end(vs), std::back_inserter(vnext));

    bool changed = false;
    for (Index y = 0; y < vs.size(); ++y) {
        for (Index x = 0; x < vs.front().size(); ++x) {
            const auto ch = vs[y][x];
            switch (ch) {
            case '.': break;        // floor, skip this location
            case 'L':
                if (count_adjacents_2(vs, x, y) == 0) {
                    vnext[y][x] = '#';
                    changed = true;
                }
                break;
            case '#':
                if (count_adjacents_2(vs, x, y) >= 4) {
                    vnext[y][x] = 'L';
                    changed = true;
                }
                break;
            }
        }
    }
    return std::make_pair(changed, vnext);
}

auto advance_round_extended(const std::vector<std::string>& vs)
{
    std::vector<std::string> vnext;
    std::copy(std::begin(vs), std::end(vs), std::back_inserter(vnext));
    bool changed = false;
    for (Index y = 0; y < vs.size(); ++y) {
        for (Index x = 0; x < vs.front().size(); ++x) {
            const auto ch = vs[y][x];
            switch (ch) {
            case '.': break;        // floor, skip this location
            case 'L':
                if (count_extended_adjacents_3(vs, x, y) == 0) {
                    vnext[y][x] = '#';
                    changed = true;
                }
                break;
            case '#':
                if (count_extended_adjacents_3(vs, x, y) >= 5) {
                    vnext[y][x] = 'L';
                    changed = true;
                }
                break;
            }
        }
    }
    return std::make_pair(changed, vnext);
}

auto count_occupied(const std::vector<std::string>& vs)
{
    auto count = 0;
    for (const auto& s : vs)
        for (const auto& c : s)
            if (c == '#')
                ++count;
    return count;
}

auto advance_till_stable_1(std::vector<std::string> vs)
{
    while (true) {
        auto [ changed, vnext ] = advance_round(vs);
        if (!changed)
            return count_occupied(vnext);
        vs = vnext;
    }
}

auto advance_till_stable_2(std::vector<std::string> vs)
{
    while (true) {
        auto [ changed, vnext ] = advance_round_extended(vs);
        if (!changed)
            return count_occupied(vnext);
        vs = vnext;
    }
}

int main()
{
    // start of timing
    auto start = std::chrono::steady_clock::now();

    const auto seating_area = read_input_lines();

    const auto part1 = advance_till_stable_1(seating_area);
    const auto part2 = advance_till_stable_2(seating_area);
    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';

    // end of timing and report
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << "Time: " << time.count() << '\n';
}