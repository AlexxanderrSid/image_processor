#pragma once

#include "../constant.h"
#include "../image/image.h"

#include <fstream>
#include <string>
#include <stdexcept>

namespace read_and_write {
class Writer {
public:
    explicit Writer(const std::string& file_path);

    void WriteToFile(Image& image);

private:
    std::string path_;
};
}  // namespace read_and_write