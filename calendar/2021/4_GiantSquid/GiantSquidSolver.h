#pragma once

#include <ProblemSolver.h>

#include <array>
#include <vector>

namespace aoc2021::GiantSquid
{
    static constexpr std::size_t BOARD_WIDTH { 5 };
    static constexpr std::size_t BOARD_HEIGHT { 5 };

    using BingoRow = std::array<std::uint8_t, BOARD_WIDTH>;
    using BingoBoard = std::array<BingoRow, BOARD_HEIGHT>;

    using NumberTracker = std::vector<std::uint8_t>;
    using NumberSequence = std::vector<std::uint8_t>;

    struct Problem final
    {
        void AddBoard();
        void AddBoardRow(const std::size_t rowIndex, const std::string& rowString);

        std::vector<BingoBoard> m_Boards;
        NumberSequence m_Sequence;
    };

    struct BoardTracker
    {
        void Init(const BingoBoard& board);

        bool ExtractAndTestWinning(const std::uint8_t number);

        std::array<NumberTracker, BOARD_WIDTH> m_Rows;
        std::array<NumberTracker, BOARD_HEIGHT> m_Columns;

        bool m_Won { false };
    };

    class GiantSquidSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
    {
    public:
        void Init(std::string& input) override;
        std::uint32_t SolveProblemA() const override;
        std::uint32_t SolveProblemB() const override;

    private:
        Problem m_Problem;

        void InitNumberSequence(const std::string& sequenceInput);
        std::vector<BoardTracker> CreateGameTracker() const;
        std::uint32_t EvaluateScore(const BoardTracker& winningBoard, const std::uint8_t winningNumber) const;
    };
}