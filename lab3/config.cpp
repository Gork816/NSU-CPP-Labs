#include "config.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

ConfigProcessor::ConfigProcessor(const std::string& configPath) : configPath(configPath) {}

std::vector<std::unique_ptr<Converter>> ConfigProcessor::parseConfig(const std::vector<std::string>& inputFiles) {
    std::ifstream file(configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + configPath);
    }

    std::vector<std::unique_ptr<Converter>> converters;
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string name;
        iss >> name;

        std::vector<std::string> args;
        std::string arg;
        while (iss >> arg) {
            if (arg[0] == '$') {
                int index = std::stoi(arg.substr(1)) - 1;
                if (index < 0 || index >= inputFiles.size()) {
                    throw std::runtime_error("Invalid input file reference: " + arg);
                }
                args.push_back(inputFiles[index]);
            }
            else {
                args.push_back(arg);
            }
        }

        converters.push_back(ConverterFactory::createConverter(name, args));
    }

    return converters;
}
