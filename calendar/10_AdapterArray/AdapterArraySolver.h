#pragma once

#include <ProblemSolver.h>

#include <vector>

std::uint64_t Factorial(std::uint64_t val);

class AdapterArraySolver : public ProblemSolver<std::string, std::uint32_t, std::uint64_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint64_t SolveProblemB() const override;

private:
    using Problem = std::vector<std::uint32_t>;

    std::uint64_t CountRemovableAdapters(std::unordered_set<uint32_t>& holes) const;

    Problem m_Problem;
};