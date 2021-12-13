#include "RambunctiousRecitationSolver.h"

#include <fstream>
#include <sstream>
#include <optional>

void RambunctiousRecitationSolver::Init(std::string& input)
{
    std::stringstream inputStream(input);
    for (std::string num; std::getline(inputStream, num, ','); )
    {
        m_Problem.push_back(std::stoi(num));
    }
}

std::uint64_t RambunctiousRecitationSolver::SolveProblemA() const
{
    return GetSpokenNumber(2020);
}

std::uint64_t RambunctiousRecitationSolver::SolveProblemB() const
{
    return GetSpokenNumber(30000000);
}

std::uint64_t RambunctiousRecitationSolver::GetSpokenNumber(std::size_t idx) const
{
    MemoryMap map { };
    std::size_t turn { 1 };
    std::optional<std::uint64_t> lastSpoken;
    for (const auto init : m_Problem)
    {
        if (lastSpoken)
        {
            map[*lastSpoken] = turn++;
        }

        lastSpoken = init;
    }

    std::uint64_t nextSpoken { 0 };
    while (turn < idx)
    {
        if (map.count(*lastSpoken))
        {
            nextSpoken = turn - map[*lastSpoken];
        }
        else
        {
            nextSpoken = 0;
        }

        map[*lastSpoken] = turn++;
        lastSpoken = nextSpoken;
    }

    return *lastSpoken;
}

