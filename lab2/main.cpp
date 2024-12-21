#include <iostream>
#include <cstdlib>
#include <string>
#include "game.h"
#include "filemanager.h"
#include "interface.h"


bool checkArguments(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage in offline mode: program -i <iterations> -o <filename>" << std::endl;
        return false;
    }

    int iterations = -1;
    std::string outputFilename;

    for (int i = 2; i < argc; i += 2) {
        std::string flag = argv[i];
        std::string value = argv[i + 1];

        if (flag == "-i") {
            try {
                iterations = std::stoi(value);
                if (iterations <= 0) {
                    throw std::invalid_argument("Iterations must be a positive integer.");
                }
            }
            catch (const std::exception&) {
                std::cerr << "Invalid value for -i: must be a positive integer." << std::endl;
                return false;
            }
        }
        else if (flag == "-o") {
            outputFilename = value;
        }
        else {
            std::cerr << "Unknown flag: " << flag << std::endl;
            return false;
        }
    }

    if (iterations == -1) {
        std::cerr << "Missing -i <iterations> argument." << std::endl;
        return false;
    }
    if (outputFilename.empty()) {
        std::cerr << "Missing -o <filename> argument." << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    std::string filename;

    if (argc < 2) {
        filename = "default.lif";
    }
    else {
        filename = argv[1];
    }

    FileManager fileManager;

    if (!fileManager.loadFromFile(filename)) {
        std::cerr << "Error while loading universe from file" << std::endl;
        return 1;
    }

    Game game;
    game.initializeFieldFromFile(fileManager);

    if (argc <= 2) {
        Interface interface(game, fileManager);
        interface.run();
    }
    else {
        if (!checkArguments(argc, argv)) {
            return 1;
        }
        for (short i = 0; i < short(argv[3]); ++i) {
            game.processGeneration();
        }
        fileManager.saveToFile(argv[5], game.getAliveCells());
    }

    return 0;
}
