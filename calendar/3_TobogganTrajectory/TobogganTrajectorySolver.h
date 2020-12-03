#pragma once

#include <ProblemSolver.h>

#include <vector>

class TobogganTrajectorySolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    enum class Tile
    {
        Tree,
        Space
    };

    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    using Problem = std::vector<std::vector<Tile>>;

    std::size_t Traverse(std::size_t right, std::size_t down) const;

    Problem m_Problem;
    std::size_t m_Width;
    std::size_t m_Height;
};