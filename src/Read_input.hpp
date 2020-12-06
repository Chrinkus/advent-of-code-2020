#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

template<typename Data>
auto read_data(std::istream& is = std::cin)
{
    std::vector<Data> vd;
    for (Data d; is >> d; ) {
        vd.push_back(d);
    }
    return vd;
}

template<typename Data>
auto read_data_and_sort(std::istream& is = std::cin)
{
    auto vd = read_data<Data>(is);
    std::sort(std::begin(vd), std::end(vd));
    return vd;
}

/*
template<typename Data>
auto read_data_and_sort_each(std::istream& is = std::cin)
{
    auto vd = read_data<Data>(is);
    for (auto& d : vd) {
        std::sort(std::begin(d), std::end(d));
    }
}
*/