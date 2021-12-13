#pragma once

#include <ProblemSolver.h>

#include <bitset>
#include <vector>

class CustomCustomsSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    static constexpr std::size_t QUESTION_COUNT = 26;
    
    struct Group
    {
        std::bitset<QUESTION_COUNT> m_AnyAnswered;
        std::bitset<QUESTION_COUNT> m_AllAnswered;
    };

    using Problem = std::vector<Group>;

    Problem m_Problem;
};