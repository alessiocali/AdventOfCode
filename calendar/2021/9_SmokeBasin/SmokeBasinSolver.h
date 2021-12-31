#pragma once

#include <ProblemSolver.h>

#include <cstddef>
#include <vector>
#include <unordered_set>

namespace aoc2021::SmokeBasin
{
    static constexpr std::uint8_t BASIN_BORDER_VALUE { 9 };

    struct Coordinate
    {
        std::size_t m_Row { 0 };
        std::size_t m_Col { 0 };

        auto operator<=>(const Coordinate& other) const = default;
    };

    class FloorHeightMap final
    {
    public:
        void Init(std::istream& inputStream);

        inline std::size_t GetWidth() const { return m_Width; }
        inline std::size_t GetHeight() const { return m_Height; }

        inline std::uint8_t GetValueAt(const Coordinate& coordinate) const { return m_Data[coordinate.m_Row][coordinate.m_Col]; }
        
        std::vector<Coordinate> GetLocalMinima() const;
        std::unordered_set<Coordinate> GetBasinAround(const Coordinate& coordinate) const;

        bool IsLocalMinimum(const Coordinate& coordinate) const;
        std::vector<Coordinate> GetNeighbours(const Coordinate& coordinate) const;
    
    private:
        std::vector<std::vector<std::uint8_t>> m_Data;

        std::size_t m_Width { 0 };
        std::size_t m_Height { 0 };
    };

    class SmokeBasinSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        FloorHeightMap m_HeightMap;
    };
}

namespace std
{
    template<>
    struct hash<aoc2021::SmokeBasin::Coordinate>
    {
        inline std::size_t operator()(const aoc2021::SmokeBasin::Coordinate& coordinate) const 
        { 
            return ((hash<std::size_t>()(coordinate.m_Row) << 1) ^ hash<std::size_t>()(coordinate.m_Col)) >> 1;
        }
    };
}