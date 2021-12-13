#pragma once

#include <ProblemSolver.h>

#include <vector>

namespace sf
{
    class RenderWindow;
}

enum class SeatStatus
{
    Floor,
    Empty,
    Occupied
};

using SeatPosition = std::pair<std::size_t, std::size_t>;

using SeatRow = std::vector<SeatStatus>;
using Seats = std::vector<SeatRow>;

class SeatSystemInstance
{
public:
    using OccupiedCounter = std::size_t(SeatSystemInstance::*)(const std::size_t, const std::size_t)const;

    struct UpdateParameters
    {
        const unsigned int m_Tolerance;
        OccupiedCounter m_Counter;
    };

    SeatSystemInstance(const Seats& problem);

    void Solve(const UpdateParameters params, const bool doDebugDisplay);

    inline const Seats& CurrentState() const { return *m_CurrentBuffer; }
    inline Seats& CurrentState() { return *m_CurrentBuffer; }

    std::size_t CountAllOccupiedSeats() const;
    std::size_t CountOccupiedAround(const std::size_t r, std::size_t c) const;
    std::size_t CountOccupiedVisible(const std::size_t r, std::size_t c) const;

    void Draw(sf::RenderWindow& renderWindow) const;

private:
    Seats m_BufferA;
    Seats m_BufferB;

    Seats* m_CurrentBuffer;
    Seats* m_PendingBuffer;

    std::vector<SeatPosition> m_CachedSeatPositions;

    static class SimpleControllableView CreateDebugView();

    void Update(const UpdateParameters params);
    inline bool HasChanged() { return m_HasChanged; };

    inline Seats& PendingState() { return *m_PendingBuffer; }
    inline const Seats& PendingState() const { return *m_PendingBuffer; }

    bool m_HasChanged { false };

    bool IsInBounds(const int r, const int c) const;
    void SwapBuffer();
};

class SeatingSystemSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    Seats m_Problem;
};