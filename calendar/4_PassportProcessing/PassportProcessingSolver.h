#pragma once

#include <ProblemSolver.h>

#include <unordered_map>
#include <unordered_set>

class PassportProcessingSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    using Passport = std::unordered_map<std::string, std::string>;
    using Problem = std::vector<Passport>;

    Problem m_Problem;

    static bool IsValid(const Passport& passport);
};