#include <SonarSweepSolver.h>

#include <algorithm>
#include <cassert>
#include <format>
#include <fstream>
#include <numeric>
#include <string>

namespace aoc2021::SonarSweep
{
    template<typename Container>
    std::size_t CountIncreases(const Container& container)
    {
        std::vector<int> differences;
        differences.reserve(container.size());

        std::adjacent_difference(container.begin(), container.end(), std::back_inserter(differences));
        auto isPositive = [](auto val) { return val > 0; };
        return std::count_if(differences.begin(), differences.end(), isPositive);
    }

    void SonarSweepSolver::Init(std::string& inputFileName)
    {
        std::ifstream inputFile { inputFileName };
        assert(inputFile.is_open());

        for (std::string nextLine; std::getline(inputFile, nextLine); )
        {
            m_Report.emplace_back(std::stoi(nextLine));
        }
    }

    std::uint32_t SonarSweepSolver::SolveProblemA() const
    {
        return CountIncreases(m_Report);
    }

    std::uint32_t SonarSweepSolver::SolveProblemB() const
    {
        assert(m_Report.size() >= 3);

        std::vector<int> windows;
        windows.reserve(m_Report.size());

        for (auto windowFirst = m_Report.cbegin(), windowLast = windowFirst + 2; windowLast != m_Report.cend(); windowFirst++, windowLast++)
        {
            windows.emplace_back(std::accumulate(windowFirst, windowLast + 1, 0));
        }

        return CountIncreases(windows);
    }

}