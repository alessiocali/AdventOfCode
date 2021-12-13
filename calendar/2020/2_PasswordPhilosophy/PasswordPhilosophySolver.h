#pragma once

#include <ProblemSolver.h>

#include <unordered_set>

class PasswordPhilosophySolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    struct Policy
    {
        Policy(std::string inputString);

        std::uint32_t m_Min { 0 };
        std::uint32_t m_Max { 0 };
        char m_Character { 'a' };
    };

    struct PolicyPassword
    {
        Policy m_Policy;
        std::string m_Password;

        bool IsValidA() const;
        bool IsValidB() const;
    };

    using Problem = std::vector<PolicyPassword>;
    Problem m_Problem;

    PolicyPassword Parse(std::string& inputString);
};