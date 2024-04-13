#include "writer.h"

read_and_write::Writer::Writer(const std::string& file_path) : path_(file_path) {
}

void read_and_write::Writer::WriteToFile(Image& image) {

    std::ofstream output_file;
    output_file.open(path_);

    if (errno == EACCES) {
        throw std::invalid_argument("ERROR: No permission to open file: " + path_);
    }

    Image::BitmapFileHeader& file_header = image.GetStructureFileHeader();
    output_file.write(reinterpret_cast<char*>(&file_header), constant::FILE_HEADER_SIZE);

    if (file_header.Format != constant::BMP_FORMAT) {
        throw std::invalid_argument("ERROR: Wrong format of file: " + path_);
    }

    try {
        Image::BitmapInfoHeader& file_info_header = image.GetStructureInfoHeader();
        output_file.write(reinterpret_cast<char*>(&file_info_header), constant::INFO_HEADER_SIZE);

        std::vector<std::vector<Image::Color>> image_data = image.GetImageData();
        const size_t padding_size = (constant::MAX_PADDING_SIZE - (file_info_header.biWidth * constant::NUM_OF_PIXELS) %
                                                                      constant::MAX_PADDING_SIZE) %
                                    constant::MAX_PADDING_SIZE;

        for (size_t i = 0; i < file_info_header.biHeight; ++i) {
            for (size_t j = 0; j < file_info_header.biWidth; ++j) {
                unsigned char pixel[constant::NUM_OF_PIXELS];
                Image::Color color = image.GetColor(file_info_header.biHeight - i - 1, j);
                pixel[0] = static_cast<unsigned char>(color.blue);
                pixel[1] = static_cast<unsigned char>(color.green);
                pixel[2] = static_cast<unsigned char>(color.red);
                output_file.write(reinterpret_cast<char*>(&pixel), constant::NUM_OF_PIXELS);
            }
            for (size_t j = 0; j < padding_size; ++j) {
                output_file.write("\0", sizeof(uint8_t));
            }
        }

        output_file.close();
    } catch (std::exception& exception) {
        throw std::invalid_argument("Error occurred during writing file: " + path_);
    }
}