#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "wavprocessor.h"
#include "converters.h"
#include "config.h"
#include "exceptions.h"

void printHelp() {
    std::cout << "Usage: sound_processor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]\n";
    std::cout << "Supported converters:\n";
    for (const auto& converter : ConverterFactory::getAvailableConverters()) {
        std::cout << "  " << converter.first << ": " << converter.second << "\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2 || std::string(argv[1]) == "-h") {
        printHelp();
        return 0;
    }

    try {
        if (argc < 5 || std::string(argv[1]) != "-c") {
            throw CommandLineException("Incorrect arguments. Use -h for help.");
        }

        std::string configPath = argv[2];
        std::string outputPath = argv[3];
        std::vector<std::string> inputPaths(argv + 4, argv + argc);

        registerDefaultConverters();

        ConfigProcessor configProcessor(configPath);
        std::vector<std::unique_ptr<Converter>> converters = configProcessor.parseConfig(inputPaths);

        WavProcessor outputProcessor(inputPaths[0]);
        //outputProcessor.printInfo();
        for (auto& converter : converters) {
            converter->process(outputProcessor.getSamples(), outputProcessor.getSampleRate());
        }
        //outputProcessor.printInfo();
        outputProcessor.save(outputPath);

        std::cout << "Processing completed successfully. Output saved to " << outputPath << ".\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
