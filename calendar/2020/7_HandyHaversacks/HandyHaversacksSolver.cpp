#include "HandyHaversacksSolver.h"

#include <fstream>
#include <string>
#include <regex>

void HandyHaversacksSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    std::string temp;
    while (std::getline(inputStream, temp))
    {
        ParseRuleset(temp);
    }
}

std::size_t HandyHaversacksSolver::SolveProblemA() const
{
    const std::string toSearch("shiny gold");

    return std::count_if(m_Problem.cbegin(), m_Problem.cend(), [this, &toSearch](const auto& rulePair)
    {
        if (rulePair.first == toSearch)
        {
            return false;
        }

        return CanContain(rulePair.first, toSearch);
    });
}

std::size_t HandyHaversacksSolver::SolveProblemB() const
{
    return RecursiveCount("shiny gold") - 1; // Don't count the shiny gold bag itself
}

void HandyHaversacksSolver::ParseRuleset(std::string ruleSetString)
{
    const std::regex RULESET_PAIR_REGEX(R"((\w+ \w+) bags contain (.*))");
    std::smatch match;

    if (!std::regex_match(ruleSetString, match, RULESET_PAIR_REGEX))
    {
        return;
    }

    Color color = match[1];
    m_Problem.emplace(std::make_pair( color, Ruleset() ));
    Ruleset& ruleSet = m_Problem.at(color);
    std::string ruleSetSuffix = match[2];

    const std::regex RULE_REGEX(R"(([0-9]+) (\w+ \w+) bag(s?)((, )|\.))");
    std::smatch ruleMatch;
    while (std::regex_search(ruleSetSuffix, ruleMatch, RULE_REGEX))
    {
        ruleSet.emplace(Rule { ruleMatch[2], std::stoul(ruleMatch[1]) });
        ruleSetSuffix = ruleMatch.suffix();
    }
}

bool HandyHaversacksSolver::CanContain(const Color& outerBag, const Color& innerBag) const
{
    // Good old Dijkstra all over again
    std::unordered_set<Color> toExplore;
    std::unordered_set<Color> explored;

    toExplore.insert(outerBag);
    Color current;
    do
    {
        current = toExplore.extract(toExplore.begin()).value();
        if (current == innerBag) { return true; }

        for (const Rule& rule : m_Problem.at(current))
        {
            if (explored.count(rule.m_Color) > 0)
            {
                // Already explored
                continue;
            }

            toExplore.insert(rule.m_Color);
        }
    } while (!toExplore.empty());

    return false;
}

std::size_t HandyHaversacksSolver::RecursiveCount(Color color) const
{
    std::size_t total = 1;
    for (const auto& rule : m_Problem.at(color))
    {
        total += rule.m_Amount * RecursiveCount(rule.m_Color);
    }

    return total;
}
