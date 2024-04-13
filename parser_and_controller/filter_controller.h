#pragma once

#include "parser.h"
#include "../filters/filters.h"
#include "../Image/image.h"

#include <vector>
#include <iostream>
#include <stdexcept>

class FilterController {
public:
    void ApplyInputFilters(std::vector<FilterDescription> filters_with_parameters, Image& image);
};
