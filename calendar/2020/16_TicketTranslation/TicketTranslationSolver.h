#pragma once

#include <ProblemSolver.h>
#include <vector>

class TicketTranslationSolver : public ProblemSolver<std::string, std::uint32_t, std::uint64_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint64_t SolveProblemB() const override;

private:
    using Ticket = std::vector<std::uint32_t>;
    using RangeRule = std::pair<std::uint32_t, std::uint32_t>;
    
    struct Rule
    {
        std::string m_Name;
        RangeRule m_FirstRange;
        RangeRule m_SecondRange;
    };

    using Ruleset = std::vector<Rule>;

    struct Problem
    {
        Ruleset m_Ruleset;
        Ticket m_Ticket;
        std::vector<Ticket> m_NearbyTickets;
    };

    Problem m_Problem;
};