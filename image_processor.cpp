#include "Parser_and_controller/parser.h"
#include "Reading_and_writing/reader.h"
#include "Reading_and_writing/writer.h"
#include "Parser_and_controller/filter_controller.h"

#include <stdexcept>

int main(int argc, char** argv) {
    CommandLineParser input_element;
    try {
        input_element.Parse(argc, argv);
    } catch (const std::exception) {
        throw std::invalid_argument("Couldn't make to open the file " + input_element.GetInputFileName());
    }

    const std::string input_file = input_element.GetInputFileName();
    const std::string output_file = input_element.GetOutputFileName();

    read_and_write::Reader reader(input_file);
    Image image = reader.GetImage();

    FilterController controller;
    controller.ApplyInputFilters(input_element.GetVectorOfFilters(), image);

    read_and_write::Writer writer(output_file);
    writer.WriteToFile(image);

    return 0;
}
