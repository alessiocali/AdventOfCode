#include "DockingDataSolver.h"

#include <fstream>
#include <string>
#include <cassert>
#include <regex>
#include <numeric>

void DockingDataSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    assert(inputStream.is_open());
    for (std::string line; std::getline(inputStream, line); )
    {
        m_Problem.push_back(line);
    }
}

std::uint64_t DockingDataSolver::SolveProblemA() const
{
    Instance problemInstance;
    for (const auto& line : m_Problem)
    {
        Execute(line, problemInstance);
    }

    return std::accumulate(problemInstance.m_Memory.begin(), problemInstance.m_Memory.end(), 0ULL, [](const auto current, const auto& pair) { return current + pair.second; });
}

std::uint64_t DockingDataSolver::SolveProblemB() const
{
    Instance problemInstance;
    for (const auto& line : m_Problem)
    {
        Execute(line, problemInstance, ExecutionType::V2);
    }

    return std::accumulate(problemInstance.m_Memory.begin(), problemInstance.m_Memory.end(), 0ULL, [](const auto current, const auto& pair) { return current + pair.second; });

}

void DockingDataSolver::Execute(const std::string& instruction, DockingDataSolver::Instance& instance, const ExecutionType executionType) const
{
    std::smatch match;
    if (std::regex_match(instruction, match, std::regex { R"(mask = ((?:X|1|0){36}))" }))
    {
        UpdateMask(instance, match[1]);
    }
    else if (std::regex_match(instruction, match, std::regex { R"(mem\[(\d+)\] = (\d+))" }))
    {
        UpdateMemory(instance, std::stoull(match[1]), std::stoull(match[2]), executionType);
    }
}

void DockingDataSolver::UpdateMask(DockingDataSolver::Instance& instance, const std::string& maskString) const 
{
    instance.m_FloatMask =      { 0x000000000 };
    instance.m_OneOrMask =      { 0x000000000 };
    instance.m_ZeroAndMask =    { 0xFFFFFFFFF };

    for (auto rit = maskString.rbegin(); rit != maskString.rend(); rit++)
    {
        auto idx = std::distance(maskString.rbegin(), rit);

        if (*rit == 'X')
        {
            instance.m_FloatMask.set(idx);
        }
        else if (*rit == '1')
        {
            instance.m_OneOrMask.set(idx);
        }
        else if (*rit == '0')
        {
            instance.m_ZeroAndMask.reset(idx);
        }
        else
        {
            assert(false && "Invalid mask value");
        }
    }
}

void DockingDataSolver::UpdateMemory(DockingDataSolver::Instance& instance, std::uint64_t address, std::uint64_t value, const ExecutionType executionType) const
{
    if (executionType == ExecutionType::V1)
    {
        instance.m_Memory[address] = (value & instance.m_ZeroAndMask.to_ullong()) | instance.m_OneOrMask.to_ullong();
    }
    else if (executionType == ExecutionType::V2)
    {
        // Zero mask has no effect in ExecType V2
        auto baseAddress = address | instance.m_OneOrMask.to_ullong();
        std::vector<std::uint64_t> addressesToSet;
        RecursiveAddAddresses(baseAddress, addressesToSet, instance.m_FloatMask);

        for (const auto address : addressesToSet)
        {
            instance.m_Memory[address] = value;
        }
    }
    else
    {
        assert(false && "Unknown execution type");
    }
}

void DockingDataSolver::RecursiveAddAddresses(std::uint64_t baseAddress, std::vector<std::uint64_t>& addresses, DockingDataSolver::PartialMask floatMask) const
{
    std::size_t i = 0;
    while (i < floatMask.size() && !floatMask.test(i) ) { i++; }
    if (i == floatMask.size()) 
    { 
        // End of recursion, add the found address
        addresses.push_back(baseAddress);
        return; 
    }

    PartialMask nextMask { floatMask };
    nextMask.reset(i);

    std::bitset<64> baseAddressAsMask { baseAddress };
    baseAddressAsMask.reset(i);
    RecursiveAddAddresses(baseAddressAsMask.to_ullong(), addresses, nextMask);
    baseAddressAsMask.set(i);
    RecursiveAddAddresses(baseAddressAsMask.to_ullong(), addresses, nextMask);
}