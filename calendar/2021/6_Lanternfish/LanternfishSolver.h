#pragma once

#include <ProblemSolver.h>

#include <array>

namespace aoc2021::Lanternfish
{
    static constexpr std::uint64_t MAX_FISH_LIFETIME { 9 };
    static constexpr std::uint64_t FISH_TIMER_ON_SPAWN { 6 };
    static constexpr std::uint64_t FISH_TIMER_AFTER_GIVING_BIRTH { 8 };

    using AliveFishesAtLifespan = std::array<std::uint64_t, MAX_FISH_LIFETIME>;

    class LanternfishSolver : public ProblemSolver<std::string, std::uint64_t, std::uint64_t>
    {
    public:
        LanternfishSolver();

        void Init(std::string& input) override;
        std::uint64_t SolveProblemA() const override;
        std::uint64_t SolveProblemB() const override;
     
    private:
        AliveFishesAtLifespan m_StartingState;

        std::uint64_t EvaluateFishAfterDays(const std::size_t daysToSimulate) const;
    };
}