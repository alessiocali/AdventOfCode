#pragma once

#include <ProblemSolver.h>

#include <vector>

enum class SeatStatus
{
    Floor,
    Empty,
    Occupied
};

using SeatPosition = std::pair<int,int>;

using SeatRow = std::vector<SeatStatus>;
using Seats = std::vector<SeatRow>;

class SeatSystemInstance
{
public:
    using OccupiedCounter = std::size_t(SeatSystemInstance::*)(const int, const int)const;

    SeatSystemInstance(const Seats& problem);

    void Update(unsigned int tolerance = 4, OccupiedCounter counter = &SeatSystemInstance::CountOccupiedAround);
    inline bool HasChanged() { return m_HasChanged; };

    inline const Seats& CurrentState() const { return *m_CurrentBuffer; }
    inline Seats& CurrentState() { return *m_CurrentBuffer; }

    std::size_t CountOccupiedAround(const int r, const int c) const;
    std::size_t CountOccupiedVisible(const int r, const int c) const;

private:
    Seats m_BufferA;
    Seats m_BufferB;

    Seats* m_CurrentBuffer;
    Seats* m_PendingBuffer;

    std::vector<SeatPosition> m_CachedSeatPositions;

    inline Seats& PendingState() { return *m_PendingBuffer; }
    inline const Seats& PendingState() const { return *m_PendingBuffer; }

    bool m_HasChanged { false };

    bool IsInBounds(const int r, const int c) const;
    void SwapBuffer();
};

class SeatingSystemSolver : public ProblemSolver<std::string, std::uint32_t, std::uint32_t>
{
public:
    void Init(std::string& input) override;
    std::uint32_t SolveProblemA() const override;
    std::uint32_t SolveProblemB() const override;

private:
    Seats m_Problem;
};