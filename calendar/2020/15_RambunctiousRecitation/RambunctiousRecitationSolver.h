#pragma once

#include <ProblemSolver.h>
#include <vector>
#include <unordered_map>

class RambunctiousRecitationSolver : public ProblemSolver<std::string, std::uint64_t, std::uint64_t>
{
public:
    void Init(std::string& input) override;
    std::uint64_t SolveProblemA() const override;
    std::uint64_t SolveProblemB() const override;

private:
    using MemoryMap = std::unordered_map<std::uint64_t, std::uint64_t>;
    using Problem = std::vector<std::uint8_t>;

    Problem m_Problem;

    std::uint64_t GetSpokenNumber(std::size_t idx) const;
};