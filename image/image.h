#pragma once

#include "../constant.h"

#include <vector>
#include <locale>

class Image {
public:
    struct Color {
        Color() = default;
        Color(uint8_t blue, uint8_t green, uint8_t red);

        void SetColor(uint8_t color_blue, uint8_t color_green, uint8_t color_red);

        uint8_t blue = 0;
        uint8_t green = 0;
        uint8_t red = 0;
    };

#pragma pack(push, 1)
    struct BitmapFileHeader {
        uint16_t Format = 0;
        uint32_t BitmapFileSize = 0;
        uint16_t BitmapFileReserved1 = 0;
        uint16_t BitmapFileReserved2 = 0;
        uint32_t BitmapOffsetBits = 0;
    };
    struct BitmapInfoHeader {
        uint32_t biSize = 0;
        int32_t biWidth = 0;
        int32_t biHeight = 0;
        uint16_t biPlanes = 0;
        uint16_t biBitCount = 0;
        uint32_t biCompression = 0;
        uint32_t biSizeImage = 0;
        int32_t biXPelsPerMeter = 0;
        int32_t biYPelsPerMeter = 0;
        uint32_t biClrUsed = 0;
        uint32_t biClrImportant = 0;
    };
#pragma pack(pop)

public:
    BitmapFileHeader& GetStructureFileHeader();
    BitmapInfoHeader& GetStructureInfoHeader();
    std::vector<std::vector<Color>>& GetImageData();
    Image::Color& GetColor(size_t height, size_t width);

public:
    Image() = default;
    Image(std::vector<std::vector<Color>>& image, BitmapFileHeader bitmap_file_header,
          BitmapInfoHeader bitmap_info_header);
    ~Image() = default;

private:
    std::vector<std::vector<Color>> image_;
    Image::BitmapFileHeader bitmap_file_header_;
    Image::BitmapInfoHeader bitmap_info_header_;
};