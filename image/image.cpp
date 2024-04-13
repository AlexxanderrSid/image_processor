#include "image.h"

Image::Color::Color(uint8_t color_blue, uint8_t color_green, uint8_t color_red) {
    SetColor(color_blue, color_green, color_red);
}

void Image::Color::SetColor(uint8_t color_blue, uint8_t color_green, uint8_t color_red) {
    blue = color_blue;
    green = color_green;
    red = color_red;
}

Image::Image(std::vector<std::vector<Color>>& image, Image::BitmapFileHeader bitmap_file_header,
             Image::BitmapInfoHeader bitmap_info_header)
    : image_(image), bitmap_file_header_(bitmap_file_header), bitmap_info_header_(bitmap_info_header) {
}

Image::BitmapFileHeader& Image::GetStructureFileHeader() {
    return bitmap_file_header_;
}

Image::BitmapInfoHeader& Image::GetStructureInfoHeader() {
    return bitmap_info_header_;
}

std::vector<std::vector<Image::Color>>& Image::GetImageData() {
    return image_;
}

Image::Color& Image::GetColor(size_t height, size_t width) {
    return image_[height][width];
}
