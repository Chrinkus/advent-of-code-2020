#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>       // isdigit, isxdigit

using Passports = std::vector<std::string>;

enum class Field { byr, iyr, eyr, hgt, hcl, ecl, pid, cid };

const std::vector<std::string> field_names {
    "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"//, "cid"
};

const std::vector<std::string> eye_colors {
    "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
};

Field get_field(const std::string& s)
{
    auto it = std::find(std::begin(field_names), std::end(field_names),
            s.substr(0, 3));
    if (it == std::end(field_names))
        return Field::cid;
    else
        return static_cast<Field>(std::distance(std::begin(field_names), it));
}

bool validate_field(const Field& f, const std::string& data)
{
    switch (f) {
        case Field::byr:    // d{4}, 1920 to 2002
            {
                if (data.size() != 4)
                    return false;
                auto y = std::stoi(data);
                return (1920 <= y && y <= 2020);
            }
        case Field::iyr:    // d{4}, 2010 to 2020
            {
                if (data.size() != 4)
                    return false;
                auto y = std::stoi(data);
                return (2010 <= y && y <= 2020);
            }
        case Field::eyr:    // d{4}, 2020 to 2030
            {
                if (data.size() != 4)
                    return false;
                auto y = std::stoi(data);
                return (2020 <= y && y <= 2030);
            }
        case Field::hgt:    // d{2,3}(cm|in), cm: 150 to 193, in: 59 to 76 
        {
            std::istringstream iss {data};
            int height;
            std::string sys;
            iss >> height >> sys;
            if (sys == "cm")
                return (150 <= height && height <= 193);
            else if (sys == "in")
                return (59 <= height && height <= 76);
            else
                return false;
        }
        case Field::hcl:    // #[0-9a-f]{6}
            if (data.size() != 7 || data[0] != '#')
                return false;
            for (auto i = 1; i < data.size(); ++i)
                if (!isxdigit(data[i]))
                    return false;
            return true;

        case Field::ecl:    // (amb|blu|brn|gry|grn|hzl|oth)
            {
                auto it = std::find(std::begin(eye_colors),
                        std::end(eye_colors), data);
                return it != std::end(eye_colors);
            }

        case Field::pid:    // d{9}
            if (data.size() != 9)
                return false;
            for (const auto ch : data)
                if (!isdigit(ch))
                    return false;
            return true;

        case Field::cid:    // ignored
            return true;
        default:            // never get here, might as well invalidate
            return false;
    }
}

int count_valid_passports(const Passports& pps)
{
    int count = 0;
    for (const auto& pp : pps) {
        auto flag = true;
        std::istringstream iss {pp};
        for (std::string s; iss >> s; ) {
            auto f = get_field(s.substr(0,3));
            if (!validate_field(f, s.substr(4))) {
                flag = false;
                break;          // stop checking this passport
            }
        }
        if (flag)
            ++count;
    }
    return count;
}

Passports parse_passports()
{
    Passports passports;
    std::string line;
    do {
        if (line.empty())
            passports.push_back(line);
        else
            passports.back() += ' ' + line;

    } while (std::getline(std::cin, line));
    return passports;
}

Passports count_valid_passport_fields(const Passports& passports)
{
    Passports valid_pps;

    for (const auto& p : passports) {
        if (std::all_of(std::begin(field_names), std::end(field_names),
                [&p](const auto& f){ return p.find(f) != std::string::npos; }))
            valid_pps.push_back(p);
    }
    return valid_pps;
}

int main()
{
    auto passports = parse_passports();
    auto valid_pps = count_valid_passport_fields(passports);

    auto part1 = valid_pps.size();
    std::cout << "Part 1: " << part1 << '\n';
    auto part2 = count_valid_passports(valid_pps);
    std::cout << "Part 2: " << part2 << '\n';
}