#include <catch.hpp>

#include "parser_and_controller/parser.h"
#include "parser_and_controller/filter_controller.h"
#include "Image/image.h"

TEST_CASE("IncorrectNameOfFilter") {
    FilterDescription filter;
    filter.filter_name = "-wrong_name";
    filter.filter_parameters = {};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("crop: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-crop";
    filter.filter_parameters = {"800"};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Grayscale: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-gs";
    filter.filter_parameters = {"800"};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Negative: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-neg";
    filter.filter_parameters = {"800"};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Sharpening: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-sharp";
    filter.filter_parameters = {"800"};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Edge Detection: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-edge";
    filter.filter_parameters = {};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Gaussian Blur: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-blur";
    filter.filter_parameters = {};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}

TEST_CASE("Custom Filter: incorrect number of parameters") {
    FilterDescription filter;
    filter.filter_name = "-custom";
    filter.filter_parameters = {"800"};
    std::vector<FilterDescription> filters_with_parameters = {filter};

    Image image;
    FilterController controller;
    REQUIRE_THROWS(controller.ApplyInputFilters(filters_with_parameters, image));
}
