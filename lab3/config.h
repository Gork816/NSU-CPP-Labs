#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Converters.h"

class ConfigProcessor {
    std::string configPath;

public:
    explicit ConfigProcessor(const std::string& configPath);
    std::vector<std::unique_ptr<Converter>> parseConfig(const std::vector<std::string>& inputFiles);
};
