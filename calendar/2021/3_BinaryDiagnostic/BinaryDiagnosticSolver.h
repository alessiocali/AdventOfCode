#pragma once

#include <ProblemSolver.h>

#include <bitset>
#include <vector>

namespace aoc2021::BinaryDiagnostic
{
    static constexpr std::size_t MAX_BITSET_SIZE { 32 };

    using DiagnosticReport = std::vector<std::bitset<MAX_BITSET_SIZE>>;

    std::int16_t SumBitsAt(const DiagnosticReport& report, std::size_t idx);

    struct Problem
    {
        DiagnosticReport m_DiagnosticReport;
        std::int32_t m_ReportWidth { 0 };
    };

    class BinaryDiagnosticSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        Problem m_Problem;

        // Most common bits
        std::bitset<MAX_BITSET_SIZE> m_Gamma;
        // Least common bits
        std::bitset<MAX_BITSET_SIZE> m_Epsilon;

        std::bitset<MAX_BITSET_SIZE> m_OxygenRating;
        std::bitset<MAX_BITSET_SIZE> m_CO2Rating;

        void ComputeGammaEpsilon();
        void ComputeRatings();
        
        template <typename CountFilter> std::uint32_t ComputeRatingWithCountFilter(CountFilter countFilter) const;
    };
}