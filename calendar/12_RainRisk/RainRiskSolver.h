#pragma once

#include <ProblemSolver.h>

#include <unordered_set>
#include <SFML/System/Vector2.hpp>

enum class InstructionType
{
    MoveCardinal,
    Rotate,
    Forward
};

struct Instruction
{
    InstructionType m_Type;
    int m_Value;
    sf::Vector2i m_Direction;
};

class RainRiskSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;

private:
    using Problem = std::vector<Instruction>;
    Problem m_Problem;
};