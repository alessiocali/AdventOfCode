#include <PatternSearcher.h>

#include <functional>

namespace JurassicJigsaw
{
    PatternSearcher::PatternSearcher(const Image& sourceImage, const Image& pattern)
        : m_StoredImage(sourceImage)
        , m_Pattern(pattern)
    {
        FindPatternInSourceImage();
    }

    Image PatternSearcher::SubtractPattern()
    {
        Image subtractedImage = m_StoredImage;
        for (const PatternFoundPosition& foundPosition : m_FoundPositions)
        {
            for (std::size_t patternRow = 0; patternRow < m_Pattern.GetHeight(); patternRow++)
            {
                for (std::size_t patternCol = 0; patternCol < m_Pattern.GetWidth(); patternCol++)
                {
                    if (m_Pattern[patternRow][patternCol] == '#')
                    {
                        subtractedImage[foundPosition.m_Row + patternRow][foundPosition.m_Col + patternCol] = 'O';
                    }
                }
            }
        }
        return subtractedImage;
    }

    void PatternSearcher::FindPatternInSourceImage()
    {
        using ImageTransform = Image(const Image&);
        using TransformFunctor = std::function<ImageTransform>;

        auto identityTransform = [](const Image& image) { return image; };

        static const std::vector<TransformFunctor> rotationTransforms
        {
            TransformFunctor { identityTransform },
            TransformFunctor { &Image::Rotate90Right },
            TransformFunctor { &Image::Rotate90Left },
            TransformFunctor { &Image::Rotate180 }
        };

        static const std::vector<TransformFunctor> flipTransforms
        {
            TransformFunctor { identityTransform },
            TransformFunctor { &Image::FlipHorizontally },
            TransformFunctor { &Image::FlipVertically }
        };

        Image flippedPattern { m_Pattern };
        Image rotatedFlippedPattern { m_Pattern };
        for (auto flipIt = flipTransforms.begin(); m_FoundPositions.empty() && flipIt != flipTransforms.end(); flipIt++)
        {
            flippedPattern = std::invoke(*flipIt, m_Pattern);
            for (auto rotationIt = rotationTransforms.begin(); m_FoundPositions.empty() && rotationIt != rotationTransforms.end(); rotationIt++)
            {
                rotatedFlippedPattern = std::invoke(*rotationIt, flippedPattern);
                m_FoundPositions = FindTransformedPattern(rotatedFlippedPattern);
            }
        }

        m_Pattern = rotatedFlippedPattern;
    }

    std::vector<PatternSearcher::PatternFoundPosition> PatternSearcher::FindTransformedPattern(const Image& transformedPattern) const
    {
        std::vector<PatternSearcher::PatternFoundPosition> foundPositions;
        for (std::size_t i = 0; i + transformedPattern.GetHeight() - 1 < m_StoredImage.GetHeight(); i++)
        {
            for (std::size_t j = 0; j + transformedPattern.GetWidth() - 1 < m_StoredImage.GetWidth(); j++)
            {
                if (IsTransformedPatternAtCoordinates(transformedPattern, i, j))
                {
                    foundPositions.emplace_back(i, j);
                }
            }
        }
        return foundPositions;
    }

    bool PatternSearcher::IsTransformedPatternAtCoordinates(const Image& transformedPattern, std::size_t i, std::size_t j) const
    {
        for (std::size_t patternI = 0; patternI < transformedPattern.GetHeight(); patternI++)
        {
            for (std::size_t patternJ = 0; patternJ < transformedPattern.GetWidth(); patternJ++)
            {
                if (transformedPattern[patternI][patternJ] == '#' && m_StoredImage[i + patternI][j + patternJ] != '#')
                {
                    return false;
                }
            }
        }

        return true;
    }
}