#include <TransparentOrigamiSolver.h>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <regex>
#include <string>

namespace aoc2021::TransparentOrigami
{
    FoldUp::FoldUp(const int y)
        : m_Y(y)
    { }

    HoledSheet FoldUp::ApplyTo(const HoledSheet& sheet) const
    { 
        auto isAbove = [&](const Position& pos) { return pos.m_Y < m_Y; };
        auto flipHoleUp = [&](const Position& pos) { return Position { pos.m_X, 2 * m_Y - pos.m_Y }; };
        return FilterAndTransform(sheet, isAbove, flipHoleUp);
    }

    FoldLeft::FoldLeft(const int x)
        : m_X(x)
    { }

    HoledSheet FoldLeft::ApplyTo(const HoledSheet& sheet) const
    {
        auto isLeft = [&](const Position& pos) { return pos.m_X < m_X; };
        auto flipHoleLeft = [&](const Position& pos) { return Position { 2 * m_X - pos.m_X, pos.m_Y }; };
        return FilterAndTransform(sheet, isLeft, flipHoleLeft);
    }

    std::string MakePrintable(const HoledSheet& sheet)
    {
        auto sortByX = [](const Position& pos1, const Position& pos2) { return pos1.m_X < pos2.m_X; };
        auto sortByY = [](const Position& pos1, const Position& pos2) { return pos1.m_Y < pos2.m_Y; };

        const int maxX = std::max_element(std::begin(sheet), std::end(sheet), sortByX)->m_X + 1;
        const int maxY = std::max_element(std::begin(sheet), std::end(sheet), sortByY)->m_Y + 1;

        const std::string emptyLine(maxX, '.');
        std::vector<std::string> lines(maxY);
        std::fill(std::begin(lines), std::end(lines), emptyLine);

        for (const Position& hole : sheet)
        {
            lines[hole.m_Y][hole.m_X] = '#';
        }

        return ranges::accumulate(lines | ranges::view::intersperse(std::string { "\n" }), std::string { "\n\n" });
    }

    void TransparentOrigamiSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        static const std::regex HOLE_REGEX { R"((\d+),(\d+))" };
        static const std::regex INSTRUCTION_REGEX { R"(fold along (x|y)=(\d+))" };

        std::smatch match;

        for (std::string line; std::getline(input, line) && !line.empty(); )
        {
            const bool regexMatched = std::regex_match(line, match, HOLE_REGEX);
            assert(regexMatched);

            m_InitialSheet.emplace(std::stoi(match[1]), std::stoi(match[2]));
        }

        for (std::string line; std::getline(input, line); )
        {
            const bool regexMatched = std::regex_match(line, match, INSTRUCTION_REGEX);
            assert(regexMatched);

            std::unique_ptr<IFoldInstruction> instruction;
            if (match[1] == "x")
            {
                instruction = std::make_unique<FoldLeft>(std::stoi(match[2]));
            }
            else if (match[1] == "y")
            {
                instruction = std::make_unique<FoldUp>(std::stoi(match[2]));
            }

            assert(instruction != nullptr);
            m_Instructions.emplace_back(std::move(instruction));
        }
    }

    std::uint32_t TransparentOrigamiSolver::SolveProblemA() const
    {
        return m_Instructions[0]->ApplyTo(m_InitialSheet).size();
    }

    std::string TransparentOrigamiSolver::SolveProblemB() const
    {
        HoledSheet currentSheet { m_InitialSheet };
        for (const auto& instruction : m_Instructions)
        {
            currentSheet = instruction->ApplyTo(currentSheet);
        }

        return MakePrintable(currentSheet);
    }
}