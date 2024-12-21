#pragma once
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <set>


class FileManager {
public:
    FileManager();
    ~FileManager();

    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename, const std::set<std::pair<short, short>>& activeCells);

    std::string getName() const;
    std::string getRawRules() const;
    std::array<short, 9> getRules() const;
    std::pair<short, short> getSize() const;
    const std::vector<std::pair<short, short>>& getAliveCells() const;

private:
    std::string name;
    std::string rawRules;
    std::array<short, 9> rules;
    short width;
    short height;
    std::vector<std::pair<short, short>> aliveCells;
};

