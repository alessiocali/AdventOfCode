#include "MonsterMessagesSolver.h"

#include <fstream>
#include <string>
#include <sstream>
#include <cassert>

void MonsterMessagesSolver::Init(std::string& input)
{
    static const std::regex RULE_REGEX { R"((\d+)\: (.*))" };

    std::ifstream inputStream(input);
    std::smatch match;
    assert(inputStream.is_open());
    for (std::string line; std::getline(inputStream, line) && !line.empty();)
    {
        if (std::regex_match(line, match, RULE_REGEX))
        {
            std::uint16_t id = static_cast<std::uint16_t>(std::stoi(match[1]));
            m_Problem.m_Ruleset[id] = Rule { id, std::string(match[2]) };
        }
    }

    for (std::string line; std::getline(inputStream, line);)
    {
        m_Problem.m_Messages.emplace_back(line);
    }

    for (auto& [id, rule] : m_Problem.m_Ruleset)
    {
        ConvertRuleToRegex(rule);
    }
}

std::size_t MonsterMessagesSolver::SolveProblemA() const
{
    assert(m_Problem.m_Ruleset.count(0) == 1);
    const auto& ruleZero = m_Problem.m_Ruleset.at(0);

    std::regex exactMatchRegex { "^(" + ruleZero.m_RegexText + ")$" };
    auto matchesRuleZero = [&exactMatchRegex](const std::string& msg) { return std::regex_match(msg, exactMatchRegex); };
    return std::count_if(m_Problem.m_Messages.cbegin(), m_Problem.m_Messages.cend(), matchesRuleZero);
}

std::uint32_t MonsterMessagesSolver::SolveProblemB() const
{
    return 0;
}

void MonsterMessagesSolver::ConvertRuleToRegex(Rule& rule)
{
    static const std::regex LEAF_RULE_REGEX { R"(\"(\w)\")" };
    static const std::regex SEQUENCE_RULE_REGEX { R"((?:(\d+) ?)+)" };
    static const std::regex PIPE_RULE_REGEX { R"(((?:\d+ )+)\|((?: \d+)+))" };

    if (!rule.m_RegexText.empty())
    {
        return;
    }

    std::smatch match;
    if (std::regex_match(rule.m_RawText, match, LEAF_RULE_REGEX))
    {
        rule.m_RegexText = match[1];
    }
    else if (std::regex_match(rule.m_RawText, match, PIPE_RULE_REGEX))
    {
        std::stringstream regexBuilder {  };
        regexBuilder    << "(?:"
                        << ConvertSequenceToRegex(match[1]) << ")|(?:"
                        << ConvertSequenceToRegex(match[2]) << ")";

        rule.m_RegexText = regexBuilder.str();
    }
    else if (std::regex_match(rule.m_RawText, match, SEQUENCE_RULE_REGEX))
    {
        rule.m_RegexText = ConvertSequenceToRegex(match[0]);
    }
    else
    {
        assert(false && "Invalid rule");
        return;
    }

    assert(!rule.m_RegexText.empty());
    rule.m_Regex = std::regex { "(" + rule.m_RegexText + ")" };
}

std::string MonsterMessagesSolver::ConvertSequenceToRegex(const std::string& sequence)
{
    static const std::regex REF_RULE_REGEX { R"(\d+)" };
    std::smatch match;
    std::string searchString { sequence };
    std::stringstream result;
    while (std::regex_search(searchString, match, REF_RULE_REGEX))
    {
        std::uint16_t refRuleID = std::stoi(match[0]);
        auto& rule = m_Problem.m_Ruleset[refRuleID];
        if (rule.m_RegexText.empty())
        {
            ConvertRuleToRegex(rule);
        }
        result << "(" << rule.m_RegexText << ")";
        searchString = match.suffix();
    };
    return result.str();
}