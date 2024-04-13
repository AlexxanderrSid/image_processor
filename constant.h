#pragma once

#include <cstdint>

namespace constant {
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;
const int MAX_PADDING_SIZE = 4;
const int NUM_OF_PIXELS = 3;
const int MIN_NUMBER_OF_PARAMETERS = 2;
const uint16_t BMP_FORMAT = 0x4D42;
const int INPUT_FILE_POSITION = 1;
const int OUTPUT_FILE_POSITION = 2;
const int MAX_COLOR_VALUE_INT = 255;
const double MAX_COLOR_VALUE_DOUBLE = 255.0;
const int FIVE = 5;
const double RED_MULTIPLIER = 0.299;
const double GREEN_MULTIPLIER = 0.587;
const double BLUE_MULTIPLIER = 0.114;
const int LEFT_RANGE_BORDER = 100;
const int RIGHT_RANGE_BORDER = 350;
const int CUSTOM_FILTER_CONSTANT = 135;
}  // namespace constant
