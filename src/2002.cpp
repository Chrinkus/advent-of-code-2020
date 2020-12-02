#include <iostream>
#include <string>
#include <algorithm>

std::pair<int,int> count_valid_passwords()
{
    int lower, upper, count1 = 0, count2 = 0;
    char ch, xx;
    std::string password;
    while (std::cin >> lower >> xx >> upper >> ch >> xx >> password) {
        // Part 1
        auto n = std::count(std::begin(password), std::end(password), ch);
        if (lower <= n && n <= upper)
            ++count1;
        
        // Part 2
        auto f = 0;
        if (--lower <= password.size() && password[lower] == ch)
            ++f;
        if (--upper <= password.size() && password[upper] == ch)
            ++f;
        if (f == 1) 
            ++count2;
    }

    return std::make_pair(count1, count2);
}

int main()
{
    auto results = count_valid_passwords();

    std::cout << "Part 1: " << results.first << '\n';
    std::cout << "Part 2: " << results.second << '\n';
}