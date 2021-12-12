#include <Solver.h>

#include <Parser.h>
#include <PatternSearcher.h>

#include <cassert>
#include <fstream>
#include <numeric>
#include <string>

namespace JurassicJigsaw
{
    void Solver::Init(std::string& input)
    {
        std::ifstream inputStream(input);
        assert(inputStream.is_open());

        Parser parser;
        for (std::string nextLine; std::getline(inputStream, nextLine); )
        {
            parser.ParseNextLine(nextLine);
        }

        m_Problem = parser.Finalize();
        m_ImageMatcher = ImageMatcher { m_Problem };
    }

    std::uint64_t Solver::SolveProblemA() const
    {
        const TileGrid& matchedTileGrid = m_ImageMatcher.GetTileGrid();
        const std::size_t imageWidth = matchedTileGrid[0].size();
        const std::size_t imageHeight = matchedTileGrid.size();

        return std::uint64_t { 1 }
            *matchedTileGrid[0][0].GetTileID()
            * matchedTileGrid[0][imageWidth - 1].GetTileID()
            * matchedTileGrid[imageHeight - 1][0].GetTileID()
            * matchedTileGrid[imageHeight - 1][imageWidth - 1].GetTileID();
    }

    std::uint32_t Solver::SolveProblemB() const
    {
        Image seaMonsterPattern { SEA_MONSTER_PATTERN_DATA };
        PatternSearcher patternSearcher { m_ImageMatcher.GetMergedImage(), seaMonsterPattern };
        Image patternSubtractedImage = patternSearcher.SubtractPattern();

        auto waterRoughnessAccumulator = [](std::uint32_t current, const std::string& line) -> std::uint32_t
        {
            return current + static_cast<std::uint32_t>(std::count(line.begin(), line.end(), '#'));
        };

        return std::accumulate(patternSubtractedImage.begin(), patternSubtractedImage.end(), std::uint32_t { 0 }, waterRoughnessAccumulator);
    }

    void Solver::DebugDisplay() const
    {
        std::cout << "Reordered image tiles" << std::endl;
        for (const TileRow& matchRow : m_ImageMatcher.GetTileGrid())
        {
            for (const Tile& orderedTile : matchRow)
            {
                std::cout << orderedTile.GetTileID() << " ";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl << "Reordered image (no borders)" << std::endl;
        for (const std::string& line : m_ImageMatcher.GetMergedImage())
        {
            std::cout << line << std::endl;
        }
    }
}