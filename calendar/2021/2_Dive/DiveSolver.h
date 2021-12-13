#pragma once
#include <ProblemSolver.h>

#include <string>
#include <vector>

namespace aoc2021::Dive
{
    struct Instruction
    {
        std::string m_Direction;
        std::int32_t m_Value;
    };

    struct Position
    {
        std::int32_t m_Horizontal { 0 };
        std::int32_t m_Depth { 0 };
        std::int32_t m_Aim { 0 };
    };

    void ApplyInstruction(Position& position, const Instruction& instruction);
    void ApplyRevisedInstruction(Position& position, const Instruction& instruction);

    class DiveSolver : public ProblemSolver<std::string, std::int32_t, std::int32_t>
    {
    public:
        void Init(std::string& input) override;
        std::int32_t SolveProblemA() const override;
        std::int32_t SolveProblemB() const override;

    private:
        std::vector<Instruction> m_Instructions;

        template<typename InstructionInterpreter>
        std::int32_t SolveWithInterpreter(InstructionInterpreter interpreter) const;
    };
}