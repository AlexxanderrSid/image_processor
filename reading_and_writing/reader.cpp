#include "reader.h"
#include "writer.h"

read_and_write::Reader::Reader(const std::string& file_path) : path_(file_path) {
}

Image read_and_write::Reader::GetImage() {
    std::ifstream input_file;
    input_file.open(path_);

    if (!input_file.is_open()) {
        throw std::invalid_argument("ERROR: Can't open file: " + path_);
    }

    if (errno == EACCES) {
        throw std::invalid_argument("ERROR: No permission to open file: " + path_);
    }

    Image::BitmapFileHeader file_header;
    input_file.read(reinterpret_cast<char*>(&file_header.Format), sizeof(file_header.Format));

    if (file_header.Format != constant::BMP_FORMAT) {
        throw std::invalid_argument("ERROR: Wrong format of file: " + path_);
    }

    input_file.read(reinterpret_cast<char*>(&file_header.BitmapFileSize), sizeof(file_header.BitmapFileSize));
    input_file.read(reinterpret_cast<char*>(&file_header.BitmapFileReserved1), sizeof(file_header.BitmapFileReserved1));
    input_file.read(reinterpret_cast<char*>(&file_header.BitmapFileReserved2), sizeof(file_header.BitmapFileReserved2));
    input_file.read(reinterpret_cast<char*>(&file_header.BitmapOffsetBits), sizeof(file_header.BitmapOffsetBits));

    Image::BitmapInfoHeader file_info_header;
    try {
        input_file.read(reinterpret_cast<char*>(&file_info_header.biSize), sizeof(file_info_header.biSize));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biWidth), sizeof(file_info_header.biWidth));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biHeight), sizeof(file_info_header.biHeight));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biPlanes), sizeof(file_info_header.biPlanes));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biBitCount), sizeof(file_info_header.biBitCount));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biCompression),
                        sizeof(file_info_header.biCompression));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biSizeImage), sizeof(file_info_header.biSizeImage));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biXPelsPerMeter),
                        sizeof(file_info_header.biXPelsPerMeter));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biYPelsPerMeter),
                        sizeof(file_info_header.biYPelsPerMeter));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biClrUsed), sizeof(file_info_header.biClrUsed));
        input_file.read(reinterpret_cast<char*>(&file_info_header.biClrImportant),
                        sizeof(file_info_header.biClrImportant));

        std::vector<std::vector<Image::Color>> image_data(file_info_header.biHeight);
        std::vector<Image::Color> temporary(file_info_header.biWidth);
        const size_t padding_size = (constant::MAX_PADDING_SIZE - (file_info_header.biWidth * constant::NUM_OF_PIXELS) %
                                                                      constant::MAX_PADDING_SIZE) %
                                    constant::MAX_PADDING_SIZE;

        for (size_t i = 0; i < file_info_header.biHeight; ++i) {
            for (size_t j = 0; j < file_info_header.biWidth; ++j) {
                unsigned char pixel[constant::NUM_OF_PIXELS];
                input_file.read(reinterpret_cast<char*>(&pixel), constant::NUM_OF_PIXELS);
                temporary[j].SetColor(static_cast<uint8_t>(pixel[0]), static_cast<uint8_t>(pixel[1]),
                                      static_cast<uint8_t>(pixel[2]));
            }
            image_data[file_info_header.biHeight - i - 1] = temporary;
            input_file.ignore(static_cast<int>(padding_size));
        }

        Image image(image_data, file_header, file_info_header);

        input_file.close();
        return image;
    } catch (std::exception& exception) {
        throw std::invalid_argument("Error occurred during reading file: " + path_);
    }
}
