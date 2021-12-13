#include <Problem.h>

namespace JurassicJigsaw
{
    void Problem::AddTile(const TileID tileID, const ImageData& tileData)
    {
        m_Tiles[tileID] = Tile { tileID, tileData };
    }

    const Tile& Problem::GetTile(const TileID tileID) const
    {
        return m_Tiles.at(tileID);
    }

    std::optional<BorderMatchInfo> Problem::GetMatchingTileFor(const Tile& tile, const BorderIndex border) const
    {
        const Border& borderToMatch = tile.GetBorderAtIndex(border);
        for (const auto& [otherTileID, otherTile] : m_Tiles)
        {
            if (otherTileID == tile.GetTileID())
            {
                continue;
            }

            if (std::optional<BorderMatchInfo> borderMatch = otherTile.GetMatchingBorderWith(borderToMatch))
            {
                return borderMatch;
            }
        }

        return std::nullopt;
    }

    CornerType Problem::GetCornerTypeFor(const Tile& tile) const
    {
        bool isTopFree { !GetMatchingTileFor(tile, BorderIndex::Top) };
        bool isRightFree { !GetMatchingTileFor(tile, BorderIndex::Right) };
        bool isBottomFree { !GetMatchingTileFor(tile, BorderIndex::Bottom) };
        bool isLeftFree { !GetMatchingTileFor(tile, BorderIndex::Left) };

        if (isTopFree && isLeftFree) { return CornerType::TopLeft; }
        else if (isTopFree && isRightFree) { return CornerType::TopRight; }
        else if (isBottomFree && isLeftFree) { return CornerType::BottomLeft; }
        else if (isBottomFree && isRightFree) { return CornerType::BottomRight; }
        else { return CornerType::None; }
    }
}