#include <DumboOctopusSolver.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <ranges>
#include <string>

#include <range/v3/all.hpp>

namespace aoc2021::DumboOctopus
{
    void Grid::Init(std::istream& inputStream)
    {
        std::size_t currentRowIdx { 0 };
        for (std::string line; std::getline(inputStream, line); )
        {
            GridRow& currentRow = m_Data[currentRowIdx++];
            std::transform(std::begin(line), std::end(line), std::begin(currentRow), [](const char c) { return c - '0'; });
        }
    }

    void Grid::Simulate(std::size_t steps)
    {
        if (steps == 0)
        {
            return;
        }

        while (steps-- > 0)
        {
            Simulate();
        }
    }

    void Grid::Simulate()
    {
        m_PositionsToFlash.clear();
        m_PositionsAlreadyFlashed.clear();

        ChargeOctopuses();
        while (AreTherePendingFlashes())
        {
            FlashPendingOctopuses();
        }

        ResetFlashedOctopuses();
    }

    bool Grid::AreTherePendingFlashes()
    {
        return !m_PositionsToFlash.empty();
    }

    void Grid::FlashPendingOctopuses()
    {
        std::vector<Position> toFlashNext;

        auto isNotFlashed = [&](const Position& pos) { return !m_PositionsAlreadyFlashed.contains(pos); };
        for (auto& flashedPos : m_PositionsToFlash | std::views::filter(isNotFlashed))
        {
            std::vector<Position> adjacents = GetAdjacents(flashedPos);
            for (auto& [row, col] : adjacents | std::views::filter(isNotFlashed))
            {
                if (++m_Data[row][col] >= FLASH_THRESHOLD)
                {
                    toFlashNext.emplace_back(row, col);
                }
            }

            m_PositionsAlreadyFlashed.emplace(flashedPos);
            m_FlashCount++;
        }

        m_PositionsToFlash = std::move(toFlashNext);
    }

    void Grid::ResetFlashedOctopuses()
    {
        for (auto& [row, col] : m_PositionsAlreadyFlashed)
        {
            m_Data[row][col] = 0;
        }
    }

    std::vector<Position> Grid::GetAdjacents(const Position& pos) const
    {
        std::vector<Position> adjacents;
        adjacents.reserve(9);

        if (pos.m_X > 0) { adjacents.emplace_back(pos.m_X - 1, pos.m_Y); }
        if (pos.m_Y > 0) { adjacents.emplace_back(pos.m_X, pos.m_Y - 1); }
        if (pos.m_X < GRID_HEIGHT - 1) { adjacents.emplace_back(pos.m_X + 1, pos.m_Y); }
        if (pos.m_Y < GRID_WIDTH - 1) { adjacents.emplace_back(pos.m_X, pos.m_Y + 1); }

        if (pos.m_X > 0 && pos.m_Y > 0) { adjacents.emplace_back(pos.m_X - 1, pos.m_Y - 1); }
        if (pos.m_X > 0 && pos.m_Y < GRID_WIDTH - 1) { adjacents.emplace_back(pos.m_X - 1, pos.m_Y + 1); }
        if (pos.m_X < GRID_HEIGHT - 1 && pos.m_Y > 0) { adjacents.emplace_back(pos.m_X + 1, pos.m_Y - 1); }
        if (pos.m_X < GRID_HEIGHT - 1 && pos.m_Y < GRID_WIDTH - 1) { adjacents.emplace_back(pos.m_X + 1, pos.m_Y + 1); }

        return adjacents;
    }

    void Grid::ChargeOctopuses()
    {
        auto rowView = std::ranges::iota_view(0u, GRID_HEIGHT);
        auto colView = std::ranges::iota_view(0u, GRID_WIDTH);
        auto gridView = ranges::cartesian_product_view(rowView, colView);

        for (auto [row, col] : gridView)
        {
            if (++m_Data[row][col] >= FLASH_THRESHOLD)
            {
                m_PositionsToFlash.emplace_back(row, col);
            }
        }
    }

    void DumboOctopusSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());
        m_InitialState.Init(input);
    }

    std::size_t DumboOctopusSolver::SolveProblemA() const
    {
        Grid simulation { m_InitialState };
        simulation.Simulate(100);
        return simulation.GetFlashCount();
    }

    std::uint32_t DumboOctopusSolver::SolveProblemB() const
    {
        Grid simulation { m_InitialState };
        std::size_t lastFlashCount { 0 };
        std::size_t stepCount { 0 };

        static constexpr std::size_t TARGET_DIFF = GRID_WIDTH * GRID_HEIGHT;
        while (simulation.GetFlashCount() - lastFlashCount < TARGET_DIFF)
        {
            lastFlashCount = simulation.GetFlashCount();
            simulation.Simulate();
            stepCount++;
        }

        return stepCount;
    }
}