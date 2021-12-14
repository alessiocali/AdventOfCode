#include <GiantSquidSolver.h>

#include <cassert>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>

namespace aoc2021::GiantSquid
{
    void BoardTracker::Init(const BingoBoard& board)
    {
        for (std::size_t i = 0; i < BOARD_HEIGHT; i++)
        {
            for (std::size_t j = 0; j < BOARD_WIDTH; j++)
            {
                m_Rows[i].emplace_back(board[i][j]);
            }
        }

        for (std::size_t i = 0; i < BOARD_HEIGHT; i++)
        {
            for (std::size_t j = 0; j < BOARD_WIDTH; j++)
            {
                m_Columns[i].emplace_back(board[j][i]);
            }
        }
    }

    bool BoardTracker::ExtractAndTestWinning(const std::uint8_t number)
    {
        auto accumulateTrackers = [&](bool winning, auto& tracker) -> bool
        {
            std::erase(tracker, number);
            return winning || tracker.empty();
        };

        bool winningRows = std::accumulate(m_Rows.begin(), m_Rows.end(), false, accumulateTrackers);
        bool winningCols = std::accumulate(m_Columns.begin(), m_Columns.end(), false, accumulateTrackers);
        m_Won = winningRows || winningCols;
        return m_Won;
    }

    void Problem::AddBoard()
    {
        m_Boards.emplace_back();
    }

    void Problem::AddBoardRow(const std::size_t rowIndex, const std::string& rowString)
    {
        assert(!m_Boards.empty());
        assert(rowIndex < BOARD_HEIGHT);

        BingoBoard& board = *m_Boards.rbegin();
        BingoRow& row = board[rowIndex];

        std::istringstream stringStream { rowString };
        std::size_t colIndex { 0 };
        for (std::string numberString; std::getline(stringStream, numberString, ' '); )
        {
            if (numberString.empty())
            {
                continue;
            }

            assert(colIndex < BOARD_WIDTH);
            row[colIndex++] = std::stoi(numberString);
        }
    }

    void GiantSquidSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        std::string sequenceLine;
        bool sequenceLineTaken { std::getline(input, sequenceLine) };
        assert(sequenceLineTaken);

        InitNumberSequence(sequenceLine);

        std::size_t currentRowIndex { 0 };
        for (std::string line; std::getline(input, line); )
        {
            if (line.empty())
            {
                m_Problem.AddBoard();
                currentRowIndex = 0;
            }
            else
            {
                assert(currentRowIndex < BOARD_HEIGHT);
                m_Problem.AddBoardRow(currentRowIndex++, line);
            }
        }
    }

    std::uint32_t GiantSquidSolver::SolveProblemA() const
    {
        std::vector<BoardTracker> gameTracker = CreateGameTracker();
        for (const std::uint8_t number : m_Problem.m_Sequence)
        {
            for (BoardTracker& boardTracker : gameTracker)
            {
                if (boardTracker.ExtractAndTestWinning(number))
                {
                    return EvaluateScore(boardTracker, number);
                }
            }
        }

        assert(false && "Unable to evaluate a winning board.");
        return 0;
    }

    std::uint32_t GiantSquidSolver::SolveProblemB() const
    {
        std::vector<BoardTracker> gameTracker = CreateGameTracker();
        BoardTracker* lastWinningBoard { nullptr };
        std::uint8_t lastWinningNumber { 0 };

        for (const std::uint8_t number : m_Problem.m_Sequence)
        {
            for (BoardTracker& boardTracker : gameTracker)
            {
                if (!boardTracker.m_Won && boardTracker.ExtractAndTestWinning(number))
                {
                    lastWinningBoard = &boardTracker;
                    lastWinningNumber = number;
                }
            }
        }

        assert(lastWinningBoard != nullptr && "Unable to evaluate a winning board.");
        return EvaluateScore(*lastWinningBoard, lastWinningNumber);
    }

    void GiantSquidSolver::InitNumberSequence(const std::string& sequenceInput)
    {
        std::stringstream stringStream { sequenceInput };
        for (std::string numberLine; std::getline(stringStream, numberLine, ','); )
        {
            m_Problem.m_Sequence.emplace_back(std::stoi(numberLine));
        }
    }

    std::vector<BoardTracker> GiantSquidSolver::CreateGameTracker() const
    {
        std::vector<BoardTracker> gameTracker;
        gameTracker.reserve(m_Problem.m_Boards.size());
        
        for (const BingoBoard& board : m_Problem.m_Boards)
        {
            gameTracker.emplace_back().Init(board);
        }

        return gameTracker;
    }

    std::uint32_t GiantSquidSolver::EvaluateScore(const BoardTracker& winningBoard, const std::uint8_t winningNumber) const
    {
        auto accumulateTrackers = [](std::uint32_t currentScore, const NumberTracker& tracker) -> std::uint32_t
        {
            return currentScore + std::accumulate(tracker.begin(), tracker.end(), 0u, std::plus<std::uint32_t>());
        };

        return winningNumber * std::accumulate(winningBoard.m_Rows.begin(), winningBoard.m_Rows.end(), 0u, accumulateTrackers);
    }
}