#pragma once

#include <ProblemSolver.h>

#include <vector>

namespace aoc2021::TreacheryOfWhales
{
    using Crabs = std::vector<std::int32_t>;

    class TreacheryOfWhalesSolver : public ProblemSolver<std::string, std::uint64_t, std::uint64_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint64_t SolveProblemA() const override;
        std::uint64_t SolveProblemB() const override;

    private:
        Crabs m_Problem;
    };
}