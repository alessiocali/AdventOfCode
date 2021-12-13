#include <JurassicJigsaw.h>

#include <cassert>

namespace JurassicJigsaw
{
    BorderMatchQuery::BorderMatchQuery(const Border& border, BorderMatchType matchType)
        : m_Border(border)
        , m_MatchType(matchType)
    { }

    bool DoBordersMatch(const BorderMatchQuery& border1, const BorderMatchQuery& border2)
    {
        const std::size_t borderWidth1 = border1.m_Border.size();
        const std::size_t borderWidth2 = border2.m_Border.size();
        assert(borderWidth1 == borderWidth2);

        for (std::size_t i = 0; i < borderWidth1; i++)
        {
            const std::size_t idx1 = border1.m_MatchType == BorderMatchType::Normal ? i : borderWidth1 - 1 - i;
            const std::size_t idx2 = border2.m_MatchType == BorderMatchType::Normal ? i : borderWidth2 - 1 - i;
            if (border1.m_Border[idx1] != border2.m_Border[idx2])
            {
                return false;
            }
        }

        return true;
    }
}