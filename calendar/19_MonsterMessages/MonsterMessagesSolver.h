#pragma once

#include <ProblemSolver.h>

#include <unordered_map>
#include <regex>

class MonsterMessagesSolver : public ProblemSolver<std::string, std::size_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;

private:
    struct Rule
    {
        Rule() = default;
        Rule(std::uint16_t id, std::string raw) : m_ID(id), m_RawText(raw) { };

        std::uint16_t m_ID;
        std::string m_RawText;
        std::string m_RegexText;
        std::regex m_Regex;
    };

    using Ruleset = std::unordered_map<std::uint16_t, Rule>;

    struct Problem
    {
        Ruleset m_Ruleset;
        std::vector<std::string> m_Messages;
    };

    Problem m_Problem;

    void ConvertRuleToRegex(Rule& rule);
    std::string ConvertSequenceToRegex(const std::string& sequence);
};