#include <BinaryDiagnosticSolver.h>

#include <cassert>
#include <fstream>
#include <numeric>
#include <string>

namespace aoc2021::BinaryDiagnostic
{
    std::int16_t SumBitsAt(const DiagnosticReport& report, std::size_t idx)
    {
        auto bitAccumulator = [&](std::int16_t count, const auto& reportItem) -> std::int16_t
        {
            return count + (reportItem[idx] ? 1 : -1);
        };

        return std::accumulate(report.begin(), report.end(), 0, bitAccumulator);
    }

    void BinaryDiagnosticSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        for (std::string line; std::getline(input, line); )
        {
            m_Problem.m_DiagnosticReport.emplace_back(line);
            
            assert(m_Problem.m_ReportWidth == 0 || m_Problem.m_ReportWidth == line.size());
            m_Problem.m_ReportWidth = m_Problem.m_ReportWidth == 0 ? line.size() : m_Problem.m_ReportWidth;
        }

        ComputeGammaEpsilon();
        ComputeRatings();
    }

    std::uint32_t BinaryDiagnosticSolver::SolveProblemA() const
    {
        return m_Gamma.to_ulong() * m_Epsilon.to_ulong();
    }

    std::uint32_t BinaryDiagnosticSolver::SolveProblemB() const
    {
        return m_OxygenRating.to_ulong() * m_CO2Rating.to_ulong();
    }

    void BinaryDiagnosticSolver::ComputeGammaEpsilon()
    {
        for (std::size_t i = 0; i < m_Problem.m_ReportWidth; i++)
        {
            std::int16_t sum = SumBitsAt(m_Problem.m_DiagnosticReport, i);
            m_Gamma[i] = sum > 0;
            m_Epsilon[i] = sum < 0;
        }
    }

    void BinaryDiagnosticSolver::ComputeRatings()
    {
        m_OxygenRating = ComputeRatingWithCountFilter([](std::int16_t count) { return count >= 0; });
        m_CO2Rating = ComputeRatingWithCountFilter([](std::int16_t count) { return count < 0; });
    }

    template <typename CountFilter>
    std::uint32_t BinaryDiagnosticSolver::ComputeRatingWithCountFilter(CountFilter countFilter) const
    {
        const std::size_t leftMostIndex = m_Problem.m_ReportWidth - 1;
        DiagnosticReport copiedReport { m_Problem.m_DiagnosticReport };
        
        for (std::int8_t i = leftMostIndex; i >= 0 && copiedReport.size() > 1; i--)
        {
            std::int16_t bitCount = SumBitsAt(copiedReport, i);
            const bool bitCriterium = countFilter(bitCount);
            auto criteriumFilter = [&](const auto& reportItem) { return bitCriterium != reportItem[i]; };
            std::erase_if(copiedReport, criteriumFilter);
        }

        assert(copiedReport.size() == 1);
        return copiedReport[0].to_ulong();
    }
}