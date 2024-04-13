#pragma once

#include <string>
#include <vector>
#include <stdexcept>

struct FilterDescription {
    std::string filter_name;
    std::vector<std::string> filter_parameters;
};

class CommandLineParser {
public:
    void Parse(int argc, char** argv);
    std::string GetInputFileName();
    std::string GetOutputFileName();
    std::vector<FilterDescription> GetVectorOfFilters();

private:
    std::string input_file_name_;
    std::string output_file_name_;
    std::vector<FilterDescription> filters_with_parameters_;
};
