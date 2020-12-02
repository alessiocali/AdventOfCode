#pragma once

#include <ProblemSolver.h>

#include <unordered_set>

class ||PROBLEM_SOLVER|| : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;
};