#include "AdapterArraySolver.h"

#include <fstream>
#include <string>
#include <algorithm>
#include <array>
#include <cassert>
#include <unordered_set>

std::uint64_t Factorial(std::uint64_t val)
{
    if (val <= 1)
    {
        return val;
    }

    return val * Factorial(val - 1);
}

void AdapterArraySolver::Init(std::string& input)
{
    m_Problem.push_back(0); // The outlet

    std::ifstream inputStream(input);
    std::string temp;
    while (std::getline(inputStream, temp))
    {
        m_Problem.push_back(std::stoul(temp));
    }

    std::sort(m_Problem.begin(), m_Problem.end());
    std::uint32_t lastValue = *(m_Problem.end() - 1);
    m_Problem.push_back(lastValue + 3);
}

std::uint32_t AdapterArraySolver::SolveProblemA() const
{
    std::array<std::uint32_t, 3> gapCounts { };
    std::fill(gapCounts.begin(), gapCounts.end(), 0);

    for (auto current = m_Problem.begin(), next = m_Problem.begin() + 1; next < m_Problem.end(); current++, next++)
    {
        std::size_t gap = *next - *current;
        assert(1 <= gap && gap <= 3);
        gapCounts[gap - 1]++;
    }

    return gapCounts[0] * gapCounts[2];
}

std::uint64_t AdapterArraySolver::SolveProblemB() const
{
    return 0;
}

std::uint64_t AdapterArraySolver::CountRemovableAdapters(std::unordered_set<uint32_t>& holes) const
{
    return 0;
    //std::vector<std::uint32_t> removables;

    //auto current = m_Problem.cbegin() + 1;

    //while (current != m_Problem.cend())
    //{
    //    current++;
    //    if (current == m_Problem.cend())
    //    {
    //        break;
    //    }

    //    if (holes.count(*current) || holes.count)
    //    {
    //        continue;
    //    }

    //    std::uint32_t gap = *current - *(current - 2);
    //    if (gap <= 3)
    //    {
    //        removables.push_back(*(current - 1));
    //    }
    //}

    //if (removables.empty())
    //{
    //    return 1;
    //}

    //std::uint64_t combinations { 0 };
    //for (std::uint32_t val : removables)
    //{
    //    std::unordered_set<std::uint32_t> newHoles(holes);
    //    newHoles.insert(val);
    //}
}
