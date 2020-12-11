#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>


class Timer {
    using Clock = std::chrono::steady_clock;
    using Time_point = std::chrono::time_point<Clock>;
public:
    Timer() = default;
    explicit Timer(const std::string& l) : label{l} { start(); }
private:
    void start();

    std::string label;
    std::vector<Time_point> vtp;
};