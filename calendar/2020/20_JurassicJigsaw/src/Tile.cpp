#include <Tile.h>

namespace JurassicJigsaw
{
        Tile::Tile(const TileID tileID, const Image& image)
        : m_TileID(tileID)
        , m_Image(image)
    {
        CacheBorders();
    }

    Tile::Tile(const TileID tileID, Image&& image)
        : m_TileID(tileID)
        , m_Image(std::move(image))
    {
        CacheBorders();
    }

    void Tile::CacheBorders()
    {
        const std::size_t height = m_Image.GetHeight();
        const std::size_t width = m_Image.GetWidth();

        // Borders are read from the top-left corner moving clockwise.
        // It is quite arbitrary, but one order has to be picked.
        for (std::size_t i = 0; i < width; i++)
        {
            m_Borders[static_cast<std::size_t>(BorderIndex::Top)] += m_Image[0][i];
            m_Borders[static_cast<std::size_t>(BorderIndex::Bottom)] += m_Image[height - 1][width - 1 - i];
        }

        for (std::size_t i = 0; i < height; i++)
        {
            m_Borders[static_cast<std::size_t>(BorderIndex::Right)] += m_Image[i][width - 1];
            m_Borders[static_cast<std::size_t>(BorderIndex::Left)] += m_Image[height - 1 - i][0];
        }
    }

    std::optional<BorderMatchInfo> Tile::GetMatchingBorderWith(const Border& border) const
    {
        for (std::size_t borderIdx = 0; borderIdx < BORDER_COUNT; borderIdx++)
        {
            if (DoBordersMatch({ border, BorderMatchType::Normal }, { m_Borders[borderIdx], BorderMatchType::Normal }))
            {
                return BorderMatchInfo { m_TileID, static_cast<BorderIndex>(borderIdx), BorderMatchType::Normal };
            }
            else if (DoBordersMatch({ border, BorderMatchType::Normal }, { m_Borders[borderIdx], BorderMatchType::Mirrored }))
            {
                return BorderMatchInfo { m_TileID, static_cast<BorderIndex>(borderIdx), BorderMatchType::Mirrored };
            }
        }

        return std::nullopt;
    }
}