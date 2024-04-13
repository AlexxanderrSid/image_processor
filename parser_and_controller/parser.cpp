#include "../constant.h"
#include "parser.h"

void CommandLineParser::Parse(int argc, char** argv) {
    if (argc == 0) {
        throw std::invalid_argument(
            "Description of cmd arguments: {имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя "
            "фильтра 1} [параметр фильтра 1] "
            "[параметр фильтра 2] ...] [-{имя фильтра 2} [параметр фильтра 1] [параметр фильтра 2] ...] ... ");
    } else if (argc - 1 < constant::MIN_NUMBER_OF_PARAMETERS) {
        throw std::invalid_argument("ERROR: Should be at least 3 parameters ");
    }

    input_file_name_ = argv[constant::INPUT_FILE_POSITION];
    output_file_name_ = argv[constant::OUTPUT_FILE_POSITION];

    if (argc - 1 == constant::MIN_NUMBER_OF_PARAMETERS) {
        return;
    }  // Empty filter list

    for (size_t i = constant::MIN_NUMBER_OF_PARAMETERS + 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            FilterDescription description;
            description.filter_name = argv[i];
            filters_with_parameters_.push_back(description);
        } else {
            if (filters_with_parameters_.empty()) {
                throw std::invalid_argument("ERROR: Incorrect name of filter: -<filter_name> ");
            }
            filters_with_parameters_[filters_with_parameters_.size() - 1].filter_parameters.emplace_back(argv[i]);
        }
    }
}

std::string CommandLineParser::GetInputFileName() {
    return input_file_name_;
}

std::string CommandLineParser::GetOutputFileName() {
    return output_file_name_;
}

std::vector<FilterDescription> CommandLineParser::GetVectorOfFilters() {
    return filters_with_parameters_;
}
