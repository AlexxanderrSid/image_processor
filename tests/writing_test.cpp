#include <catch.hpp>

#include "reading_and_writing/writer.h"

TEST_CASE("Wrong image format: JPG") {
    const std::string output_file = "test_photo.jpg";

    Image image;
    read_and_write::Writer writer(output_file);
    REQUIRE_THROWS(writer.WriteToFile(image));
}
