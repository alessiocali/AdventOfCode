#include <TreacheryOfWhalesSolver.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>

namespace aoc2021::TreacheryOfWhales
{
    void TreacheryOfWhalesSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        std::string inputLine;
        bool inputRead { std::getline(input, inputLine) };
        assert(inputRead);

        std::istringstream inputStringStream { inputLine };
        for (std::string crabLine; std::getline(inputStringStream, crabLine, ','); )
        {
            m_Problem.emplace_back(std::stoi(crabLine));
        }

        std::sort(m_Problem.begin(), m_Problem.end());
    }

    std::uint64_t TreacheryOfWhalesSolver::SolveProblemA() const
    {
        assert(!m_Problem.empty());

        auto medianIt = m_Problem.begin() + (m_Problem.size() / 2);
        std::int32_t median = *medianIt;

        auto accumulateCrabs = [median](const uint64_t currentDistance, const std::int32_t currentCrab)
        {
            return currentDistance + static_cast<uint64_t>(std::abs(currentCrab - median));
        };

        return std::accumulate(m_Problem.begin(), m_Problem.end(), std::uint64_t { 0 }, accumulateCrabs);
    }

    std::uint64_t TreacheryOfWhalesSolver::SolveProblemB() const
    {
        std::int32_t currentPosition = *m_Problem.begin();

        const std::int32_t first = *m_Problem.begin();
        const std::int32_t last = *m_Problem.rbegin();

        auto computeCostAtPosition = [&](const std::int32_t position) -> std::uint64_t
        {
            auto accumulateCrabs = [&](const std::uint64_t totalCost, const std::int32_t currentCrab) -> std::uint64_t
            {
                const std::uint64_t offset = static_cast<std::uint64_t>(std::abs(currentCrab - position));
                const std::uint64_t cost = offset * (offset + 1) / 2;
                return totalCost + cost;
            };

            return std::accumulate(m_Problem.begin(), m_Problem.end(), std::uint64_t { 0 }, accumulateCrabs);
        };

        std::uint64_t currentCost = computeCostAtPosition(currentPosition);
        std::uint64_t nextCost = computeCostAtPosition(++currentPosition);
        
        while (nextCost < currentCost && currentPosition < last)
        {
            currentCost = std::exchange(nextCost, computeCostAtPosition(++currentPosition));
        }

        return currentCost;
    }
}