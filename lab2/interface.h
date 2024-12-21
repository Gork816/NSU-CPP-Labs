#pragma once
#include "game.h"
#include "filemanager.h"
#include <string>


class Interface {
private:
    Game& game;
    FileManager& fileManager;

    void executeDump(const std::string& filename);
    void executeTick(int n);
    void executeHelp();
    void executeExit();
    void executeSave(std::ofstream& file);
    void executeLoad(std::ifstream& file);

public:
    Interface(Game& game, FileManager& fileManager);
    ~Interface();

    void run();
    std::string getCommand();
};
