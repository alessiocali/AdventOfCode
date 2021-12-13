#pragma once

#include <ProblemSolver.h>

#include <unordered_set>
#include <unordered_map>

class ConwayCubesSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
{
public:
    void Init(std::string& input) override;
    std::size_t SolveProblemA() const override;
    std::size_t SolveProblemB() const override;

private:
    struct CubePos
    {
        std::int32_t x, y, z, w;

        CubePos(std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w)
            : x(x), y(y), z(z), w(w)
        { }

        bool operator==(const CubePos& other) const
        {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        bool operator<(const CubePos& other) const
        {
            return std::tie(x, y, z, w) < std::tie(other.x, other.y, other.z, other.w);
        }
    };

    struct CubePosHasher
    {
        std::size_t operator()(const ConwayCubesSolver::CubePos& pos) const
        {
            const auto hasher = std::hash<std::int32_t> { };

            return  hasher(pos.x) ^
                    hasher(pos.y) ^
                    hasher(pos.z) ^ 
                    hasher(pos.w);
        }
    };

    using CubePosSet = std::unordered_set<CubePos, CubePosHasher>;
    using CubeNeighbourCounter = std::unordered_map<CubePos, std::size_t, CubePosHasher>;

    // Set of active cubes
    using Problem = CubePosSet;

    Problem m_Problem;

    enum class SearchType
    {
        _3D, _4D
    };

    void RunNCycles(CubePosSet& startState, std::size_t n, const SearchType searchType) const;
    void RunOneCycle(CubePosSet& currentState, const SearchType searchType) const;

    /** Explore all neighbours of cube, and if cube is active update the neighbour's counter .
     *  Cube MUST be active, else bugs.
     */
    void UpdateNeighboursAroundCube(const CubePos& cube, CubeNeighbourCounter& neighbourCounter, const SearchType searchType) const;
};