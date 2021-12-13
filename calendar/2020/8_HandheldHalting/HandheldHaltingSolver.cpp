#include "HandheldHaltingSolver.h"

#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <cassert>

HandheldComputer::InstructionSet HandheldComputer::ms_InstructionSet =
{
    { std::string("acc") , &HandheldComputer::Accumulate    },
    { std::string("jmp") , &HandheldComputer::Jump          },
    { std::string("nop") , &HandheldComputer::Nop           }
};

void HandheldComputer::Init(std::istream& input)
{
    std::regex INSTRUCTION_REGEX(R"((\w{3}) ((\+|\-)\d+))");

    std::string temp;
    std::smatch match;
    while (std::getline(input, temp))
    {
        if (std::regex_match(temp, match, INSTRUCTION_REGEX))
        {
            m_Program.emplace_back(Instruction { match[1], std::stoi(match[2]) });
        }
    }
}

void HandheldComputer::FlipNopOrJumpAt(std::size_t pointer)
{
    std::string& code = m_Program[pointer].m_Code;
    
    if (code == "jmp")
    {
        code = "nop";
    }
    else if (code == "nop")
    {
        code = "jmp";
    }
    else
    {
        assert(false && "Not JMP or NOP");
    }
}

void HandheldComputer::Step()
{
    const Instruction& current = m_Program[m_InstructionPointer];
    (this->*ms_InstructionSet[current.m_Code])(current.m_Value);
}

void HandheldComputer::Accumulate(const std::int32_t value)
{
    m_Accumulator += value;
    m_InstructionPointer++;
}

void HandheldComputer::Jump(const std::int32_t value)
{
    m_InstructionPointer += value;
}

void HandheldComputer::Nop(const std::int32_t value)
{
    m_InstructionPointer++;
}

void HandheldHaltingSolver::Init(std::string& input)
{
    m_Computer.Init(std::ifstream(input));
}

std::uint32_t HandheldHaltingSolver::SolveProblemA() const
{
    std::unordered_set<std::size_t> executedInstructions;
    HandheldComputer instance = m_Computer;

    ExecuteUntilLoopOrTermination(instance);
    return instance.GetAccumulator();
}

std::uint32_t HandheldHaltingSolver::SolveProblemB() const
{
    HandheldComputer instance { m_Computer };

    auto tryExecute = [](HandheldComputer& computer)
    {
        computer.Reset();
        ExecuteUntilLoopOrTermination(computer);
        return computer.HasTerminated();
    };

    for (std::size_t i = 0; i < instance.GetProgramSize(); i++)
    {
        if (instance.GetInstructionAt(i).m_Code == "acc")
        {
            continue;
        }

        instance.FlipNopOrJumpAt(i);
        if (tryExecute(instance))
        {
            return instance.GetAccumulator();
        }
        instance.FlipNopOrJumpAt(i);    // Restore old instruction
    }

    return 0;
}

void HandheldHaltingSolver::ExecuteUntilLoopOrTermination(HandheldComputer& computer)
{
    std::unordered_set<std::size_t> executedInstructions;

    while (executedInstructions.count(computer.GetInstructionPointer()) == 0 && !computer.HasTerminated())
    {
        executedInstructions.insert(computer.GetInstructionPointer());
        computer.Step();
    }
}
