#pragma once

#include <ProblemSolver.h>

#include <vector>
#include <tuple>

struct BusGap
{
    std::uint32_t m_ID;
    std::uint32_t m_Gap;
};

struct Problem
{
    std::uint32_t m_EarliestTime;
    std::vector< BusGap > m_BusIDs;
    std::vector<std::uint32_t> m_Gaps;
};

class ShuttleSearchSolver : public ProblemSolver<std::string, std::uint32_t, std::uint64_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint64_t SolveProblemB() const override;

private:
    Problem m_Problem;
};