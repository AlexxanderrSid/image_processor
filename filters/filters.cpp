#include "filters.h"

template <typename T>
void BaseFilter::ApplyMatrix(const std::vector<std::vector<T>>& matrix_to_apply, Image& image) const {
    std::vector<std::vector<Image::Color>> copy_of_image = image.GetImageData();
    Image::BitmapInfoHeader& image_data = image.GetStructureInfoHeader();
    std::vector<std::vector<Image::Color>>& image_bitmap = image.GetImageData();
    int32_t height = image_data.biHeight;
    int32_t width = image_data.biWidth;

    for (int32_t row = 0; row < height; ++row) {
        for (int32_t column = 0; column < width; ++column) {

            int32_t height_radius = static_cast<int32_t>(matrix_to_apply.size() / 2);
            int32_t width_radius = static_cast<int32_t>(matrix_to_apply[0].size() / 2);
            Image::Color new_color;

            double sum_red = 0;
            double sum_green = 0;
            double sum_blue = 0;

            for (int32_t x_offset = -width_radius; x_offset <= width_radius; ++x_offset) {
                for (int32_t y_offset = -height_radius; y_offset <= height_radius; ++y_offset) {

                    int32_t x = column + x_offset;
                    int32_t y = row + y_offset;

                    x = std::clamp(x, 0, width - 1);

                    y = std::clamp(y, 0, height - 1);

                    sum_red += (matrix_to_apply[height_radius + y_offset][width_radius + x_offset] *
                                (static_cast<double>(copy_of_image[y][x].red) / constant::MAX_COLOR_VALUE_DOUBLE));
                    sum_green += (matrix_to_apply[height_radius + y_offset][width_radius + x_offset] *
                                  (static_cast<double>(copy_of_image[y][x].green) / constant::MAX_COLOR_VALUE_DOUBLE));
                    sum_blue += (matrix_to_apply[height_radius + y_offset][width_radius + x_offset] *
                                 (static_cast<double>(copy_of_image[y][x].blue) / constant::MAX_COLOR_VALUE_DOUBLE));
                }
            }

            new_color.red = static_cast<uint8_t>(
                std::round(constant::MAX_COLOR_VALUE_INT * (std::min(1.0, std::max(0.0, sum_red)))));
            new_color.green = static_cast<uint8_t>(
                std::round(constant::MAX_COLOR_VALUE_INT * (std::min(1.0, std::max(0.0, sum_green)))));
            new_color.blue = static_cast<uint8_t>(
                std::round(constant::MAX_COLOR_VALUE_INT * (std::min(1.0, std::max(0.0, sum_blue)))));

            image_bitmap[row][column] = new_color;
        }
    }
}

Crop::Crop(int32_t width, int32_t height) : width_(width), height_(height) {
}

void Crop::ApplyFilter(Image& image) {
    Image::BitmapInfoHeader& image_info = image.GetStructureInfoHeader();
    int32_t width = image_info.biWidth;
    int32_t height = image_info.biHeight;

    image_info.biWidth = std::min(width, width_);
    image_info.biHeight = std::min(height, height_);
}

void GrayScale::ApplyFilter(Image& image) {
    Image::BitmapInfoHeader& image_info = image.GetStructureInfoHeader();
    std::vector<std::vector<Image::Color>>& image_data = image.GetImageData();
    int32_t width = image_info.biWidth;
    int32_t height = image_info.biHeight;

    for (int32_t i = 0; i < height; ++i) {
        for (int32_t j = 0; j < width; ++j) {
            uint8_t new_color =
                static_cast<uint8_t>(static_cast<double>(image_data[i][j].red) * constant::RED_MULTIPLIER +
                                     static_cast<double>(image_data[i][j].green) * constant::GREEN_MULTIPLIER +
                                     static_cast<double>(image_data[i][j].blue) * constant::BLUE_MULTIPLIER);
            image_data[i][j].SetColor(new_color, new_color, new_color);
        }
    }
}

