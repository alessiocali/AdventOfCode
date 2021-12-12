#pragma once
#include <JurassicJigsaw.h>
#include <Image.h>

#include <array>
#include <optional>

namespace JurassicJigsaw
{
    class Tile final
    {
    public:
        Tile() = default;
        Tile(const TileID tileID, const Image& image);
        Tile(const TileID tileID, Image&& image);

        inline TileID GetTileID() const { return m_TileID; }
        inline void SetTileID(const TileID tileID) { m_TileID = tileID; }

        inline const Image& GetImage() const { return m_Image; }

        inline const Border& GetBorderAtIndex(const BorderIndex idx) const { return m_Borders[static_cast<std::size_t>(idx)]; }

        std::optional<BorderMatchInfo> GetMatchingBorderWith(const Border& border) const;

    private:
        TileID m_TileID;
        Image m_Image;
        std::array<Border, BORDER_COUNT> m_Borders;

        void CacheBorders();
    };
}