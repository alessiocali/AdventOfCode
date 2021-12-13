#pragma once

#include <ProblemSolver.h>
#include <vector>

class EncodingErrorSolver : public ProblemSolver<std::string, std::int64_t, std::int64_t>
{
public:
    void Init(std::string& input) override;
    std::int64_t SolveProblemA() const override;
    std::int64_t SolveProblemB() const override;

private:
    static constexpr std::size_t BACKLIST_SIZE = 25;
    static constexpr std::int64_t WEAK_NUMBER = 3199139634;

    using Problem = std::vector<std::int64_t>;

    Problem m_Problem;
};