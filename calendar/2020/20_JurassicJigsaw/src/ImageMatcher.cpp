#include <ImageMatcher.h>

#include <JurassicJigsaw.h>
#include <Problem.h>
#include <Tile.h>

#include <cassert>
#include <numeric>
#include <optional>

namespace JurassicJigsaw
{
    ImageMatcher::ImageMatcher(const Problem& problem)
    {
        auto [firstCorner, firstCornerType] = FindFirstCorner(problem);
        assert(firstCorner != nullptr);

        InitializeFirstColumn(*firstCorner, firstCornerType, problem);
        InitializeRows(problem);

        m_MergedImage = MergeImageData(ExtractBorders(m_TileGrid));
    }

    std::pair<const Tile*, CornerType> ImageMatcher::FindFirstCorner(const Problem& problem)
    {
        const Tile* firstCorner { nullptr };
        CornerType firstCornerType { CornerType::None };
        for (const auto& [tileID, tile] : problem.GetTiles())
        {
            const CornerType tileCornerType = problem.GetCornerTypeFor(tile);
            if (tileCornerType != CornerType::None)
            {
                firstCorner = &tile;
                firstCornerType = tileCornerType;
                break;
            }
        }

        return { firstCorner, firstCornerType };
    }

    void ImageMatcher::InitializeFirstColumn(const Tile& firstCorner, const CornerType firstCornerType, const Problem& problem)
    {
        Image reorderedImage = RotateToBeTopLeft(firstCorner.GetImage(), firstCornerType);
        Tile* previousTile = &m_TileGrid.emplace_back().emplace_back(firstCorner.GetTileID(), std::move(reorderedImage));

        while (std::optional<BorderMatchInfo> borderMatch = problem.GetMatchingTileFor(*previousTile, BorderIndex::Bottom))
        {
            const Tile& matchedTile = problem.GetTile(borderMatch->m_TileID);
            reorderedImage = FixAlignmentWithBottomBorder(*borderMatch, matchedTile);
            previousTile = &m_TileGrid.emplace_back().emplace_back(matchedTile.GetTileID(), std::move(reorderedImage));
        }
    }

    Image ImageMatcher::RotateToBeTopLeft(const Image& firstCornerImage, const CornerType firstCornerType) const
    {
        Image reorderedImage;

        if (firstCornerType == CornerType::TopRight)
        {
            reorderedImage = firstCornerImage.Rotate90Left();
        }
        else if (firstCornerType == CornerType::BottomRight)
        {
            reorderedImage = firstCornerImage.Rotate180();
        }
        else if (firstCornerType == CornerType::BottomLeft)
        {
            reorderedImage = firstCornerImage.Rotate90Right();
        }
        else
        {
            reorderedImage = firstCornerImage;
        }

        return reorderedImage;
    }

    // Yes this is an abomination which only works for matching the bottom border with something, and only
    // assuming that borders are read in a clock-wise fashion. But it works.
    Image ImageMatcher::FixAlignmentWithBottomBorder(const BorderMatchInfo& borderMatchInfo, const Tile& matchedTile) const
    {
        const bool isNormalMatch = borderMatchInfo.m_MatchType == BorderMatchType::Normal;
        const BorderIndex matchingBorderIndex = borderMatchInfo.m_MatchingBorderIndex;
        Image reorderedImage;

        if (matchingBorderIndex == BorderIndex::Top)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipHorizontally() : matchedTile.GetImage();
        }
        else if (matchingBorderIndex == BorderIndex::Bottom)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipVertically() : matchedTile.GetImage().Rotate180();
        }
        else if (matchingBorderIndex == BorderIndex::Left)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipVertically().Rotate90Right() : matchedTile.GetImage().Rotate90Right();
        }
        else if (matchingBorderIndex == BorderIndex::Right)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipVertically().Rotate90Left() : matchedTile.GetImage().Rotate90Left();
        }

        return reorderedImage;
    }

    void ImageMatcher::InitializeRows(const Problem& problem)
    {
        for (TileRow& currentRow : m_TileGrid)
        {
            Image reorderedImage { };
            const Tile* previousTile = &currentRow[0];

            while (std::optional<BorderMatchInfo> borderMatch = problem.GetMatchingTileFor(*previousTile, BorderIndex::Right))
            {
                const Tile& matchedTile = problem.GetTile(borderMatch->m_TileID);
                const bool isNormalMatch = borderMatch->m_MatchType == BorderMatchType::Normal;

                reorderedImage = FixAlignmentWithRightBorder(*borderMatch, matchedTile);
                previousTile = &currentRow.emplace_back(matchedTile.GetTileID(), std::move(reorderedImage));
            }
        }
    }

    // Yes this is the same abomination as before but for the right border.
    Image ImageMatcher::FixAlignmentWithRightBorder(const BorderMatchInfo& borderMatchInfo, const Tile& matchedTile) const
    {
        const bool isNormalMatch = borderMatchInfo.m_MatchType == BorderMatchType::Normal;
        const BorderIndex matchingBorderIndex = borderMatchInfo.m_MatchingBorderIndex;
        Image reorderedImage { };

        if (matchingBorderIndex == BorderIndex::Left)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipVertically() : matchedTile.GetImage();
        }
        else if (matchingBorderIndex == BorderIndex::Right)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipHorizontally() : matchedTile.GetImage().Rotate180();
        }
        else if (matchingBorderIndex == BorderIndex::Top)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipHorizontally().Rotate90Left() : matchedTile.GetImage().Rotate90Left();
        }
        else if (matchingBorderIndex == BorderIndex::Bottom)
        {
            reorderedImage = isNormalMatch ? matchedTile.GetImage().FlipHorizontally().Rotate90Right() : matchedTile.GetImage().Rotate90Right();
        }

        return reorderedImage;
    }

    TileGrid ImageMatcher::ExtractBorders(const TileGrid& matchImageData) const
    {
        TileGrid borderlessImageData;
        for (const TileRow& matchRow : matchImageData)
        {
            TileRow& borderlessRow = borderlessImageData.emplace_back();
            for (const Tile& tile : matchRow)
            {
                borderlessRow.emplace_back(tile.GetTileID(), tile.GetImage().ExtractBorders());
            }
        }
        return borderlessImageData;
    }

    Image ImageMatcher::MergeImageData(const TileGrid& matchImage) const
    {
        Image mergedImage;

        for (const TileRow& matchRow : matchImage)
        {
            const std::size_t rowHeight = matchRow[0].GetImage().GetHeight();
            for (std::size_t i = 0; i < rowHeight; i++)
            {
                auto accumulateTiles = [i](std::string current, const Tile& tile) -> std::string
                {
                    return current + tile.GetImage()[i];
                };

                mergedImage.GetImageData().emplace_back(std::accumulate(matchRow.cbegin(), matchRow.cend(), std::string { "" }, accumulateTiles));
            }
        }

        return mergedImage;
    }
}