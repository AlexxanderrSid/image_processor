#include "filter_controller.h"

void FilterController::ApplyInputFilters(std::vector<FilterDescription> filters_with_parameters, Image& image) {

    for (const auto& [filter, parameters] : filters_with_parameters) {
        if (filter == "-crop") {
            if (parameters.size() != 2) {
                throw std::invalid_argument("ERROR: Incorrect number of arguments for Crop: 2 parameters required");
            }
            int32_t new_height = std::stoi(parameters[0]);
            int32_t new_width = std::stoi(parameters[1]);
            Crop crop_applier(new_height, new_width);
            crop_applier.ApplyFilter(image);
        } else if (filter == "-gs") {
            if (!parameters.empty()) {
                throw std::invalid_argument(
                    "ERROR: Incorrect number of arguments for Grayscale: 0 parameters required");
            }
            GrayScale gray_scale_applier;
            gray_scale_applier.ApplyFilter(image);
        } else if (filter == "-neg") {
            if (!parameters.empty()) {
                throw std::invalid_argument("ERROR: Incorrect number of arguments for Negative: 0 parameters required");
            }
            Negative negative_applier;
            negative_applier.ApplyFilter(image);
        } else if (filter == "-sharp") {
            if (!parameters.empty()) {
                throw std::invalid_argument(
                    "ERROR: Incorrect number of arguments for Sharpening: 0 parameters required");
            }
            Sharpening sharpening_applier;
            sharpening_applier.ApplyFilter(image);
        } else if (filter == "-edge") {
            if (parameters.size() != 1) {
                throw std::invalid_argument(
                    "ERROR: Incorrect number of arguments for Edge Detection: 1 parameters required");
            }
            double threshold = std::stod(parameters[0]);
            EdgeDetection edge_detection_applier(threshold);
            edge_detection_applier.ApplyFilter(image);
        } else if (filter == "-blur") {
            if (parameters.size() != 1) {
                throw std::invalid_argument(
                    "ERROR: Incorrect number of arguments for Gaussian Blur: 1 parameters required");
            }
            int32_t sigma = std::stoi(parameters[0]);
            GaussianBlur gaussian_blur_applier(sigma);
            gaussian_blur_applier.ApplyFilter(image);
        } else if (filter == "-custom") {
            if (!parameters.empty()) {
                throw std::invalid_argument(
                    "ERROR: Incorrect number of arguments for Custom Filter: 0 parameters required");
            }
            CustomFilter custom_applier;
            custom_applier.ApplyFilter(image);
        } else {
            throw std::invalid_argument("ERROR: Filter " + filter + " is not available\n" + "Available filters:\n" +
                                        "  Crop (-crop width height)\n" + "  Grayscale (-gs)\n" +
                                        "  Negative (-neg)\n" + "  Sharpening (-sharp)\n" +
                                        "  Edge Detection (-edge threshold)\n" + "  Gaussian Blur (-blur sigma)\n" +
                                        "  Custom Filter (-custom)\n");
        }
    }
}