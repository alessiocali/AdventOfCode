#include "SeatingSystemSolver.h"

#include <SimpleControllableView.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <unordered_map>
#include <fstream>
#include <string>

SeatSystemInstance::SeatSystemInstance(const Seats& problem)
    : m_BufferA(problem)
    , m_BufferB(problem)
    , m_CurrentBuffer(&m_BufferA)
    , m_PendingBuffer(&m_BufferB)
{
    for (std::size_t r = 0; r < problem.size(); r++)
    {
        for (std::size_t c = 0; c < problem[r].size(); c++)
        {
            if (problem[r][c] == SeatStatus::Empty || problem[r][c] == SeatStatus::Occupied)
            {
                m_CachedSeatPositions.emplace_back(r, c);
            }
        }
    }
}

void SeatSystemInstance::Solve(const UpdateParameters params, const bool doDebugDisplay)
{
    if (doDebugDisplay)
    {
        CreateDebugView().RunUntilClosed
        (
            [this](sf::RenderWindow& renderWindow) { Draw(renderWindow); },
            [this, &params](sf::RenderWindow& renderWindow) { Update(params); },
            [this]() { return !HasChanged(); }
        );
    }
    else
    {
        do 
        {
            Update(params);
        }
        while (HasChanged());
    }
}

class SimpleControllableView SeatSystemInstance::CreateDebugView()
{
    return SimpleControllableView { sf::VideoMode { 1280, 720 }, "Seating System", 0, SimpleControllableView::SpeedParameters { 0.1f, 2.f } };
}

void SeatSystemInstance::Update(const UpdateParameters params)
{
    m_HasChanged = false;

    for (const auto [r, c] : m_CachedSeatPositions)
    {
        std::size_t occupiedAround = (this->*params.m_Counter)(r, c);
        if (CurrentState()[r][c] == SeatStatus::Empty && occupiedAround == 0)
        {
            PendingState()[r][c] = SeatStatus::Occupied;
            m_HasChanged = true;
        }
        else if (CurrentState()[r][c] == SeatStatus::Occupied && occupiedAround >= params.m_Tolerance)
        {
            PendingState()[r][c] = SeatStatus::Empty;
            m_HasChanged = true;
        }
        else
        {
            PendingState()[r][c] = CurrentState()[r][c];
        }
    }

    SwapBuffer();
}

bool SeatSystemInstance::IsInBounds(const int r, const int c) const
{
    return  r >= 0 && r < CurrentState().size() &&
            c >= 0 && c < CurrentState()[r].size();
}

std::size_t SeatSystemInstance::CountOccupiedAround(const std::size_t r, const std::size_t c) const
{
    std::size_t count { 0 };

    for (int adjR = int(r) - 1; adjR <= int(r) + 1; adjR++)
    {
        for (int adjC = int(c) - 1; adjC <= int(c) + 1; adjC++)
        {
            if (adjC == c && adjR == r)
            {
                continue;
            }

            if (!IsInBounds(adjR, adjC))
            {
                continue;
            }

            if (CurrentState()[adjR][adjC] == SeatStatus::Occupied) { count++; }
        }
    }

    return count;
}

std::size_t SeatSystemInstance::CountOccupiedVisible(const std::size_t r, const std::size_t c) const
{
    static const std::vector<sf::Vector2i> DIRECTIONS_TO_CHECK =
    {
        {  0,  1 },
        {  0, -1 },
        {  1,  0 },
        { -1,  0 },
        {  1,  1 },
        {  1, -1 },
        { -1, -1 },
        { -1,  1 }
    };

    std::size_t occupiedCount { 0 };
    for (const sf::Vector2i direction : DIRECTIONS_TO_CHECK)
    {
        int row { int(r) + direction.y };
        int col { int(c) + direction.x };

        while (IsInBounds(row, col))
        {
            SeatStatus seenStatus = CurrentState()[row][col];
            if (seenStatus != SeatStatus::Floor)
            {
                occupiedCount += seenStatus == SeatStatus::Occupied ? 1 : 0;
                break;
            }

            row += direction.y;
            col += direction.x;
        }
    }

    return occupiedCount;
}

void SeatSystemInstance::Draw(sf::RenderWindow& renderWindow) const
{
    constexpr float TILE_DISPLAY_SIZE = 0.01f;
    sf::RectangleShape tileToDraw { sf::Vector2f { TILE_DISPLAY_SIZE, TILE_DISPLAY_SIZE } };

    for (std::size_t r = 0; r < CurrentState().size(); r++)
    {
        for (std::size_t c = 0; c < CurrentState()[r].size(); c++)
        {
            const sf::Vector2f coordinate = { c * TILE_DISPLAY_SIZE, r * TILE_DISPLAY_SIZE };

            static const std::unordered_map<SeatStatus, sf::Color> COLOR_MAPPINGS =
            {
                { SeatStatus::Empty, sf::Color::Green },
                { SeatStatus::Occupied, sf::Color::Red },
                { SeatStatus::Floor, sf::Color::Blue }
            };

            const sf::Color color = COLOR_MAPPINGS.at(CurrentState()[r][c]);

            tileToDraw.setPosition(coordinate);
            tileToDraw.setFillColor(color);

            renderWindow.draw(tileToDraw);
        }
    }
}

std::size_t SeatSystemInstance::CountAllOccupiedSeats() const
{
    std::size_t occupiedCount { 0 };
    for (std::size_t r = 0; r < CurrentState().size(); r++)
    {
        for (std::size_t c = 0; c < CurrentState()[r].size(); c++)
        {
            if (CurrentState()[r][c] == SeatStatus::Occupied)
            {
                occupiedCount++;
            }
        }
    }

    return occupiedCount;
}

void SeatSystemInstance::SwapBuffer()
{
    std::swap(m_CurrentBuffer, m_PendingBuffer);
}

void SeatingSystemSolver::Init(std::string& input)
{
    std::ifstream inputStream(input);
    assert(inputStream.is_open());
    std::string temp;

    while (std::getline(inputStream, temp))
    {
        SeatRow& row = m_Problem.emplace_back();
        for (auto ch : temp)
        {
            if (ch == 'L')
            {
                row.emplace_back(SeatStatus::Empty);
            }
            else if (ch == '.')
            {
                row.emplace_back(SeatStatus::Floor);
            }
            else
            {
                assert(false && "Unexpected Seat type in input");
            }
        }
    }
}

std::size_t SeatingSystemSolver::SolveProblemA() const
{    
    SeatSystemInstance instance { m_Problem };
    instance.Solve({ 4, &SeatSystemInstance::CountOccupiedAround }, /*doDebugDisplay =*/ IsDebugging());
    return instance.CountAllOccupiedSeats();
}

std::size_t SeatingSystemSolver::SolveProblemB() const
{
    SeatSystemInstance instance { m_Problem };
    instance.Solve({ 5, &SeatSystemInstance::CountOccupiedVisible }, /*doDebugDisplay =*/ IsDebugging());
    return instance.CountAllOccupiedSeats();
}