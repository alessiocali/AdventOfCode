#include <PassagePathingSolver.h>

#include <cassert>
#include <fstream>
#include <regex>
#include <string>

namespace aoc2021::PassagePathing
{
    void PassagePathingSolver::Init(std::string& inputFileName)
    {
        std::ifstream input { inputFileName };
        assert(input.is_open());

        static const std::regex CONNECTION_REGEX { R"(([a-zA-Z]+)\-([a-zA-Z]+))" };
        std::smatch match;

        for (std::string line; std::getline(input, line); )
        {
            const bool regexMatched = std::regex_match(line, match, CONNECTION_REGEX);
            assert(regexMatched);
            
            const CaveID id1 = match[1];
            const CaveID id2 = match[2];

            Cave& cave1 = m_Map[id1];
            Cave& cave2 = m_Map[id2];

            cave1.m_ID = id1;
            cave2.m_ID = id2;

            cave1.m_Connections.insert(id2);
            cave2.m_Connections.insert(id1);
        }
    }

    std::size_t PassagePathingSolver::SolveProblemA() const
    {
        PathSearcher pathSearcher;
        SmallCavesOncePolicy policy;
        return pathSearcher.CountPaths(m_Map, policy);
    }

    std::size_t PassagePathingSolver::SolveProblemB() const
    {
        PathSearcher pathSearcher;
        OneSmallCaveTwicePolicy policy;
        return pathSearcher.CountPaths(m_Map, policy);
    }

    std::size_t PathSearcher::CountPaths(const Map& map, ISearchPolicy& policy)
    {
        policy.Reset();
        Reset();

        while (!m_ExplorationHistory.empty())
        {
            const CaveID& nextCaveID = m_ExplorationHistory.top();
            const Cave& nextCave = map.at(nextCaveID);
            ExploreCave(nextCave, policy);
        }

        return m_FoundPaths;
    }

    void PathSearcher::ExploreCave(const Cave& nextCave, ISearchPolicy& policy)
    {
        if (nextCave.IsEnd())
        {
            EndReached();
        }
        else if (IsPathBack(nextCave))
        {
            policy.OnAllSubPathsExplored(nextCave);
            AllSubPathsExplored(nextCave);
        }
        else if (!policy.TryVisit(nextCave))
        {
            AlreadyVisited();
        }
        else
        {
            policy.OnVisit(nextCave);
            Visit(nextCave);
        }
    }

    void PathSearcher::Reset()
    {
        m_FoundPaths = 0;
        m_CurrentPath.clear();

        m_ExplorationHistory = std::stack<CaveID> { };
        m_ExplorationHistory.push(START_ID);
    }

    void PathSearcher::EndReached()
    {
        m_FoundPaths++;
        m_ExplorationHistory.pop();
    }

    bool PathSearcher::IsPathBack(const Cave& cave)
    {
        return !m_CurrentPath.empty() && m_CurrentPath.back() == cave.m_ID;
    }

    void PathSearcher::AllSubPathsExplored(const Cave& subPathsRoot)
    {
        m_CurrentPath.pop_back();
        m_ExplorationHistory.pop();
    }

    void PathSearcher::AlreadyVisited()
    {
        m_ExplorationHistory.pop();
    }

    void PathSearcher::Visit(const Cave& cave)
    {
        m_CurrentPath.emplace_back(cave.m_ID);
        for (const CaveID& connection : cave.m_Connections)
        {
            m_ExplorationHistory.push(connection);
        }
    }

    void SmallCavesOncePolicy::Reset()
    {
        m_VisitedSmallCaves.clear();
    }

    void SmallCavesOncePolicy::OnAllSubPathsExplored(const Cave& subPathRoot)
    {
        m_VisitedSmallCaves.erase(subPathRoot.m_ID);
    }

    bool SmallCavesOncePolicy::TryVisit(const Cave& cave)
    {
        return !m_VisitedSmallCaves.contains(cave.m_ID);
    }

    void SmallCavesOncePolicy::OnVisit(const Cave& cave)
    {
        if (cave.IsSmall())
        {
            m_VisitedSmallCaves.insert(cave.m_ID);
        }
    }

    void OneSmallCaveTwicePolicy::Reset()
    {
        m_VisitedSmallCaves.clear();
        m_SpecialCaveID.reset();
    }

    void OneSmallCaveTwicePolicy::OnAllSubPathsExplored(const Cave& subPathsRoot)
    {
        if (m_SpecialCaveID == subPathsRoot.m_ID)
        {
            m_SpecialCaveID.reset();
        }
        else
        {
            m_VisitedSmallCaves.erase(subPathsRoot.m_ID);
        }
    }

    bool OneSmallCaveTwicePolicy::TryVisit(const Cave& cave)
    {
        return !m_VisitedSmallCaves.contains(cave.m_ID) || (!cave.IsStart() && !m_SpecialCaveID.has_value());
    }

    void OneSmallCaveTwicePolicy::OnVisit(const Cave& cave)
    {
        if (m_VisitedSmallCaves.contains(cave.m_ID))
        {
            assert(!m_SpecialCaveID.has_value());
            m_SpecialCaveID = cave.m_ID;
        }
        else if (cave.IsSmall())
        {
            m_VisitedSmallCaves.insert(cave.m_ID);
        }
    }
}