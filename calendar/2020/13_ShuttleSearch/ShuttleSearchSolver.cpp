#include "ShuttleSearchSolver.h"

#include <fstream>
#include <cassert>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>

void ShuttleSearchSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    assert(inputStream.is_open());
    
    std::string header;
    std::string buses;

    bool result = bool(std::getline(inputStream, header));
    assert(result);
    m_Problem.m_EarliestTime = std::stoi(header);

    result = bool(std::getline(inputStream, buses));
    assert(result);

    std::stringstream busStream(buses);
    std::string busID;
    std::uint32_t gap { 0 };
    while (std::getline((busStream), busID, ','))
    {
        if (busID == "x")
        {
            gap++;
            continue;
        }

        m_Problem.m_BusIDs.push_back( { std::stoul(busID), gap++ });
    }

    auto largest_gap = (m_Problem.m_BusIDs.cend() - 1)->m_Gap;
    for (auto& pair : m_Problem.m_BusIDs)
    {
        // Define the gap in reverse from the last bus
        // This allows to define
        //
        // T ~= gap_i (mod bus_i)
        pair.m_Gap = largest_gap - pair.m_Gap;
    }
}

std::uint32_t ShuttleSearchSolver::SolveProblemA() const
{
    std::map<std::uint32_t, std::uint32_t> delayToBus;
    for (const auto& busWithGap : m_Problem.m_BusIDs)
    {
        auto bus = busWithGap.m_ID;
        const std::uint32_t delay = bus - (m_Problem.m_EarliestTime % bus);
        delayToBus[delay] = bus;
    }

    const auto [delay, bus] = *delayToBus.begin();
    return bus * delay;
}

std::uint64_t ShuttleSearchSolver::SolveProblemB() const
{
    auto firstBus = m_Problem.m_BusIDs.cbegin();
    std::uint64_t candidate = firstBus->m_Gap % firstBus->m_ID;
   
    std::size_t idx { 0 };
    std::uint64_t currentSummer = firstBus->m_ID;
    while (++idx < m_Problem.m_BusIDs.size())
    {
        auto currentModulus = m_Problem.m_BusIDs[idx].m_ID;
        auto currentCongruent = m_Problem.m_BusIDs[idx].m_Gap % currentModulus;
        while (candidate % currentModulus != currentCongruent)
        {
            candidate += currentSummer;
        }
        currentSummer *= currentModulus;
    }

    return candidate - firstBus->m_Gap;
}
