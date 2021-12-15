#pragma once

#include <ProblemSolver.h>

#include <vector>
#include <unordered_map>

namespace aoc2021::HydrothermalVenture
{
    struct Point final
    {
        std::int32_t m_X { 0 };
        std::int32_t m_Y { 0 };

        auto operator<=>(const Point& other) const = default;

        inline Point operator+(const Point& other) const { return Point { m_X + other.m_X, m_Y + other.m_Y }; }
    };

    struct Line final
    {
        Line() = default;
        Line(const std::string& inputLine);

        inline bool IsHorizontal() const { return m_P1.m_Y == m_P2.m_Y; }
        inline bool IsVertical() const { return m_P1.m_X == m_P2.m_X; }
        inline bool IsDiagonal() const { return std::abs(m_P1.m_X - m_P2.m_X) == std::abs(m_P1.m_Y - m_P2.m_Y); }

        inline std::int32_t GetMinX() const { return std::min(m_P1.m_X, m_P2.m_X); }
        inline std::int32_t GetMaxX() const { return std::max(m_P1.m_X, m_P2.m_X); }
        inline std::int32_t GetMinY() const { return std::min(m_P1.m_Y, m_P2.m_Y); }
        inline std::int32_t GetMaxY() const { return std::max(m_P1.m_Y, m_P2.m_Y); }

        Point m_P1 { 0, 0 };
        Point m_P2 { 0, 0 };
    };

    using Problem = std::vector<Line>;

    class HydrothermalVentureSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;
    
    private:
        using CrossedPoints = std::unordered_map<Point, std::size_t>;

        Problem m_Problem;

        template<typename FilteredLines> 
        static std::uint32_t SolveProblemWithFilteredLines(FilteredLines&& lines);
    
        static void MarkPointsCrossedByLine(CrossedPoints& crossedPoints, const Line& line);
        static void AppendCrossedPoint(CrossedPoints& points, const Point& point);
    };
}

namespace std
{
    template<>
    struct hash<aoc2021::HydrothermalVenture::Point>
    {
        std::size_t operator()(const aoc2021::HydrothermalVenture::Point& point) const
        {
            return ((hash<std::int32_t>()(point.m_X) << 1) ^ hash<std::int32_t>()(point.m_Y)) >> 1;
        }
    };
}