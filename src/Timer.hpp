#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std::chrono;

class Timer {
    using Clock = std::chrono::steady_clock;
    using Time_point = std::chrono::time_point<Clock>;
public:
    Timer(const bool start_now = true) { if (start_now) start(); }

    void start() { start_stamp = Clock::now(); }
    void end() { stamp("Total"); print_log(); }

    void stamp(const std::string& label)
    {
        log.push_back(std::make_pair(label, Clock::now()));
    }

    void print_log() const;

private:

    Time_point start_stamp;
    std::vector<std::pair<std::string,Time_point>> log;
};

void Timer::print_log() const
{
    for (const auto& [ l, t ] : log) {
        std::cout << std::setw(8) << l << ":\t"
                  << duration_cast<microseconds>(t - start_stamp).count()
                  << " us\n";
    }
}