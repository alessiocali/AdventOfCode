#pragma once
#include <JurassicJigsaw.h>
#include <Tile.h>

#include <optional>
#include <unordered_map>

namespace JurassicJigsaw
{
    class Problem final
    {
    public:
        using TileMap = std::unordered_map<TileID, Tile>;

        inline const TileMap& GetTiles() const { return m_Tiles; }

        void AddTile(const TileID tileID, const ImageData& tileData);
        const Tile& GetTile(const TileID tileID) const;

        CornerType GetCornerTypeFor(const Tile& tile) const;
        std::optional<BorderMatchInfo> GetMatchingTileFor(const Tile& tile, const BorderIndex border) const;

    private:
        TileMap m_Tiles;
    };
}