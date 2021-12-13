#pragma once

#include <ProblemSolver.h>

#include <unordered_set>
#include <unordered_map>

using Color = std::string;

struct Rule
{
    Color m_Color;
    std::size_t m_Amount;
};

namespace std
{
    template<>
    struct hash<Rule>
    {
        std::size_t operator()(const Rule& rule) const
        {
            return std::hash<Color>()(rule.m_Color);
        }
    };

    inline bool operator==(const Rule& r1, const Rule& r2) { return r1.m_Color == r2.m_Color; }
}

using Ruleset = std::unordered_set<Rule>;
using Problem = std::unordered_map<Color, Ruleset>;

class HandyHaversacksSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    Problem m_Problem;

    void ParseRuleset(std::string ruleset);
    bool CanContain(const Color& outerBag, const Color& innerBag) const;
    std::size_t RecursiveCount(Color color) const;
};