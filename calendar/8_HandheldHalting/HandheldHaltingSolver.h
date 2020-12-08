#pragma once

#include <ProblemSolver.h>
#include <vector>
#include <unordered_map>

class HandheldComputer
{
private:
    struct Instruction
    {
        std::string m_Code;
        std::int32_t m_Value;
    };

public:
    void Init(std::istream& input);

    std::size_t GetInstructionPointer() const { return m_InstructionPointer; }
    std::int32_t GetAccumulator() const { return m_Accumulator; }

    void Reset() { m_InstructionPointer = 0; m_Accumulator = 0; }

    std::size_t GetProgramSize() const { return m_Program.size(); }
    const Instruction& GetInstructionAt(std::size_t pointer) const { return m_Program[pointer]; }
    bool HasTerminated() const { return m_InstructionPointer >= m_Program.size(); }
    void FlipNopOrJumpAt(std::size_t pointer);

    void Step();

private:

    using Program = std::vector<Instruction>;
    using Function = void(HandheldComputer::*)(const std::int32_t);
    using InstructionSet = std::unordered_map<std::string, Function>;

    Program         m_Program;
    
    std::size_t     m_InstructionPointer    { 0 };
    std::int32_t    m_Accumulator           { 0 };

    static InstructionSet ms_InstructionSet;

    void Accumulate(const std::int32_t value);
    void Jump(const std::int32_t value);
    void Nop(const std::int32_t value);
};

class HandheldHaltingSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;

private:
    HandheldComputer m_Computer;

    static void ExecuteUntilLoopOrTermination(HandheldComputer& computer);
};