#include <LanternfishSolver.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>

namespace aoc2021::Lanternfish
{
    std::size_t Simulate(AliveFishesAtLifespan& fishes, const std::size_t remainingDays)
    {
        const auto closestToHatch = std::find_if(fishes.begin(), fishes.end(), [](const auto count) { return count > 0; });
        const std::size_t hatchIndex = std::distance(fishes.begin(), closestToHatch);
        const std::size_t daysToSimulate = std::min(hatchIndex + 1, remainingDays);

        const std::uint64_t fishesToGiveBirth = *closestToHatch;
        for (std::size_t i = 0; i + daysToSimulate < MAX_FISH_LIFETIME; i++)
        {
            fishes[i] = std::exchange(fishes[i + daysToSimulate], 0);
        }

        fishes[FISH_TIMER_AFTER_GIVING_BIRTH] += fishesToGiveBirth;
        fishes[FISH_TIMER_ON_SPAWN] += fishesToGiveBirth;

        return daysToSimulate;
    }

    LanternfishSolver::LanternfishSolver()
    {
        m_StartingState.fill(0);
    }

    void LanternfishSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        std::string startingState;
        bool inputRead { std::getline(input, startingState) };
        assert(inputRead);

        std::istringstream stateStringInput { startingState };
        for (std::string ageString; std::getline(stateStringInput, ageString, ','); )
        {
            std::size_t age = std::stoi(ageString);
            assert(age < MAX_FISH_LIFETIME);

            m_StartingState[age]++;
        }
    }

    std::uint64_t LanternfishSolver::SolveProblemA() const
    {
        return EvaluateFishAfterDays(80);
    }

    std::uint64_t LanternfishSolver::SolveProblemB() const
    {
        return EvaluateFishAfterDays(256);
    }

    std::uint64_t LanternfishSolver::EvaluateFishAfterDays(const std::size_t daysToSimulate) const
    {
        AliveFishesAtLifespan aliveFishes { m_StartingState };
        for (std::size_t day = 0; day < daysToSimulate; )
        {
            day += Simulate(aliveFishes, daysToSimulate - day);
        }
        return std::accumulate(aliveFishes.begin(), aliveFishes.end(), std::uint64_t { 0 });
    }
}