#include <DiveSolver.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <format>

namespace aoc2021::Dive
{
    void ApplyInstruction(Position& position, const Instruction& instruction)
    {
        if (instruction.m_Direction == "forward")
        {
            position.m_Horizontal += instruction.m_Value;
        }
        else if (instruction.m_Direction == "up")
        {
            position.m_Depth -= instruction.m_Value;
        }
        else if (instruction.m_Direction == "down")
        {
            position.m_Depth += instruction.m_Value;
        }
        else
        {
            assert(false && std::format("Unknown direction {}", instruction.m_Direction).c_str());
        }
    }

    void ApplyRevisedInstruction(Position& position, const Instruction& instruction)
    {
        if (instruction.m_Direction == "forward")
        {
            position.m_Horizontal += instruction.m_Value;
            position.m_Depth += instruction.m_Value * position.m_Aim;
        }
        else if (instruction.m_Direction == "up")
        {
            position.m_Aim -= instruction.m_Value;
        }
        else if (instruction.m_Direction == "down")
        {
            position.m_Aim += instruction.m_Value;
        }
        else
        {
            assert(false && std::format("Unknown direction {}", instruction.m_Direction).c_str());
        }
    }

    void DiveSolver::Init(std::string& inputFileName)
    {
        std::ifstream inputFile { inputFileName };
        assert(inputFile.is_open());

        Instruction instruction;
        while (inputFile >> instruction.m_Direction >> instruction.m_Value)
        {
            m_Instructions.emplace_back(instruction);
        }
    }

    std::int32_t DiveSolver::SolveProblemA() const
    {
        return SolveWithInterpreter(&ApplyInstruction);
    }

    std::int32_t DiveSolver::SolveProblemB() const
    {
        return SolveWithInterpreter(&ApplyRevisedInstruction);
    }

    template<typename InstructionInterpreter>
    std::int32_t DiveSolver::SolveWithInterpreter(InstructionInterpreter interpreter) const
    {
        Position position;
        auto applyInstruction = [&](auto instruction) { interpreter(position, instruction); };
        std::for_each(m_Instructions.begin(), m_Instructions.end(), applyInstruction);
        return position.m_Depth * position.m_Horizontal;
    }
}

