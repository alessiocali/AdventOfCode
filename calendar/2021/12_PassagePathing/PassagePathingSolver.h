#pragma once

#include <ProblemSolver.h>

#include <algorithm>
#include <optional>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace aoc2021::PassagePathing
{
    using CaveID = std::string;

    constexpr const char* START_ID { "start" };
    constexpr const char* END_ID { "end" };

    struct Cave final
    {
        inline bool IsStart() const { return m_ID == START_ID; }
        inline bool IsEnd() const { return m_ID == END_ID; }

        inline bool IsSmall() const { return std::all_of(std::begin(m_ID), std::end(m_ID), &std::islower); }
        inline bool IsBig() const { return std::all_of(std::begin(m_ID), std::end(m_ID), &std::isupper); }

        CaveID m_ID;
        std::unordered_set<CaveID> m_Connections;

        inline auto operator<=>(const Cave& other) const { return m_ID <=> other.m_ID; }
    };

    using Map = std::unordered_map<CaveID, Cave>;
    using Path = std::vector<CaveID>;

    class ISearchPolicy
    {
    public:
        virtual ~ISearchPolicy() = default;
        virtual void Reset() = 0;
        virtual void OnAllSubPathsExplored(const Cave& subPathsRoot) = 0;
        virtual bool TryVisit(const Cave& cave) = 0;
        virtual void OnVisit(const Cave& cave) = 0;
    };

    class SmallCavesOncePolicy final : public ISearchPolicy
    {
    public:
        void Reset() override;
        void OnAllSubPathsExplored(const Cave& subPathsRoot) override;
        bool TryVisit(const Cave& cave) override;
        void OnVisit(const Cave& cave) override;

    private:
        std::unordered_set<CaveID> m_VisitedSmallCaves { };
    };

    class OneSmallCaveTwicePolicy final : public ISearchPolicy
    {
    public:
        void Reset() override;
        void OnAllSubPathsExplored(const Cave& subPathsRoot) override;
        bool TryVisit(const Cave& cave) override;
        void OnVisit(const Cave& cave) override;

    private:
        std::unordered_set<CaveID> m_VisitedSmallCaves { };
        std::optional<CaveID> m_SpecialCaveID;
    };

    class PathSearcher final
    {
    public:
        std::size_t CountPaths(const Map& map, ISearchPolicy& policy);
    
    private:
        std::size_t m_FoundPaths { 0 };
        Path m_CurrentPath { };

        std::stack<CaveID> m_ExplorationHistory { };

        void Reset();
        void ExploreCave(const Cave& nextCave, ISearchPolicy& policy);
        void EndReached();
        bool IsPathBack(const Cave& cave);
        void AllSubPathsExplored(const Cave& subPathsRoot);
        void AlreadyVisited();
        void Visit(const Cave& cave);
    };

    class PassagePathingSolver : public ProblemSolver<std::string, std::size_t, std::size_t>
    {
    public:
        void Init(std::string& input) override;
        std::size_t SolveProblemA() const override;
        std::size_t SolveProblemB() const override;

    private:
        Map m_Map;
    };
}