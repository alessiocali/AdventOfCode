#pragma once

#include <ProblemSolver.h>

#include <unordered_set>

class BinaryBoardingSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;

    struct Seat
    {
        Seat(std::uint8_t row, std::uint8_t col)
            : m_Row(row), m_Col(col), m_Id(row * 8 + col)
        { }

        std::uint8_t m_Row, m_Col;
        std::uint32_t m_Id;
    };

private:

    using Problem = std::vector<Seat>;

    Problem m_Problem;
};

namespace std
{
    inline bool operator<(const BinaryBoardingSolver::Seat& s1, const BinaryBoardingSolver::Seat& s2) { return s1.m_Id < s2.m_Id; }
}