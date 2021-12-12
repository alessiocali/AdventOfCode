#pragma once

#include <Image.h>
#include <Tile.h>

#include <tuple>
#include <vector>

namespace JurassicJigsaw
{
    enum class CornerType;

    struct BorderMatchInfo;
    class Problem;

    using TileRow = std::vector<Tile>;
    using TileGrid = std::vector<TileRow>;

    class ImageMatcher final
    {
    public:
        ImageMatcher() = default;
        ImageMatcher(const Problem& problem);

        const TileGrid& GetTileGrid() const { return m_TileGrid; }
        const Image& GetMergedImage() const { return m_MergedImage; }

    private:
        TileGrid m_TileGrid;
        Image m_MergedImage;

        std::pair<const Tile*, CornerType> FindFirstCorner(const Problem& problem);

        void InitializeFirstColumn(const Tile& firstCorner, const CornerType firstCornerType, const Problem& problem);
        Image RotateToBeTopLeft(const Image& firstCornerImage, const CornerType firstCornerType) const;
        Image FixAlignmentWithBottomBorder(const BorderMatchInfo& borderMatchInfo, const Tile& matchedTile) const;

        void InitializeRows(const Problem& problem);
        Image FixAlignmentWithRightBorder(const BorderMatchInfo& borderMatchInfo, const Tile& matchedTile) const;

        Image MergeImageData(const TileGrid& matchImageData) const;
        TileGrid ExtractBorders(const TileGrid& matchImageData) const;
    };

}