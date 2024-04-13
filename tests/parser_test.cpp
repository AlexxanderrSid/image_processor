#include <catch.hpp>
#include <string>

#include "parser_and_controller/parser.h"

TEST_CASE("Zero arguments") {
    int argc = 0;
    char** argv = nullptr;

    CommandLineParser parsed_params;

    REQUIRE_THROWS(parsed_params.Parse(argc, argv));
}

TEST_CASE("Less than three arguments") {
    int argc = 1;
    char** argv = new char*[argc];
    CommandLineParser parsed_params;

    const std::string working_file_name = "./image_processor";
    argv[0] = new char[working_file_name.size() + 1];
    std::strncpy(argv[0], working_file_name.data(), working_file_name.size() + 1);

    REQUIRE_THROWS(parsed_params.Parse(argc, argv));
}

TEST_CASE("Three argument") {
    const std::string working_file_name = "./image_processor";
    const std::string input_file_name = "input.txt";
    const std::string output_file_name = "output.txt";

    int argc = 3;
    char** argv = new char*[argc];
    argv[0] = new char[working_file_name.size() + 1];
    std::strncpy(argv[0], working_file_name.data(), working_file_name.size() + 1);
    argv[1] = new char[input_file_name.size() + 1];
    std::strncpy(argv[1], input_file_name.data(), input_file_name.size() + 1);
    argv[2] = new char[output_file_name.size() + 1];
    std::strncpy(argv[2], output_file_name.data(), output_file_name.size() + 1);

    CommandLineParser parsed_params;
    parsed_params.Parse(argc, argv);
    REQUIRE(input_file_name == parsed_params.GetInputFileName());
    REQUIRE(output_file_name == parsed_params.GetOutputFileName());
}

TEST_CASE("More than three argument") {
    static const int FIVE = 5;
    static const int SIX = 6;
    static const int SEVEN = 7;

    const std::string working_file_name = "./image_processor";
    const std::string input_file_name = "input.txt";
    const std::string output_file_name = "output.txt";
    const std::string first_filter_name = "-crop";
    const std::string first_filter_parameter_1 = "800";
    const std::string first_filter_parameter_2 = "600";
    const std::string second_filter_name = "-gs";

    int argc = SEVEN;
    char** argv = new char*[argc];

    argv[0] = new char[working_file_name.size() + 1];
    std::strncpy(argv[0], working_file_name.data(), working_file_name.size() + 1);
    argv[1] = new char[input_file_name.size() + 1];
    std::strncpy(argv[1], input_file_name.data(), input_file_name.size() + 1);
    argv[2] = new char[output_file_name.size() + 1];
    std::strncpy(argv[2], output_file_name.data(), output_file_name.size() + 1);

    argv[3] = new char[first_filter_name.size() + 1];
    std::strncpy(argv[3], first_filter_name.data(), first_filter_name.size() + 1);
    argv[4] = new char[first_filter_parameter_1.size() + 1];
    std::strncpy(argv[4], first_filter_parameter_1.data(), first_filter_parameter_1.size() + 1);
    argv[FIVE] = new char[first_filter_parameter_2.size() + 1];
    std::strncpy(argv[FIVE], first_filter_parameter_2.data(), first_filter_parameter_2.size() + 1);
    argv[SIX] = new char[second_filter_name.size() + 1];
    std::strncpy(argv[SIX], second_filter_name.data(), second_filter_name.size() + 1);

    CommandLineParser parsed_params;
    parsed_params.Parse(argc, argv);
    REQUIRE(input_file_name == parsed_params.GetInputFileName());
    REQUIRE(output_file_name == parsed_params.GetOutputFileName());
    REQUIRE(first_filter_name == parsed_params.GetVectorOfFilters()[0].filter_name);
    REQUIRE(first_filter_parameter_1 == parsed_params.GetVectorOfFilters()[0].filter_parameters[0]);
    REQUIRE(first_filter_parameter_2 == parsed_params.GetVectorOfFilters()[0].filter_parameters[1]);
    REQUIRE(second_filter_name == parsed_params.GetVectorOfFilters()[1].filter_name);
}

TEST_CASE("Incorrect argument") {
    const std::string working_file_name = "./image_processor";
    const std::string input_file_name = "input.txt";
    const std::string output_file_name = "output.txt";
    const std::string filter_name = "neg";

    int argc = 4;
    char** argv = new char*[argc];
    argv[0] = new char[working_file_name.size() + 1];
    std::strncpy(argv[0], working_file_name.data(), working_file_name.size() + 1);
    argv[1] = new char[input_file_name.size() + 1];
    std::strncpy(argv[1], input_file_name.data(), input_file_name.size() + 1);
    argv[2] = new char[output_file_name.size() + 1];
    std::strncpy(argv[2], output_file_name.data(), output_file_name.size() + 1);

    argv[3] = new char[filter_name.size() + 1];
    std::strncpy(argv[3], filter_name.data(), filter_name.size() + 1);

    CommandLineParser parsed_params;
    REQUIRE_THROWS(parsed_params.Parse(argc, argv));
}
