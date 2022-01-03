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
        return pathSearcher.CountPaths(m_Map, PathSearcher::SearchType::SmallCavesOnce);
    }

    std::size_t PassagePathingSolver::SolveProblemB() const
    {
        PathSearcher pathSearcher;
        return pathSearcher.CountPaths(m_Map, PathSearcher::SearchType::OneSmallCaveTwice);
    }

    std::size_t PathSearcher::CountPaths(const Map& map, const SearchType searchType)
    {
        Reset(searchType);
        while (!m_ExplorationHistory.empty())
        {
            const CaveID& nextCaveID = m_ExplorationHistory.top();
            const Cave& nextCave = map.at(nextCaveID);

            if (nextCave.IsEnd())
            {
                EndReached();
                continue;
            }

            if (IsPathBack(nextCave))
            {
                AllSubPathsExplored(nextCave);
                continue;
            }

            if (IsAlreadyVisited(nextCave) && !TryVisitAgain(nextCave))
            {
                AlreadyVisited();
                continue;
            }

            Expand(nextCave);
        }

        return m_FoundPaths;
    }

    void PathSearcher::Reset(const SearchType searchType)
    {
        m_UseSpecialCave = (searchType == SearchType::OneSmallCaveTwice);
        m_VisitedSmallCaves.clear();
        m_SpecialCaveID.reset();
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
        if (m_UseSpecialCave && m_SpecialCaveID == subPathsRoot.m_ID)
        {
            m_SpecialCaveID.reset();
        }
        else
        {
            m_VisitedSmallCaves.erase(subPathsRoot.m_ID);
        }

        m_CurrentPath.pop_back();
        m_ExplorationHistory.pop();
    }

    bool PathSearcher::IsAlreadyVisited(const Cave& cave) const
    {
        return m_VisitedSmallCaves.contains(cave.m_ID);
    }

    bool PathSearcher::TryVisitAgain(const Cave& cave)
    {
        if (m_UseSpecialCave && !cave.IsStart() && !m_SpecialCaveID.has_value())
        {
            m_SpecialCaveID = cave.m_ID;
            return true;
        }
        else
        {
            return false;
        }
    }

    void PathSearcher::AlreadyVisited()
    {
        m_ExplorationHistory.pop();
    }

    void PathSearcher::Expand(const Cave& cave)
    {
        m_CurrentPath.emplace_back(cave.m_ID);

        if (cave.IsSmall())
        {
            m_VisitedSmallCaves.insert(cave.m_ID);
        }

        for (const CaveID& connection : cave.m_Connections)
        {
            m_ExplorationHistory.push(connection);
        }
    }
}