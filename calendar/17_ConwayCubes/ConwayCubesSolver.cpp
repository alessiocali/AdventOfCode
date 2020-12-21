#include "ConwayCubesSolver.h"

#include <fstream>
#include <string>
#include <cassert>

void ConwayCubesSolver::Init(std::string& input)
{
    std::ifstream inputStream { input };
    assert(inputStream.is_open());
    
    std::int32_t x { 0 };
    std::int32_t y { 0 };
    std::int32_t z { 0 };
    std::int32_t w { 0 };

    for (std::string line; std::getline(inputStream, line);)
    {
        x = 0;
        for (const auto c : line)
        {
            if (c == '#') 
            {
                m_Problem.emplace(x, y, z, w);
            }

            x++;
        }

        y++;
    }
}

std::size_t ConwayCubesSolver::SolveProblemA() const
{
    CubePosSet currentState { m_Problem };
    RunNCycles(currentState, 6, SearchType::_3D);
    return currentState.size();
}

std::size_t ConwayCubesSolver::SolveProblemB() const
{
    CubePosSet currentState { m_Problem };
    RunNCycles(currentState, 6, SearchType::_4D);
    return currentState.size();
}

void ConwayCubesSolver::RunNCycles(CubePosSet& startState, std::size_t n, const SearchType searchType) const
{
    for (std::size_t i = 0; i < n; i++) { RunOneCycle(startState, searchType); }
}

void ConwayCubesSolver::RunOneCycle(CubePosSet& currentState, const SearchType searchType) const
{
    CubePosSet nextState;
    CubeNeighbourCounter neighbourCounter;
    for (const auto& cube : currentState)
    {
        UpdateNeighboursAroundCube(cube, neighbourCounter, searchType);
    }

    for (const auto& [cube, activeNeighbours] : neighbourCounter)
    {
        const bool isActive = currentState.count(cube) > 0;
        const bool willBecomeActive = isActive ?
            (activeNeighbours == 2 || activeNeighbours == 3) :
            (activeNeighbours == 3);

        if (willBecomeActive) { nextState.emplace(cube); }
    }

    currentState = std::move(nextState);
}

void ConwayCubesSolver::UpdateNeighboursAroundCube(const CubePos& cube, CubeNeighbourCounter& neighbourCounter, const SearchType searchType) const
{
    for (std::int32_t x = cube.x - 1; x <= cube.x + 1; x++)
    {
        for (std::int32_t y = cube.y - 1; y <= cube.y + 1; y++)
        {
            for (std::int32_t z = cube.z - 1; z <= cube.z + 1; z++)
            {
                auto updateNeighbours = [&](std::int32_t w)
                {
                    CubePos exploredCube { x, y, z, w };
                    if (exploredCube == cube) { return; }

                    if (neighbourCounter.count(exploredCube) == 0)
                    {
                        neighbourCounter[exploredCube] = 1;
                    }
                    else
                    {
                        neighbourCounter[exploredCube]++;
                    }
                };

                if (searchType == SearchType::_4D)
                {
                    for (std::int32_t w = cube.w - 1; w <= cube.w + 1; w++)
                    {
                        updateNeighbours(w);
                    }
                }
                else
                {
                    updateNeighbours(cube.w);
                }
            }
        }
    }
}
