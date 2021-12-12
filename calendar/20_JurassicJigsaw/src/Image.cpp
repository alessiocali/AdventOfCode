#include <Image.h>

#include <string>

namespace JurassicJigsaw
{
    Image::Image(const ImageData& tileData)
        : m_ImageData(tileData)
    { }

    Image::Image(ImageData&& tileData)
        : m_ImageData(std::move(tileData))
    { }

    Image Image::Rotate90Left() const
    {
        auto getRotate90LeftPixel = [this](std::size_t i, std::size_t j) { return m_ImageData[j][GetWidth() - 1 - i]; };
        return TransformWithPixelGetter(GetHeight(), GetWidth(), getRotate90LeftPixel);
    }

    Image Image::Rotate90Right() const
    {
        auto getRotate90RightPixel = [this](std::size_t i, std::size_t j) { return m_ImageData[GetHeight() - 1 - j][i]; };
        return TransformWithPixelGetter(GetHeight(), GetWidth(), getRotate90RightPixel);
    }

    Image Image::Rotate180() const
    {
        auto getRotate180Pixel = [this](std::size_t i, std::size_t j) { return m_ImageData[GetHeight() - 1 - i][GetWidth() - 1 - j]; };
        return TransformWithPixelGetter(GetWidth(), GetHeight(), getRotate180Pixel);
    }

    Image Image::FlipHorizontally() const
    {
        auto getFlipHorizontallyPixel = [this](std::size_t i, std::size_t j) { return m_ImageData[i][GetWidth() - 1 - j];  };
        return TransformWithPixelGetter(GetWidth(), GetHeight(), getFlipHorizontallyPixel);
    }

    Image Image::FlipVertically() const
    {
        auto getFlipVerticallyPixel = [this](std::size_t i, std::size_t j) { return m_ImageData[GetHeight() - 1 - i][j];  };
        return TransformWithPixelGetter(GetWidth(), GetHeight(), getFlipVerticallyPixel);
    }

    Image Image::ExtractBorders() const
    {
        Image newImage;
        ImageData& newData = newImage.m_ImageData;
        for (std::size_t i = 1; i < m_ImageData.size() - 1; i++)
        {
            const std::string& line = m_ImageData[i];
            const std::size_t lineLength = line.size();
            newData.emplace_back(line.substr(1, lineLength - 2));
        }
        return newImage;
    }

    template<typename PixelGetter>
    Image Image::TransformWithPixelGetter(const std::size_t newWidth, const std::size_t newHeight, PixelGetter pixelGetter) const
    {
        Image transformedImage;
        ImageData& transformedData = transformedImage.GetImageData();
        transformedData.reserve(GetHeight());

        for (std::size_t i = 0; i < newHeight; i++)
        {
            std::string& nextRow = transformedData.emplace_back();
            for (std::size_t j = 0; j < newWidth; j++)
            {
                nextRow += pixelGetter(i, j);
            }
        }

        return transformedImage;
    }
}