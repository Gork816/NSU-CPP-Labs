#include "filemanager.h"
#include "grid.h"
#include <fstream>
#include <sstream>
#include <iostream>


FileManager::FileManager() : width(0), height(0), rules() {}

FileManager::~FileManager() {}

bool FileManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "'!" << std::endl;
        return false;
    }

    std::string line;

    std::getline(file, line);
    if (line != "#Life 1.06") {
        std::cerr << "Error: First line should be '#Life 1.06', but found '" << line << "'." << std::endl;
        return false;
    }

    std::getline(file, line);
    if (line.find("#N") == std::string::npos) {
        std::cout << "Error: Second line should be '#N <universe_name>'." << std::endl;
        name = filename;
    }
    else {
        name = line.substr(2);
        name = name.substr(1);
        std::getline(file, line);
    }

    std::string rulesStr;
    if (line.find("#R") == std::string::npos) {
        std::cout << "Warning: Third line should contain rules in format '#R Bx/Sy''." << std::endl;
        rulesStr = " B2/S23";
    }
    else {
        rulesStr = line.substr(2);
        std::getline(file, line);
    }
    rawRules = rulesStr.substr(1);
    size_t pos = rulesStr.find('/');
    if (pos == std::string::npos) {
        std::cerr << "Warning: Invalid format for rules string '" << rulesStr << "'. Expected 'Bx/Sy' format." << std::endl;
        return false;
    }

    std::string birthStr = rulesStr.substr(0, pos);
    std::string surviveStr = rulesStr.substr(pos + 1);

    for (char c : birthStr) {
        if (isdigit(c)) {
            rules[c - '0'] += 2;
        }
    }

    for (char c : surviveStr) {
        if (isdigit(c)) {
            rules[c - '0'] += 1;
        }
    }
    if (line.find("#S") == std::string::npos) {
        std::cerr << "Error: Fourth line should contain size in format '#S x y', but found '" << line << "'." << std::endl;
        return false;
    }
    std::stringstream strs(line.substr(2));
    if (!(strs >> width >> height)) {
        std::cerr << "Error: Invalid format for size in line '" << line << "'. Expected two integers for width and height." << std::endl;
        return false;
    }

    while (std::getline(file, line)) {
        std::stringstream strs(line);
        short x, y;
        if (!(strs >> x >> y)) {
            std::cerr << "Warning: Invalid cell coordinates in line '" << line << "'. Expected two integers for coordinates." << std::endl;
            continue;
        }
        aliveCells.push_back({ x, y });
    }

    file.close();
    std::cout << name << " was loaded successfully." << std::endl;
    return true;
}


bool FileManager::saveToFile(const std::string& filename, const std::set<std::pair<short, short>>& aliveCells) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file '" << filename << "' for saving!" << std::endl;
        return false;
    }

    file << "#Life 1.06\n";

    file << "#N " << name << "\n";

    file << "#R " << rawRules << "\n";

    file << "#S " << width << " " << height << "\n";

    for (const auto& cell : aliveCells) {
        file << cell.first << " " << cell.second << "\n";
    }

    file.close();
    return true;
}

std::string FileManager::getName() const {
    return name;
}

std::string FileManager::getRawRules() const {
    return rawRules;
}

std::array<short, 9> FileManager::getRules() const {
    return rules;
}

std::pair<short, short> FileManager::getSize() const {
    return { width, height };
}

const std::vector<std::pair<short, short>>& FileManager::getAliveCells() const {
    return aliveCells;
}
