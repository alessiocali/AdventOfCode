#pragma once

#include <ProblemSolver.h>

#include <vector>

namespace aoc2021::SonarSweep
{
    class SonarSweepSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        using Report = std::vector<int>;
        Report m_Report;
    };
}