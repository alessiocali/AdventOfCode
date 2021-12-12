#pragma once
#include <string>

namespace JurassicJigsaw
{
    using TileID = std::uint16_t;
    using Border = std::string;

    static constexpr TileID INVALID_TILE_ID { 0 };
    static constexpr std::size_t BORDER_COUNT { 4 };

    static constexpr std::size_t INPUT_BORDER_WIDTH { 10 };

    enum class BorderIndex
    {
        Top = 0,
        Right = 1,
        Bottom = 2,
        Left = 3,
    };

    enum class BorderMatchType
    {
        Normal,
        Mirrored
    };

    enum class CornerType
    {
        None = 0xFF,
        TopLeft = 0,
        TopRight = 1,
        BottomRight = 2,
        BottomLeft = 3
    };

    struct BorderMatchInfo final
    {
        TileID m_TileID { INVALID_TILE_ID };
        BorderIndex m_MatchingBorderIndex { BorderIndex::Top };
        BorderMatchType m_MatchType { BorderMatchType::Normal };
    };

    struct BorderMatchQuery final
    {
        BorderMatchQuery() = delete;

        BorderMatchQuery(const Border& border, BorderMatchType matchType);

        BorderMatchQuery(const BorderMatchQuery& other) = delete;
        BorderMatchQuery& operator=(const BorderMatchQuery& other) = delete;

        BorderMatchQuery(BorderMatchQuery&& other) = delete;
        BorderMatchQuery& operator=(BorderMatchQuery&& other) = delete;

        const Border& m_Border;
        BorderMatchType m_MatchType { BorderMatchType::Normal };
    };

    bool DoBordersMatch(const BorderMatchQuery& border1, const BorderMatchQuery& border2);
}