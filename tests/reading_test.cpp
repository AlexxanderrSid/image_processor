#include <catch.hpp>

#include "reading_and_writing/reader.h"

TEST_CASE("Wrong image format: JPG") {
    const std::string input_file = "test_photo.jpg";

    read_and_write::Reader reader(input_file);
    REQUIRE_THROWS(reader.GetImage());
}

TEST_CASE("Cannot open file: non-existing path") {
    const std::string input_file = "test_foto.jpg";

    read_and_write::Reader reader(input_file);
    REQUIRE_THROWS(reader.GetImage());
}
