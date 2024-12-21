#include "interface.h"
#include <iostream>
#include <sstream>
#include <fstream>

Interface::Interface(Game& game, FileManager& fileManager) : game(game), fileManager(fileManager) {}

Interface::~Interface() {}

void Interface::run() {
    std::string command;

    while (true) {
        command = getCommand();

        if (command.substr(0, 4) == "dump") {
            std::istringstream strs(command.substr(5));
            std::string filename;
            strs >> filename;
            executeDump(filename);
        }
        else if (command.substr(0, 4) == "tick" || command.substr(0, 1) == "t") {
            int n = 1;
            if (command.substr(0, 4) == "tick" && command.length() > 4) {
                std::istringstream strs(command.substr(5));
                strs >> n;
            }
            else if (command.substr(0, 1) == "t" && command.length() > 1) {
                std::istringstream strs(command.substr(2));
                strs >> n;
            }
            executeTick(n);
        }
        else if (command == "help") {
            executeHelp();
        }
        else if (command == "exit") {
            executeExit();
            break;
        }
        else if (command.substr(0, 4) == "save") {
            std::istringstream strs(command.substr(5));
            std::string filename;
            strs >> filename;
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open file '" << filename << "' for saving!" << std::endl;
            }
            else {
                executeSave(file);
            }
        }
        else if (command.substr(0, 4) == "load") {
            std::istringstream strs(command.substr(5));
            std::string filename;
            strs >> filename;
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open file '" << filename << "' for loading!" << std::endl;
            }
            else {
                executeLoad(file);
            }
        }
        else {
            std::cerr << "Unknown command: " << command << std::endl;
        }
    }
}

std::string Interface::getCommand() {
    std::cout << "Enter command: ";
    std::string command;
    std::getline(std::cin, command);
    return command;
}

void Interface::executeDump(const std::string& filename) {
    if (!filename.empty()) {
        if (fileManager.saveToFile(filename, game.getAliveCells())) {
            std::cout << "Universe saved to " << filename << std::endl;
        }
        else {
            std::cerr << "Error saving universe to " << filename << std::endl;
        }
    }
    else {
        std::cerr << "Error: Please specify a filename after 'dump'." << std::endl;
    }
}

void Interface::executeTick(int n) {
    for (int i = 0; i < n; ++i) {
        game.processGeneration();
    }
    game.printField();
}

void Interface::executeHelp() {
    std::cout << "Commands:\n";
    std::cout << "  dump <filename>  - Save the universe to the specified file.\n";
    std::cout << "  tick <n=1>       - Calculate n iterations (default is 1) and print the result.\n";
    std::cout << "  t <n=1>          - Shortcut for 'tick <n>'.\n";
    std::cout << "  exit             - Exit the game.\n";
    std::cout << "  save <filename>  - Save the current state of game to the specified file.\n";
    std::cout << "  load <filename>  - Load the state of game from the specified file.\n";
    std::cout << "  exit             - Exit the game.\n";
    std::cout << "  help             - Print this help message.\n";
}

void Interface::executeExit() {
    std::cout << "Exiting the game..." << std::endl;
}

void Interface::executeSave(std::ofstream& file) {
    file << game;
    std::cout << "Game was succesfully saved." << std::endl;
}

void Interface::executeLoad(std::ifstream& file) {
    file >> game;
    game.refreshField();
    game.printField();
}