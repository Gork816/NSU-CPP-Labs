#pragma once
#include "grid.h"
#include "filemanager.h"
#include <set>
#include <utility>


class Game {
public:
    Game();
    ~Game();

    void initializeFieldFromFile(FileManager& fileManager);
    void processGeneration();
    void refreshField();

    void printField() const;
    const std::set<std::pair<short, short>>& getAliveCells() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
    friend std::istream& operator>>(std::istream& is, Game& game);
private:
    Grid field;
    Grid neighbors;

    short width;
    short height;
    std::array<short, 9> rules;
    std::string name;
    std::string rawRules;

    std::set<std::pair<short, short>> aliveCells;
    std::set<std::pair<short, short>> activeCells;
    int generation;
};