#include "PassportProcessingSolver.h"

#include <string>
#include <fstream>
#include <regex>
#include <functional>

constexpr const char* KEY_BYR = "byr";
constexpr const char* KEY_IYR = "iyr";
constexpr const char* KEY_EYR = "eyr";
constexpr const char* KEY_HGT = "hgt";
constexpr const char* KEY_HCL = "hcl";
constexpr const char* KEY_ECL = "ecl";
constexpr const char* KEY_PID = "pid";
constexpr const char* KEY_CID = "cid";

const std::vector<const char*> keysToCheck = { KEY_BYR, KEY_ECL, KEY_EYR, KEY_HCL, KEY_HGT, KEY_IYR, KEY_PID };

void PassportProcessingSolver::Init(std::string& input)
{
    const std::regex PASSPORT_FIELD_REGEX { R"(([a-z]{3}):([^\s]+)\s)" };
    std::smatch fieldMatch;

    std::ifstream inputStream(input);
    std::string temp;
    Passport* passport = &m_Problem.emplace_back();
    while (std::getline(inputStream, temp))
    {
        if (temp.empty())
        {
            passport = &m_Problem.emplace_back();
            continue;
        }

        temp += '\n';

        while (std::regex_search(temp, fieldMatch, PASSPORT_FIELD_REGEX))
        {
            (*passport)[fieldMatch[1]] = fieldMatch[2];
            temp = fieldMatch.suffix();
        }
    }
}

std::size_t PassportProcessingSolver::SolveProblemA() const
{
    return std::count_if(m_Problem.cbegin(), m_Problem.cend(), &PassportProcessingSolver::IsValid);
}

std::size_t PassportProcessingSolver::SolveProblemB() const
{
    Problem problemCopy = m_Problem;
    problemCopy.erase(std::remove_if(problemCopy.begin(), problemCopy.end(), std::not_fn(&PassportProcessingSolver::IsValid)), problemCopy.end());

    auto isByrValid = [](std::string byr)
    {
        int value = std::stoi(byr);
        return value >= 1920 && value <= 2002;
    };

    auto isIyrValid = [](std::string iyr)
    {
        int value = std::stoi(iyr);
        return value >= 2010 && value <= 2020;
    };

    auto isEyrValid = [](std::string iyr)
    {
        int value = std::stoi(iyr);
        return value >= 2020 && value <= 2030;
    };

    auto isHgtValid = [](std::string hgt)
    {
        static const std::regex HGT_REGEX { R"(([0-9]+)(in|cm))" };
        std::smatch match;
        if (std::regex_match(hgt, match, HGT_REGEX))
        {
            int value = std::stoi(match[1]);
            if (match[2] == "cm")
            {
                return value >= 150 && value <= 193;
            }
            else
            {
                return value >= 59 && value <= 76;
            }
        }
        return false;
    };

    auto isHclValid = [](std::string hcl)
    {
        static const std::regex HCL_REGEX { R"(#[0-9a-f]{6})" };
        return std::regex_match(hcl, HCL_REGEX);
    };

    auto isEclValid = [](std::string ecl)
    {
        static const std::regex ECL_REGEX { R"(amb|blu|brn|gry|grn|hzl|oth)" };
        return ecl.size() == 3 && std::regex_match(ecl, ECL_REGEX);
    };

    auto isPidValid = [](std::string pid)
    {
        static const std::regex PID_REGEX { R"([0-9]{9})" };
        return std::regex_match(pid, PID_REGEX);
    };

    return std::count_if(problemCopy.begin(), problemCopy.end(),
        [&isByrValid, &isHclValid, &isEclValid, &isEyrValid, &isHgtValid, &isIyrValid, &isPidValid]
        (Passport& passport)
        {
            return  isByrValid(passport[KEY_BYR]) &&
                    isHclValid(passport[KEY_HCL]) &&
                    isEclValid(passport[KEY_ECL]) &&
                    isEyrValid(passport[KEY_EYR]) &&
                    isHgtValid(passport[KEY_HGT]) &&
                    isIyrValid(passport[KEY_IYR]) &&
                    isPidValid(passport[KEY_PID]);
        }
    );
}

bool PassportProcessingSolver::IsValid(const Passport& passport)
{
    if (passport.size() < keysToCheck.size())
    {
        return false;
    }

    return std::all_of
    (
        keysToCheck.cbegin(), keysToCheck.cend(),
        [&passport](const char* key)
        {
            return passport.count(key) > 0;
        }
    );
}
