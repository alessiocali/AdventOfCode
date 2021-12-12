#pragma once
#include <Image.h>

namespace JurassicJigsaw
{
    static const ImageData SEA_MONSTER_PATTERN_DATA
    {
        "                  # ",
        "#    ##    ##    ###",
        " #  #  #  #  #  #   "
    };

    class PatternSearcher
    {
    public:
        PatternSearcher(const Image& sourceImage, const Image& pattern);
        Image SubtractPattern();

    private:
        struct PatternFoundPosition
        {
            PatternFoundPosition(std::size_t row, std::size_t col)
                : m_Row(row)
                , m_Col(col)
            { }

            std::size_t m_Row { 0 };
            std::size_t m_Col { 0 };
        };

        std::vector<PatternFoundPosition> m_FoundPositions;

        Image m_StoredImage;
        Image m_Pattern;

        void FindPatternInSourceImage();
        std::vector<PatternSearcher::PatternFoundPosition> FindTransformedPattern(const Image& pattern) const;
        bool IsTransformedPatternAtCoordinates(const Image& pattern, std::size_t i, std::size_t j) const;
    };
}