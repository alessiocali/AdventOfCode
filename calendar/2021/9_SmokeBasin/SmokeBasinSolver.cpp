#include <SmokeBasinSolver.h>

#include <cassert>
#include <fstream>
#include <numeric>
#include <ranges>
#include <string>

#include <range/v3/all.hpp>

namespace aoc2021::SmokeBasin
{
    void FloorHeightMap::Init(std::istream& inputStream)
    {
        auto charToInteger = [](const char c) { return c - '0'; };

        for (std::string line; std::getline(inputStream, line); )
        {
            auto& heatmapRow = m_Data.emplace_back();
            heatmapRow.reserve(line.size());
            std::transform(std::begin(line), std::end(line), std::back_inserter(heatmapRow), charToInteger);
        }

        assert(!m_Data.empty());
        m_Height = m_Data.size();

        assert(!m_Data[0].empty());
        m_Width = m_Data[0].size();
    }

    bool FloorHeightMap::IsLocalMinimum(const Coordinate& coordinate) const
    {
        std::vector<Coordinate> neighbours = GetNeighbours(coordinate);
        std::uint8_t target = GetValueAt(coordinate);
        auto greaterThanTarget = [&](const Coordinate& neihgbour) { return GetValueAt(neihgbour) > target; };
        return std::all_of(std::begin(neighbours), std::end(neighbours), greaterThanTarget);
    }

    std::vector<Coordinate> FloorHeightMap::GetNeighbours(const Coordinate& coordinate) const
    {
        std::vector<Coordinate> neighbours;
        neighbours.reserve(4);

        if (coordinate.m_Col > 0) { neighbours.emplace_back(coordinate.m_Row, coordinate.m_Col - 1); }
        if (coordinate.m_Col < m_Width - 1) { neighbours.emplace_back(coordinate.m_Row, coordinate.m_Col + 1); }
        if (coordinate.m_Row > 0) { neighbours.emplace_back(coordinate.m_Row - 1, coordinate.m_Col); }
        if (coordinate.m_Row < m_Height - 1) { neighbours.emplace_back(coordinate.m_Row + 1, coordinate.m_Col); }
    
        return neighbours;
    }

    std::vector<Coordinate> FloorHeightMap::GetLocalMinima() const
    {
        auto rowView = std::ranges::iota_view(0u, GetHeight());
        auto colView = std::ranges::iota_view(0u, GetWidth());
        auto gridView = ranges::cartesian_product_view(rowView, colView);

        auto toCoordinate = [](auto&& pair) { return Coordinate { std::get<0>(pair), std::get<1>(pair) }; };
        auto isLocalMinimum = [&](const Coordinate& coordinate) { return IsLocalMinimum(coordinate); };

        return gridView | std::views::transform(toCoordinate) | std::views::filter(isLocalMinimum) | ranges::to_vector;
    }

    std::unordered_set<Coordinate> FloorHeightMap::GetBasinAround(const Coordinate& coordinate) const
    {
        std::unordered_set<Coordinate> basin;
        basin.emplace(coordinate);

        std::vector<Coordinate> toExplore;
        auto exploreNeighbours = [&](const Coordinate& exploredCoordinate)
        {
            std::vector<Coordinate> neighbours = GetNeighbours(exploredCoordinate);
            toExplore.insert(std::begin(toExplore), std::begin(neighbours), std::end(neighbours));
        };

        exploreNeighbours(coordinate);
        while (!toExplore.empty())
        {
            const Coordinate currentlyExplored = toExplore.back();
            toExplore.pop_back();

            if (basin.contains(currentlyExplored) || GetValueAt(currentlyExplored) == BASIN_BORDER_VALUE)
            {
                continue;
            }

            basin.emplace(currentlyExplored);
            exploreNeighbours(currentlyExplored);
        }

        return basin;
    }

    void SmokeBasinSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());
        m_HeightMap.Init(input);
    }

    std::uint32_t SmokeBasinSolver::SolveProblemA() const
    {
        std::vector<Coordinate> localMinima = m_HeightMap.GetLocalMinima();

        auto toRiskLevel = [&](const Coordinate& coordinate) -> std::uint32_t { return m_HeightMap.GetValueAt(coordinate) + 1; };
        auto riskLevelsView = localMinima | std::views::transform(toRiskLevel);
        
        return std::accumulate(std::begin(riskLevelsView), std::end(riskLevelsView), std::uint32_t { 0 });
    }

    std::uint32_t SmokeBasinSolver::SolveProblemB() const
    {
        std::vector<Coordinate> localMinima = m_HeightMap.GetLocalMinima();
        auto coordinateToBasin = [&](const Coordinate& coordinate) { return m_HeightMap.GetBasinAround(coordinate); };
        auto projectToSize = [](const auto&& c1) { return c1.size(); };

        static constexpr std::size_t BASINS_TO_TAKE { 3 };

        std::vector<std::size_t> basinSizes = localMinima | std::views::transform(coordinateToBasin) | std::views::transform(projectToSize) | ranges::to_vector;
        std::partial_sort(std::begin(basinSizes), std::begin(basinSizes) + BASINS_TO_TAKE, std::end(basinSizes), std::greater {});
        auto largestBasinSizes = basinSizes | std::views::take(BASINS_TO_TAKE);
        return std::accumulate(std::begin(largestBasinSizes), std::end(largestBasinSizes), std::size_t { 1 }, std::multiplies {});
    }
}