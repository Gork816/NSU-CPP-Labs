#include "game.h"
#include <iostream>
#include <array>


Game::Game() : field(), neighbors(), activeCells(), aliveCells(), rules(), width(0), height(0), generation(1) {}

Game::~Game() {}

void Game::initializeFieldFromFile(FileManager& fileManager) {
    auto& fileAliveCells = fileManager.getAliveCells();
    auto size = fileManager.getSize();
    width = size.first;
    height = size.second;
    field = Grid(width, height);
    neighbors = Grid(width, height);

    for (const auto& cell : fileAliveCells) {
        short x = cell.first;
        short y = cell.second;

        if (x >= 0 && x < width && y >= 0 && y < height) {
            field.setCell(x, y, 1);
            aliveCells.emplace(x, y);
        }
        else {
            std::cout << "Warning: Cell (" << x << ", " << y << ") is out of bounds and was not added to the field." << std::endl;
        }
    }

    rules = fileManager.getRules();
    name = fileManager.getName();
    rawRules = fileManager.getRawRules();
}

void Game::processGeneration() {
    for (const auto& cell : aliveCells) {
        short x = cell.first;
        short y = cell.second;

        auto neighborsList = field.getNeighbors(x, y);
        for (const auto& neighbor : neighborsList) {
            short nx = neighbor.first;
            short ny = neighbor.second;
            neighbors.incrementCell(nx, ny);
            activeCells.emplace(nx, ny);
        }

        activeCells.emplace(x, y);
    }

    aliveCells.clear();

    for (const auto& cell : activeCells) {
        short x = cell.first;
        short y = cell.second;
        short neighborCount = neighbors.getCell(x, y);
        short rule = rules[neighborCount];

        bool shouldLive = false;

        if (field.getCell(x, y) == 1) {
            if (rule == 1 || rule == 3) {
                shouldLive = true;
            }
        }
        else {
            if (rule == 2 || rule == 3) {
                shouldLive = true;
            }
        }

        if (shouldLive) {
            aliveCells.emplace(x, y);
        }
    }

    activeCells.clear();
    neighbors.clear();
    refreshField();
    generation++;
}

void Game::printField() const {
    std::cout << name << " - Rules " << rawRules << " - Generation " << generation << std::endl;
    field.print();
}

const std::set<std::pair<short, short>>& Game::getAliveCells() const {
    return aliveCells;
}

std::ostream& operator<<(std::ostream& out, const Game& game) {
    out << game.name << "\n";
    out << game.rawRules << "\n";
    out << game.generation << "\n";
    out << game.width << ' ' << game.height << "\n";

    for (short rule : game.rules) {
        out << rule << ' ';
    }
    out << "\n";

    out << game.activeCells.size() << "\n";
    for (const auto& cell : game.activeCells) {
        out << cell.first << " " << cell.second << "\n";
    }

    out << game.aliveCells.size() << "\n";
    for (const auto& cell : game.aliveCells) {
        out << cell.first << " " << cell.second << "\n";
    }

    out << game.field;
    out << game.neighbors;

    return out;
}


std::istream& operator>>(std::istream& in, Game& game) {
    std::getline(in, game.name);
    //std::cout << game.name << "\n";
    std::getline(in, game.rawRules);
    //std::cout << game.rawRules << "\n";
    in >> game.generation;
    //std::cout << game.generation << "\n";
    in >> game.width >> game.height;
    //std::cout << game.width << game.height << "\n";

    for (short& rule : game.rules) {
        in >> rule;
        //std::cout << rule << " ";
    }
    //std::cout << "Rules loaded.\n";

    short activeCellsCount;
    in >> activeCellsCount;
    //std::cout << activeCellsCount << "\n";
    game.activeCells.clear();
    for (short i = 0; i < activeCellsCount; ++i) {
        short x, y;
        in >> x >> y;
        game.activeCells.emplace(x, y);
        //std::cout << "Cell " << x << ' ' << y << " loaded.\n";
    }
    //std::cout << "activeCells loaded.\n";

    short aliveCellsCount;
    in >> aliveCellsCount;
    std::cout << aliveCellsCount << "\n";
    game.aliveCells.clear();
    for (short i = 0; i < aliveCellsCount; ++i) {
        short x, y;
        in >> x >> y;
        game.aliveCells.emplace(x, y);
        //std::cout << "Cell " << x << ' ' << y << " loaded.\n";
    }
    //std::cout << "aliveCells loaded.\n";

    in >> game.field;
    //std::cout << "Field loaded.\n";
    in >> game.neighbors;
    //std::cout << "Neighbours loaded.\n";

    return in;
}


void Game::refreshField() {
    field.clear();
    for (const auto& cell : aliveCells) {
        short x = cell.first;
        short y = cell.second;
        field.setCell(x, y, 1);
    }
}