void Negative::ApplyFilter(Image& image) {
    Image::BitmapInfoHeader& image_info = image.GetStructureInfoHeader();
    std::vector<std::vector<Image::Color>>& image_data = image.GetImageData();
    int32_t width = image_info.biWidth;
    int32_t height = image_info.biHeight;

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            image_data[i][j].SetColor(constant::MAX_COLOR_VALUE_INT - image_data[i][j].blue,
                                      constant::MAX_COLOR_VALUE_INT - image_data[i][j].green,
                                      constant::MAX_COLOR_VALUE_INT - image_data[i][j].red);
        }
    }
}

void Sharpening::ApplyFilter(Image& image) {
    ApplyMatrix(sharpening_matrix_, image);
}

EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}

void EdgeDetection::ApplyFilter(Image& image) {
    Image::BitmapInfoHeader& image_data = image.GetStructureInfoHeader();
    std::vector<std::vector<Image::Color>>& image_bitmap = image.GetImageData();
    int32_t width = image_data.biWidth;
    int32_t height = image_data.biHeight;

    GrayScale::ApplyFilter(image);
    ApplyMatrix(edge_detection_matrix_, image);

    for (int32_t row = 0; row < height; ++row) {
        for (int32_t column = 0; column < width; ++column) {
            if (image_bitmap[row][column].red / constant::MAX_COLOR_VALUE_DOUBLE > threshold_) {
                image_bitmap[row][column] = Image::Color(constant::MAX_COLOR_VALUE_INT, constant::MAX_COLOR_VALUE_INT,
                                                         constant::MAX_COLOR_VALUE_INT);
            } else {
                image_bitmap[row][column] = Image::Color(0, 0, 0);
            }
        }
    }
}

void CustomFilter::ApplyFilter(Image& image) {
    auto& image_data = image.GetStructureInfoHeader();
    auto& image_bitmap = image.GetImageData();
    auto copy = image_bitmap;
    int height = image_data.biHeight;
    int width = image_data.biWidth;

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(constant::LEFT_RANGE_BORDER, constant::RIGHT_RANGE_BORDER);
    int mean = uniform_dist(e1);

    for (int row = 0; row < height; row += 2) {
        for (int column = 0; column < width; ++column) {
            Image::Color new_color;
            new_color.red = constant::MAX_COLOR_VALUE_INT - copy[row][(column + mean) % width].red;
            image_bitmap[row][column] = new_color;
        }
    }
    for (int row = 1; row < height; row += 2) {
        for (int column = 0; column < width; ++column) {
            Image::Color new_color;
            new_color.blue = constant::CUSTOM_FILTER_CONSTANT - copy[row][(column - mean) % width].blue;
            image_bitmap[row][column] = new_color;
            image_bitmap[row][column] = new_color;
        }
    }
}

GaussianBlur::GaussianBlur(double sigma) : sigma_(sigma) {
}

void GaussianBlur::ApplyFilter(Image& image) {
    int32_t matrix_size = 2 * 3 * static_cast<int32_t>(std::ceil(sigma_)) + 1;

    std::vector<std::vector<double>> horizontal_gaussian_matrix = {{}};
    horizontal_gaussian_matrix[0].reserve(matrix_size);
    std::vector<std::vector<double>> vertical_gaussian_matrix;
    vertical_gaussian_matrix.reserve(matrix_size);
    for (int32_t x = -matrix_size / 2; x <= matrix_size / 2; ++x) {
        double coefficient = GaussianFunction(x, sigma_);
        horizontal_gaussian_matrix[0].push_back(coefficient);
        vertical_gaussian_matrix.push_back({coefficient});
    }

    ApplyMatrix(vertical_gaussian_matrix, image);
    ApplyMatrix(horizontal_gaussian_matrix, image);
}

double GaussianBlur::GaussianFunction(int32_t x, double sigma) const {
    return pow(M_E, (-pow(x, 2)) / (2 * pow(sigma_, 2))) / sqrt(2 * M_PI * pow(sigma_, 2));
}
