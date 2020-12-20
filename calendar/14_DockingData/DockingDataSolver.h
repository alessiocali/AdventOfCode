#pragma once

#include <ProblemSolver.h>

#include <unordered_map>
#include <bitset>
#include <vector>

class DockingDataSolver : public ProblemSolver<std::string, std::uint64_t, std::uint64_t>
{
public:
    void Init(std::string& input) override;
    std::uint64_t SolveProblemA() const override;
    std::uint64_t SolveProblemB() const override;

private:
    using Memory = std::unordered_map<std::uint64_t, std::uint64_t>;
    using PartialMask = std::bitset<36>;
    using Problem = std::vector<std::string>;

    enum class ExecutionType
    {
        V1, V2
    };

    struct Instance
    {
        Memory m_Memory;
        PartialMask m_FloatMask     { 0x000000000 };
        PartialMask m_ZeroAndMask   { 0xFFFFFFFFF };
        PartialMask m_OneOrMask     { 0x000000000 };
    };

    Problem m_Problem;

    void Execute(const std::string& instruction, DockingDataSolver::Instance& instance, const ExecutionType executionType = ExecutionType::V1) const;
    void UpdateMask(DockingDataSolver::Instance& instance, const std::string& maskString) const;
    void UpdateMemory(DockingDataSolver::Instance& instance, std::uint64_t address, std::uint64_t value, const ExecutionType executionType) const;
    void RecursiveAddAddresses(std::uint64_t baseAddress, std::vector<std::uint64_t>& addresses, DockingDataSolver::PartialMask floatMask) const;
};