#pragma once
#include <string>
#include <vector>

namespace JurassicJigsaw
{
    using ImageData = std::vector<std::string>;

    class Image final
    {
    public:
        Image() = default;

        Image(const Image& other) = default;
        Image(Image&& other) = default;

        Image& operator=(const Image& other) = default;
        Image& operator=(Image&& other) = default;

        Image(const ImageData& tileData);
        Image(ImageData&& tileData);

        inline const ImageData& GetImageData() const { return m_ImageData; }
        inline ImageData& GetImageData() { return m_ImageData; }

        inline const std::string& operator[](const std::size_t i) const { return m_ImageData[i]; }
        inline std::string& operator[](const std::size_t i) { return m_ImageData[i]; }

        inline auto begin() { return m_ImageData.begin(); }
        inline auto end() { return m_ImageData.end(); }
        inline auto begin() const { return m_ImageData.cbegin(); }
        inline auto end() const { return m_ImageData.cend(); }

        inline std::size_t GetWidth() const { return m_ImageData.empty() ? 0 : m_ImageData[0].size(); }
        inline std::size_t GetHeight() const { return m_ImageData.size(); }

        Image Rotate90Left() const;
        Image Rotate90Right() const;
        Image Rotate180() const;

        Image FlipHorizontally() const;
        Image FlipVertically() const;

        Image ExtractBorders() const;

    private:
        ImageData m_ImageData;

        template<typename PixelGetter>
        Image TransformWithPixelGetter(const std::size_t newWidth, const std::size_t newHeight, PixelGetter pixelGetter) const;
    };
}