#include "ReportRepairSolver.h"

#include <fstream>

void ReportRepairSolver::Init(std::string& input)
{
    m_Problem.clear();

    std::ifstream inputStream(input);
    std::uint32_t temp;
    while (inputStream >> temp)
    {
        m_Problem.emplace(temp);
    }
}

std::uint32_t ReportRepairSolver::SolveProblemA() const
{
    constexpr std::uint32_t TARGET_VALUE = 2020;
    for (std::uint32_t currentValue : m_Problem)
    {
        const std::uint32_t desiredValue = TARGET_VALUE - currentValue;
        if (m_Problem.count(desiredValue) > 0)
        {
            // The desired value is in the set, so it's what we are looking for
            return desiredValue * currentValue;
        }
    }

    return 0;
}

std::uint32_t ReportRepairSolver::SolveProblemB() const
{
    constexpr std::uint32_t TARGET_VALUE = 2020;
    for (std::uint32_t currentValue : m_Problem)
    {
        const std::uint32_t desiredSum = TARGET_VALUE - currentValue;
        for (std::uint32_t currentSubValue : m_Problem)
        {
            const std::uint32_t desiredValue = desiredSum - currentSubValue;
            if (m_Problem.count(desiredValue) > 0)
            {
                return desiredValue * currentSubValue * currentValue;
            }
        }
    }

    return 0;
}
