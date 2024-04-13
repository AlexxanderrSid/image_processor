#pragma once

#include "../constant.h"
#include "../Image/image.h"

#include <fstream>
#include <string>
#include <stdexcept>

namespace read_and_write {
class Reader {
public:
    explicit Reader(const std::string& file_path);

    Image GetImage();

private:
    std::string path_;
};
}  // namespace read_and_write
