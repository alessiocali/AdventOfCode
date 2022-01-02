#pragma once

#include <CommonHelpers.h>
#include <ProblemSolver.h>

#include <array>
#include <unordered_set>
#include <vector>

namespace aoc2021::DumboOctopus
{
    static constexpr std::size_t GRID_WIDTH { 10 };
    static constexpr std::size_t GRID_HEIGHT { 10 };

    static constexpr std::uint8_t FLASH_THRESHOLD { 10 };

    using GridRow = std::array<std::uint8_t, GRID_WIDTH>;
    using GridData = std::array<GridRow, GRID_HEIGHT>;

    class Grid final
    {
    public:
        Grid() = default;
        Grid(const Grid& other) = default;
        Grid(Grid&& other) = default;

        Grid& operator=(const Grid& other) = default;
        Grid& operator=(Grid&& other) = default;

        void Init(std::istream& inputStream);

        void Simulate(std::size_t steps);
        void Simulate();

        inline std::size_t GetFlashCount() const { return m_FlashCount; }

    private:
        GridData m_Data;
        std::size_t m_FlashCount { 0 };
        std::vector<Position> m_PositionsToFlash;
        std::unordered_set<Position> m_PositionsAlreadyFlashed;

        void ChargeOctopuses();
        bool AreTherePendingFlashes();
        void FlashPendingOctopuses();
        void ResetFlashedOctopuses();

        std::vector<Position> GetAdjacents(const Position& pos) const;
    };

    class DumboOctopusSolver : public ProblemSolver<std::string, std::size_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::size_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        Grid m_InitialState;
    };
}