#include <HydrothermalVentureSolver.h>

#include <cassert>
#include <format>
#include <fstream>
#include <ranges>
#include <regex>
#include <string>

namespace aoc2021::HydrothermalVenture
{

    Line::Line(const std::string& inputLine)
    {
        static const std::regex LINE_REGEX { R"((\d+),(\d+) -> (\d+),(\d+))" };
        std::smatch match;

        if (std::regex_match(inputLine, match, LINE_REGEX))
        {
            m_P1.m_X = std::stoi(match[1]);
            m_P1.m_Y = std::stoi(match[2]);
            m_P2.m_X = std::stoi(match[3]);
            m_P2.m_Y = std::stoi(match[4]);
        }
        else
        {
            assert(false && std::format("Invalid Line String: {}", inputLine).c_str());
        }
    }

    void HydrothermalVentureSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        for (std::string line; std::getline(input, line); )
        {
            m_Problem.emplace_back(line);
        }
    }

    std::uint32_t HydrothermalVentureSolver::SolveProblemA() const
    {     
        auto isStraight = [](const Line& line) { return line.IsHorizontal() || line.IsVertical(); };
        return SolveProblemWithFilteredLines(m_Problem | std::views::filter(isStraight));
    }

    std::uint32_t HydrothermalVentureSolver::SolveProblemB() const
    {
        return SolveProblemWithFilteredLines(m_Problem);
    }

    template<typename FilteredLines>
    std::uint32_t HydrothermalVentureSolver::SolveProblemWithFilteredLines(FilteredLines&& lines)
    {
        std::unordered_map<Point, std::size_t> pointsCrossedByLines;

        for (const Line& line : lines)
        {
            MarkPointsCrossedByLine(pointsCrossedByLines, line);
        }

        auto geqTwo = [](const auto val) { return val >= 2; };
        auto atLeastTwo = pointsCrossedByLines | std::views::values | std::views::filter(geqTwo);
        return std::distance(atLeastTwo.begin(), atLeastTwo.end());
    }

    void HydrothermalVentureSolver::MarkPointsCrossedByLine(CrossedPoints& crossedPoints, const Line& line)
    {
        std::int32_t xDir = line.m_P2.m_X - line.m_P1.m_X;
        std::int32_t yDir = line.m_P2.m_Y - line.m_P1.m_Y;

        xDir /= std::max(std::abs(xDir), 1);
        yDir /= std::max(std::abs(yDir), 1);

        Point direction { xDir, yDir };
        Point last = line.m_P2 + direction;

        for (Point pt = line.m_P1; pt != last; pt = pt + direction)
        {
            AppendCrossedPoint(crossedPoints, pt);
        }
    }

    void HydrothermalVentureSolver::AppendCrossedPoint(CrossedPoints& crossedPoints, const Point& point)
    {
        if (crossedPoints.count(point) == 0)
        {
            crossedPoints[point] = 1;
        }
        else
        {
            crossedPoints[point]++;
        }
    }
}