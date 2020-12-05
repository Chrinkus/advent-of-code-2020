#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>       // isdigit, isxdigit

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Field definitions and validation
enum class Field { byr, iyr, eyr, hgt, hcl, ecl, pid, cid };

const std::vector<std::string> field_names {
    "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"//, "cid"
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

const std::vector<std::string> eye_colors {
    "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
};

bool check_birth_year(const std::string& data)
{
    if (data.size() != 4)
        return false;
    auto y = std::stoi(data);
    return (1920 <= y && y <= 2020);
}

bool check_issue_year(const std::string& data)
{
    if (data.size() != 4)
        return false;
    auto y = std::stoi(data);
    return (2010 <= y && y <= 2020);
}
bool check_expire_year(const std::string& data)
{
    if (data.size() != 4)
        return false;
    auto y = std::stoi(data);
    return (2020 <= y && y <= 2030);
}
bool check_height(const std::string& data)
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
bool check_hair_color(const std::string& data)
{
    if (data.size() != 7 || data[0] != '#')
        return false;
    for (auto i = 1; i < data.size(); ++i)
        if (!isxdigit(data[i]))
            return false;
    return true;
}
bool check_eye_color(const std::string& data)
{
    auto it = std::find(std::begin(eye_colors),
            std::end(eye_colors), data);
    return it != std::end(eye_colors);
}
bool check_passport_id(const std::string& data)
{
    if (data.size() != 9)
        return false;
    for (const auto ch : data)
        if (!isdigit(ch))
            return false;
    return true;
}

bool validate_entry(const std::string& entry)
{
    std::cout << "Made it here with: " << entry << '\n';
    Field f = get_field(entry.substr(0, 3));
    std::string val = entry.substr(4);

    switch (f) {
        case Field::byr:    return check_birth_year(val);
        case Field::iyr:    return check_issue_year(val);
        case Field::eyr:    return check_expire_year(val);
        case Field::hgt:    return check_height(val);
        case Field::hcl:    return check_hair_color(val);
        case Field::ecl:    return check_eye_color(val);
        case Field::pid:    return check_passport_id(val);
        case Field::cid:    return true;
        default:            return false;
    }
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Passport class
class Passport {
public:
    Passport() = default;
    explicit Passport(const std::string& s);

    bool has_valid_fields() const { return valid_fields; }
    bool is_valid() const { return valid_fields && valid_data; }

private:
    std::string data;
    bool valid_fields = false;
    bool valid_data   = false;

    void check_fields();
    void check_data();
};

Passport::Passport(const std::string& s)
    : data{s}
{
    check_fields();
    check_data();
}

void Passport::check_fields()
{
    valid_fields = std::all_of(std::begin(field_names), std::end(field_names),
            [this](const auto& f) {
                return this->data.find(f) != std::string::npos;
            });
}

void Passport::check_data()
{
    std::cout << "Is there a space here >" << data << '\n';
    std::vector<std::string> entries;
    std::istringstream iss {data};
    for (std::string entry; std::getline(iss, entry, ' '); )
        entries.push_back(entry);
    
    valid_data = std::all_of(std::begin(entries), std::end(entries),
            validate_entry);
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
// Input processing and main()
std::vector<Passport> parse_passports()
{
    std::vector<Passport> passports;
    std::string line, buffer;
    do {
        if (line.empty() && !buffer.empty()) {
            passports.push_back(Passport{buffer});
            buffer.clear();
        } else if (!line.empty()) {
            buffer += line + ' ';
        }
    } while (std::getline(std::cin, line));
    passports.push_back(Passport{buffer});
    return passports;
}

int main()
{
    auto vpp = parse_passports();

    auto part1 = std::count_if(std::begin(vpp), std::end(vpp),
            [](const auto& pp) { return pp.has_valid_fields(); });
    auto part2 = std::count_if(std::begin(vpp), std::end(vpp),
            [](const auto& pp) { return pp.is_valid(); });

    std::cout << "Part 1: " << part1 << '\n';
    std::cout << "Part 2: " << part2 << '\n';
}